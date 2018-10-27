#include <stdio.h>
using namespace std;

#define MAXN 102

int find_max_sum (int n, int array[]);

int main () {
	int i, j, k;
	
	int n;
	int map_array[MAXN][MAXN];
	
	scanf ("%d", &n);
	
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			scanf ("%d", &map_array[i][j]);
		}
	}
	
	int max_sum=map_array[0][0], tmp;
	int sub_array[MAXN];
	for (i=0; i<n; i++) {
		for (k=0; k<n; k++)
			sub_array[k] = 0;
		
		for (j=i; j<n; j++) {
			for (k=0; k<n; k++)
				sub_array[k] += map_array[j][k];
			tmp = find_max_sum(n, sub_array);
			if (max_sum < tmp)
				max_sum = tmp;
		}
	}
	printf ("%d\n", max_sum);
	
	return 0;
}

int find_max_sum (int n, int array[]) {
	int i;
	
	int max=array[0], sum=0;
	for (i=0; i<n; i++) {
		if (sum < 0)
			sum = array[i];
		else
			sum += array[i];
		
		if (max < sum)
			max = sum;
	}
	return max;
}