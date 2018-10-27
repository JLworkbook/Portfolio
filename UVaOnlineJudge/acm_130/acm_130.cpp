#include <stdio.h>
#include <vector>
using namespace std;

int main () {
	int n, k;
	while (scanf ("%d%d", &n, &k) != EOF) {
		if (n == 0 && k == 0)
			break;
		
		vector<int> people_list;
		for (int i=1; i<=n; i++) {
			people_list.push_back(i);
		}
		
		int target = -1, bury_person;
		while (people_list.size() > 1) {
			target = (target+k)%people_list.size();
			/*
			printf ("%d %d\n", people_list[target], target);
			*/
			people_list.erase(people_list.begin()+target);
			
			
			bury_person = (target-1+k)%people_list.size();
			int temp = people_list[bury_person];
			people_list.erase(people_list.begin()+bury_person);
			
			if (bury_person < target)
				target--;
			
			people_list.insert(people_list.begin()+target, temp);
			/*
			for (int i=0; i<people_list.size(); i++)
				printf ("%d ", people_list[i]);
			printf ("\n");
			*/
		}
		if (people_list[0] > 1)
			printf ("%d\n", n+2-people_list[0]);
		else
			printf ("1\n");
	}
	
	return 0;
}