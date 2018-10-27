#include <stdio.h>
#include <math.h>
#include<algorithm>
using namespace std;

double area (double x1, double y1, double x2, double y2, double x3, double y3) {
	return fabs(x1*y2 + x2*y3 + x3*y1 - x1*y3 - x2*y1 - x3*y2);
}

int main () {
	double triangle[3][2];
	while (scanf ("%lf%lf%lf%lf%lf%lf", &triangle[0][0], &triangle[0][1], &triangle[1][0], &triangle[1][1], &triangle[2][0], &triangle[2][1]) != EOF) {
		if (triangle[0][0] == 0.0 && triangle[0][1] == 0.0 && triangle[1][0] == 0.0 && triangle[1][1] == 0.0 && triangle[2][0] == 0.0 && triangle[2][1] == 0.0) {
			break;
		}
		
		int min_x = max(1, (int)ceil( min( min(triangle[0][0], triangle[1][0]), triangle[2][0]) ) );
		int min_y = max(1, (int)ceil( min( min(triangle[0][1], triangle[1][1]), triangle[2][1]) ) );
		int max_x = min(99, (int)floor( max( max(triangle[0][0], triangle[1][0]), triangle[2][0]) ) );
		int max_y = min(99, (int)floor( max( max(triangle[0][1], triangle[1][1]), triangle[2][1]) ) );
		
		int inside_tree_num=0;
		for (int i=min_x; i<=max_x; i++) {
			for (int j=min_y; j<=max_y; j++) {
				if (fabs( area(i, j, triangle[0][0], triangle[0][1], triangle[1][0], triangle[1][1])
					    + area(i, j, triangle[1][0], triangle[1][1], triangle[2][0], triangle[2][1])
					    + area(i, j, triangle[2][0], triangle[2][1], triangle[0][0], triangle[0][1])
					    - area(triangle[0][0], triangle[0][1], triangle[1][0], triangle[1][1], triangle[2][0], triangle[2][1]) ) 
						< 1e-8) {
					inside_tree_num++;
				}
			}
		}
		printf ("%4d\n", inside_tree_num);
	}
	
	return 0;
}