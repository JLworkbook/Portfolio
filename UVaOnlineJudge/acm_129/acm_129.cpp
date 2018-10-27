#include <stdio.h>
#include <vector>
using namespace std;

char alphabet[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
void dfs (int n, int L, int &count, vector<int> list);
bool check_hard (vector<int> list);

int main () {
	int n, L;
	while (scanf ("%d%d", &n, &L) != EOF) {
		if (n == 0 && L == 0)
			break;
		
		int count = 0;
		vector<int> list;
		dfs (n, L, count, list);
	}
	
	return 0;
}

bool check_hard (vector<int> list) {
	for (int i=1; i<=list.size()/2; i++) {
		bool repeat_flag=true;
		for (int j=0; j<i; j++) {
			if (list[list.size()-1-j] != list[list.size()-1-i-j]) {
				repeat_flag = false;
				break;
			}
		}
		if (repeat_flag)
			return false;
	}
	return true;
}


/* 窮舉 */
void dfs (int n, int L, int &count, vector<int> list) {
	if (!list.empty()) {
		if(!check_hard(list))
			return;
		else 
			count++;
	}
	
	/*
	printf ("%d ", count);
	for (int i=0; i<list.size(); i++) {
		printf ("%c", alphabet[list[i]]);
	}
	printf ("\n");
	*/
	
	if (count == n) {
		for (int i=0; i<list.size(); i++) {
			if (i!=0 && i%4 == 0) {
				if (i%64 == 0)
					printf ("\n");
				else
					printf (" ");
			}
			printf ("%c", alphabet[list[i]]);
		}
		printf ("\n");
		
		printf ("%d\n", list.size());
		
		return;
	}
	
	for (int i=0; i<L; i++) {
		list.push_back(i);
		dfs (n, L, count, list);
		if (count >= n)
			return;
		list.pop_back();
	}
	
	return;
}