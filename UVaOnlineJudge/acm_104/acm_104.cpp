#include <stdio.h>
using namespace std;

#define MAXDIMENSION 22

double transformation_table[MAXDIMENSION][MAXDIMENSION][MAXDIMENSION];
int path[MAXDIMENSION][MAXDIMENSION][MAXDIMENSION];

void find_path (int i, int j, int steps);
void modified_floyd_warshall (int n);

int main () {
	int i, j, k;
	
	int n;
	while (scanf("%d", &n) != EOF) {
		for (i=0; i<n; i++) {
			for (j=0; j<n; j++) {
				for (k=0; k<=n; k++) {
					transformation_table[i][j][k] = 0.0;
				}
			}
		}
		
		for (i=0; i<n; i++) {
			for (j=0; j<n; j++) {
				if (i == j)
					transformation_table[i][j][1] = 1.0;
				else
					scanf("%lf", &transformation_table[i][j][1]);
				path[i][j][1] = i;
			}
		}
		
		modified_floyd_warshall (n);
		
		/*
		for (i=0; i<n; i++) {
			for (j=0; j<n; j++) {
				printf (" %.2f", transformation_table[i][j][1]);
			}
			printf ("\n");
		}
		*/
	}
	
	return 0;
}

void find_path (int i, int j, int steps) {
	int k = path[i][j][steps];
	if (steps > 1)
		find_path (i, k, steps-1);
	
	printf ("%d ", k+1);
}

void modified_floyd_warshall (int n) {
	int i, j, k;
	
	int steps;
	double tmp;
	for (steps=2; steps<=n; steps++) {
		for (k=0; k<n; k++) {
			for (i=0; i<n; i++) {
				for (j=0; j<n; j++) {
					tmp = transformation_table[i][k][steps-1]*transformation_table[k][j][1];
					//printf ("%d, %d, %d, %d\n", i, j, k, steps);
					//printf ("%f, %f\n", tmp, transformation_table[i][j][steps]);
					if (tmp > transformation_table[i][j][steps]) {
						transformation_table[i][j][steps] = tmp;
						path[i][j][steps] = k;
					}
				}
			}
		}
		for (i=0; i<n; i++) {
			if (transformation_table[i][i][steps] > 1.01) {
				//printf ("profit=%f\n", transformation_table[i][i][steps]);
				find_path (i, i, steps);
				printf ("%d\n", i+1);
				return;
			}
		}
	}
	
	
	for (steps=2; steps<=n; steps++) {
		for (i=0; i<n; i++) {
			if (transformation_table[i][i][steps] > 1.01) {
				//printf ("profit=%f\n", transformation_table[i][i][steps]);
				find_path (i, i, steps);
				printf ("%d\n", i+1);
				return;
			}
		}
	}
	
	printf ("no arbitrage sequence exists\n");
	return ;
}
