#include <stdio.h>
#include <algorithm>
using namespace std;

#define TARGET 1500

int main () {
	unsigned long long int ugly_number[TARGET+1];
	ugly_number[1] = 1;
	int p2=1, p3=1, p5=1;
	for (int n=2; n<=TARGET; n++) {
		while (ugly_number[p2]*2 <= ugly_number[n-1]) p2++;
		while (ugly_number[p3]*3 <= ugly_number[n-1]) p3++;
		while (ugly_number[p5]*5 <= ugly_number[n-1]) p5++;
		ugly_number[n] = min(ugly_number[p2]*2, min(ugly_number[p3]*3, ugly_number[p5]*5) );
	}
	printf ("The 1500'th ugly number is %d.\n", ugly_number[TARGET]);

	return 0;
}