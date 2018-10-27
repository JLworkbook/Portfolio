#include <stdio.h>
#include <math.h>
using namespace std;

int main () {
	int n=1, count=0;
	while (count < 10) {
		double x = ( (2.0*n+1) + sqrt(8.0*n*n+8.0*n+1.0) ) / 2;
		if (x - (int)x == 0) {
			printf ("%10d%10d\n", (int)x, (int)x+n);
			count++;
		}
		n++;
	}
	
	return 0;
}