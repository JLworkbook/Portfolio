#include <stdio.h>
using namespace std;

#define ROWMAX 12
#define COLUMNMAN 102

int find_min_row (int matrix[ROWMAX][COLUMNMAN], int col, int up_row, int middle_row, int down_row);

int main () {
	int i, j;
	
	int m, n;
	
	int origin_matrix[ROWMAX][COLUMNMAN];
	int dp_matrix[ROWMAX][COLUMNMAN], pre_row[ROWMAX][COLUMNMAN];
	int tmp_min;
	int min_index;
	int up_i, down_i;
	while (scanf ("%d%d", &m, &n) != EOF) {
		for (i=0; i<m; i++) {
			for (j=0; j<n; j++) {
				scanf ("%d", &origin_matrix[i][j]);
			}
		}
		
		for (i=0; i<m; i++) {
			for (j=0; j<n; j++) {
				dp_matrix[i][j] = origin_matrix[i][j];
			}
		}
		
		for (j=n-2; j>=0; j--) {
			for (i=0; i<m; i++) {
				up_i = (i+1)%m;
				down_i = (i-1+m)%m;
				pre_row[i][j] = find_min_row (dp_matrix, j+1, up_i, i, down_i);
				dp_matrix[i][j] += dp_matrix[pre_row[i][j]][j+1];
			}
		}
		
		tmp_min = dp_matrix[0][0];
		min_index = 0;
		for (i=1; i<m; i++) {
			if (dp_matrix[i][0] < tmp_min) {
				tmp_min = dp_matrix[i][0];
				min_index = i;
			}
		}
		
		for (j=0; j<n; j++) {
			if (j != 0)
				printf (" ");
			printf ("%d", min_index+1);
			min_index = pre_row[min_index][j];
		}
		printf ("\n");
		printf ("%d\n", tmp_min);
		
		/*
		for (i=0; i<m; i++) {
			for (j=0; j<n; j++) {
				printf ("%3d ", origin_matrix[i][j]);
			}
			printf ("\n");
		}
		printf ("\n");
		
		for (i=0; i<m; i++) {
			for (j=0; j<n; j++) {
				printf ("%3d ", dp_matrix[i][j]);
			}
			printf ("\n");
		}
		printf ("\n");
		*/
	}

	return 0;
}

int find_min_row (int matrix[ROWMAX][COLUMNMAN], int col, int up_row, int middle_row, int down_row) {
	int i, j;

	if (matrix[up_row][col] < matrix[middle_row][col]) {
		if (matrix[middle_row][col] <= matrix[down_row][col]) {
			return up_row;
		}
		else if (matrix[up_row][col] < matrix[down_row][col]) {
			return up_row;
		}
		else if (matrix[up_row][col] == matrix[down_row][col]) {
			if (up_row <= down_row)
				return up_row;
			else 
				return down_row;
		}
		else
			return down_row;
	}
	else if (matrix[up_row][col] == matrix[middle_row][col]) {
		if (matrix[middle_row][col] < matrix[down_row][col]) {
			if (up_row <= middle_row)
				return up_row;
			else 
				return middle_row;
		}
		else if (matrix[middle_row][col] == matrix[down_row][col]) {
			if (up_row <= middle_row && up_row <= down_row)
				return up_row;
			else if (middle_row <= down_row) {
				return middle_row;
			}
			else 
				return down_row;
		}
		else {
			return down_row;
		}
	}
	else {
		if (matrix[middle_row][col] < matrix[down_row][col]) {
			return middle_row;
		}
		else if (matrix[middle_row][col] == matrix[down_row][col]) {
			if (middle_row <= down_row)
				return middle_row;
			else 
				return down_row;
		}
		else
			return down_row;
	}
}
