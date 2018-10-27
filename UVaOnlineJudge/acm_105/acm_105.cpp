#include <stdio.h>
using namespace std;

#define MAXCOORDINATE 10002
int building[MAXCOORDINATE]={0};

int main() {
	int i, j;
	
	int left, height, right;
	int min_left=MAXCOORDINATE-1, max_right=0;
	while (scanf ("%d%d%d", &left, &height, &right) != EOF) {
		if (left < min_left)
			min_left = left;
		if (right > max_right)
			max_right = right;
		
		for (i=left+1; i<=right; i++) {
			if (height > building[i]) {
				building[i] = height;
			}
		}
	}
	/*
	for (i=min_left; i<=max_right; i++) {
		printf ("%d:%d\n", i, building[i]);
	}
	*/
	printf ("%d %d", min_left, building[min_left+1]);
	for (i=min_left+1; i<=max_right; i++) {
		if (building[i] > building[i+1]) {
			printf (" %d %d", i, building[i+1]);
		}
		else if (building[i] < building[i+1]) {
			printf (" %d %d", i, building[i+1]);
		}
	}
	printf ("\n");

	return 0;
}