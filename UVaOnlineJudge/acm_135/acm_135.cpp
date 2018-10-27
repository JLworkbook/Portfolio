#include <stdio.h>
using namespace std;

int main () {
	int k;
	bool first=true;
	while (scanf ("%d", &k) != EOF) {
		if (!first) 
			printf ("\n");
		else
			first = false;
		
		int m = k-1;
		
		for (int i=0; i<k; i++) {
			printf ("1");
			for (int j=1; j<k; j++) {
				printf (" %d", i*m+j+1);
			}
			printf ("\n");
		}
		
		for (int i=0; i<m; i++) {
			for (int j=0; j<m; j++) {
				printf ("%d", i+2);
				for (int s=0; s<m; s++) {
					printf (" %d", ( (j+(s*i))%m + s*m + k + 1)  );
				}
				printf ("\n");
			}
		}
	}
	
	return 0;
}