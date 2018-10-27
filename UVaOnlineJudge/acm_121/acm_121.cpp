#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
	int i;
	
	float self_sqrt_3 = sqrt(3.0)/2.0;
	
	int grid_num;
	int skew_num[2], skew_flat_num;
	
	float width, height;
	while (scanf ("%f%f", &width, &height) != EOF) {
		grid_num = floor(width)*floor(height);
		
		skew_flat_num = floor((height-1.0)/self_sqrt_3) + 1;
		skew_num[0] = skew_flat_num*floor(width);
		if (width-floor(width) < 0.5) {
			skew_num[0] -= skew_flat_num/2;
		}
		skew_flat_num = floor((width-1.0)/self_sqrt_3) + 1;
		skew_num[1] = skew_flat_num*floor(height);
		if (height-floor(height) < 0.5) {
			skew_num[1] -= skew_flat_num/2;
		}
		if (skew_num[0] < skew_num[1])
			swap (skew_num[0], skew_num[1]);
		
		if (grid_num >= skew_num[0]) {
			printf ("%d grid\n", grid_num);
		}
		else {
			printf ("%d skew\n", skew_num[0]);
		}
	}
	
	return 0;
}