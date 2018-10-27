#include <stdio.h>
using namespace std;

int main () {
	int road_num, city_id=0;
	while (scanf ("%d", &road_num) != EOF) {
		int map[32][32]={0}, interseption_num=0;
		for (int i=0; i<road_num; i++) {
			int start, end;
			scanf ("%d%d", &start, &end);
			map[start][end] = 1;
			
			if (interseption_num < start)
				interseption_num = start;
			if (interseption_num < end)
				interseption_num = end;
		}
		
		for (int k=0; k<=interseption_num; k++) {
			for (int i=0; i<=interseption_num; i++) {
				for (int j=0; j<=interseption_num; j++) {
					map[i][j] += map[i][k]*map[k][j];
				}
			}
		}
		
		for (int i=0; i<=interseption_num; i++) {
			for (int j=i+1; j<=interseption_num; j++) {
				if (map[i][j] != 0 && map[j][i] != 0) {
					map[i][j] = -1;
					map[j][i] = -1;
				}
			}
		}
		
		for (int k=0; k<=interseption_num; k++) {
			for (int i=0; i<=interseption_num; i++) {
				for (int j=0; j<=interseption_num; j++) {
					if (map[i][k] == -1 && map[k][j] != 0) {
						map[i][j] = -1;
					}
					if (map[k][j] == -1 && map[i][k] != 0) {
						map[i][j] = -1;
					}
				}
			}
		}
		
		printf ("matrix for city %d\n", city_id);
		for (int i=0; i<=interseption_num; i++) {
			for (int j=0; j<=interseption_num; j++) {
				if (j != 0)
					printf (" ");
				printf ("%d", map[i][j]);
			}
			printf ("\n");
		}
		
		city_id++;
	}

	return 0;
}