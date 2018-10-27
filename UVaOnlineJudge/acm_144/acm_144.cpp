#include <stdio.h>
using namespace std;

int main () {
	int N, k;
	while (scanf ("%d%d", &N, &k) != EOF) {
		if (N == 0 && k == 0)
			break;
		
		int value=0, index=0, leave_count=0;
		int people[26]={0};
		
		int next_money=0;
		while (leave_count < N) {
			if (next_money == 0) {
				value = (value < k)? value+1: 1;
				next_money = value;
			}
			
			if (people[index] != 40) {
				if (people[index]+next_money < 40) {
					people[index] += next_money;
					next_money=0;
				}
				else {
					next_money = next_money-(40-people[index]);
					people[index] = 40;
					leave_count++;
					
					printf ("%3d", index+1);
				}
			}
			
			index = (index+1)%N;
		}
		printf ("\n");
	}

	return 0;
}