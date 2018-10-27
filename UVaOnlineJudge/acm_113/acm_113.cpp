#include <stdio.h>
#include <math.h>

int main () {
	int i;
	
	double n, p;
	while (scanf ("%lf%lf", &n, &p) != EOF) {
		printf ("%.0f\n", pow(p, 1.0/n));
	}

	return 0;
}