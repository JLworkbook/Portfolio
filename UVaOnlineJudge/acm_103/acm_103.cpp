#include <stdio.h>
#include <algorithm>
using namespace std;

#define MAXBOX 32
#define MAXDIMENTION 12

int box_array[MAXBOX][MAXDIMENTION];
int array_index[MAXBOX];
int length[MAXBOX];
int prev_box[MAXBOX];

void insert_sort (int k, int n);
void LIS(int k, int n);
int box_compare (int array_1[MAXDIMENTION], int array_2[MAXDIMENTION], int n);
void output_box (int k);

int main() {
	int i, j;
	
	int k, n;
	while (scanf ("%d%d", &k, &n) != EOF) {
		for (i=0; i<k; i++) {
			array_index[i] = i;
			for (j=0; j<n; j++) {
				scanf ("%d", &box_array[i][j]);
			}
		}
		
		for (i=0; i<k; i++) {
			sort (box_array[i], box_array[i]+n);
		}
		
		insert_sort (k, n);
		LIS (k, n);
		
		/*
		for (i=0; i<k; i++) {
			printf ("%d:", i);
			for (j=0; j<n; j++) {
				printf (" %d", box_array[array_index[i]][j]);
			}
			printf ("\n");
		}
		*/
		output_box(k);
	}
	
	return 0;
}

/* 先將箱子由小排到大，一樣大的順序沒差，但是要確保任何 box[i]<box[j], then i<j */
void insert_sort (int k, int n) {
	int i,j,l;
	
	int temp;
	bool insert_flag;
	for (i=0; i<k; i++) {
		for (j=0; j<i; j++) {
			insert_flag = true;
			for (l=0; l<n; l++) {
				if (box_array[array_index[i]][l] >= box_array[array_index[j]][l])
					insert_flag = false;
			}
			if (insert_flag) {
				break;
			}
		}
		temp = array_index[i];
		for (l=i-1; l>=j; l--) {
			array_index[l+1] = array_index[l];
		}
		array_index[j] = temp;
	}
	
	return ;
}

/* 箱子比大小 */
int box_compare (int array_1[MAXDIMENTION], int array_2[MAXDIMENTION], int n) {
	int i;
	
	bool bigger_flag=false, smaller_flag=false;
	for (i=0; i<n; i++) {
		if (array_1[i] < array_2[i])
			smaller_flag = true;
		else if (array_1[i] > array_2[i])
			bigger_flag = true;
		else {
			smaller_flag = true;
			bigger_flag = true;
		}
	}
	if (bigger_flag && smaller_flag) return 0;
	else if (bigger_flag) return 1;
	else return -1;
	
	return 0;
}

/* 用LIS去找出最長遞增序列 */
void LIS(int k, int n) {
	int i,j;
	
	for (i=0; i<k; i++) {
		length[i]=1;
		prev_box[i]=-1;
	}
	
	for (i=0; i<k; i++) {
		for (j=i+1; j<k; j++) {
			if (box_compare(box_array[array_index[i]], box_array[array_index[j]], n) == -1) {
				if (length[i]+1 > length[j]) {
					length[j] = length[i]+1;
					prev_box[j] = i;
				}
			}
		}
	}
	
	return ;
}

void output_box (int k) {
	int i;
	
	int max_length=-1, last_index=0;
	for (i=0; i<k; i++) {
		if (length[i] > max_length) {
			max_length = length[i];
			last_index = i;
		}
	}
	
	int output_array[MAXBOX], index=0;
	do {
		output_array[index++] = last_index;
		last_index = prev_box[last_index];
	} while (last_index != -1);
	
	printf ("%d\n", max_length);
	for (i=max_length-1; i>=0; i--) {
		if (i != max_length-1) {
			printf (" ");
		}
		printf ("%d", array_index[output_array[i]]+1);
	}
	printf ("\n");
	
	return ;
}