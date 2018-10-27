#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int map[30][30];
bool node_used[30];
vector<int> best_list;
int min_bandwidth;
int node_count;

void findBandwidth (int bandwidth, vector<int> &list, bool list_used[30]);

int main () {
	char input[100];
	while (scanf ("%s", input) != EOF) {
		if (strcmp(input, "#") == 0)
			break;
		
		memset(map, 0, sizeof(map));
		memset(node_used, 0, sizeof(node_used));
		
		int index=0;
		while (index < strlen(input)) {
			int node1 = input[index]-'A';
			node_used[node1] = true;
			
			index += 2;
			while (index < strlen(input) && input[index] != ';') {
				int node2 = input[index]-'A';
				node_used[node2] = true;
				
				map[node1][node2] = true;
				map[node2][node1] = true;
				
				index++;
			}
			index++;
		}
		
		best_list.clear();
		node_count=0;
		for (int i=0; i<26; i++) {
			if (node_used[i]) {
				node_count++;
				best_list.push_back(i);
			}
		}
		min_bandwidth = node_count;
		
		vector<int> list;
		bool list_used[30]={0};
		findBandwidth (0, list, list_used);
		
		for (int i=0; i<best_list.size(); i++) {
			printf ("%c ", (best_list[i]+'A'));
		}
		printf ("-> %d\n", min_bandwidth);
	}

	return 0;
}

void findBandwidth (int bandwidth, vector<int> &list, bool list_used[30]) {
	if (bandwidth >= min_bandwidth)
		return;
	
	if (list.size() > 0) {
		int last = list.size()-1;
		for (int i=0; i<list.size()-1; i++) {
			if (map[list[i]][list[last]] && (last-i) > bandwidth) {
				bandwidth = last-i;
				if (bandwidth >= min_bandwidth)
					return;
				
				break;
			}
		}
	}
	
	if (list.size() < node_count) {
		for (int i=0; i<26; i++) {
			if (node_used[i] && !list_used[i]) {
				list_used[i] = true;
				list.push_back(i);
				findBandwidth (bandwidth, list, list_used);
				list.pop_back();
				list_used[i] = false;
			}
		}
	}
	else {
		if (bandwidth < min_bandwidth) {
			for (int i=0; i<list.size(); i++)
				best_list[i] = list[i];
			min_bandwidth = bandwidth;
		}
	}
	
	return;
}
