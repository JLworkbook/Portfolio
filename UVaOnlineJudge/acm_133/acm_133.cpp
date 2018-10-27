#include <stdio.h>
#include <vector>
using namespace std;

int main() {
	int N, k, m;
	
	while (scanf ("%d%d%d", &N, &k, &m) != EOF) {
		if (N == 0 && k == 0 && m == 0)
			break;
		
		vector<int> people;
		for (int i=1; i<=N; i++) {
			people.push_back(i);
		}
		
		int start_flag = true;
		int first_index=-1, second_index=N;
		
		while (!people.empty()) {
			if (start_flag)
				start_flag = false;
			else 
				printf (",");	
			
			while (first_index < 0)
				first_index += people.size();
			first_index = (first_index+k)%people.size();
			
			second_index = second_index-m;
			while (second_index < 0)
				second_index += people.size();
			second_index %= people.size();
			
			if (first_index > second_index) {
				printf ("%3d%3d", people[first_index], people[second_index]);
				
				people.erase(people.begin()+first_index);
				people.erase(people.begin()+second_index);
				first_index -= 2;
			}
			else if (second_index > first_index) {
				printf ("%3d%3d", people[first_index], people[second_index]);
				
				people.erase(people.begin()+second_index);
				people.erase(people.begin()+first_index);
				first_index -= 1;
				second_index -= 1;
			}
			else {
				printf ("%3d", people[first_index]);
				
				people.erase(people.begin()+first_index);
				first_index -= 1;
			}
		}
		
		printf ("\n");
	}
	
	
	return 0;
}