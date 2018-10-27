#include <stdio.h>
using namespace std;

#define MAXN 1000002

int pythagorean_basic_triple[MAXN]={0};
int used_min[MAXN];

int tmp_minus[MAXN]={0};

int contain_base_triple[MAXN];
int non_part_triple[MAXN];

int gcd (int m, int n);

int main() {
	int i, j, k;
	
	for (i=0; i<MAXN; i++) {
		used_min[i] = MAXN;
	}
		
	
	int x, y, z;
	for (i=2; i<1000; i++) {
		for (j=1; j<i; j++) {
			if ((i+j)%2 == 1 && gcd(i, j) == 1) {
				x = i*i-j*j;
				y = 2*i*j;
				z = i*i+j*j;
				if (z >= MAXN)
					continue;
				
				pythagorean_basic_triple[z]++;
				
				for (k=1; z*k<MAXN; k++) {
					if (z*k < used_min[x*k]) {
						used_min[x*k] = z*k;
					}
					if (z*k < used_min[y*k]) {
						used_min[y*k] = z*k;
					}
					if (z*k < used_min[z*k]) {
						used_min[z*k] = z*k;
					}
				}
			}
		}
	}
	
	/* tmp_minus用來記錄最小被當成直角三角形任意邊時的最小斜邊 */
	
	int tmp=0, tmp_base=0;
	for (i=1; i<MAXN; i++) {
		tmp_minus[used_min[i]]++;
		tmp_minus[i] += tmp_minus[i-1];
		non_part_triple[i] = i-tmp_minus[i];
		
		tmp_base += pythagorean_basic_triple[i];
		contain_base_triple[i] = tmp_base;
	}
	
	int N;
	while (scanf ("%d", &N) != EOF) {
		printf ("%d %d\n", contain_base_triple[N], non_part_triple[N]);
	}	
	
	return 0;
}

int gcd (int m, int n) {
	int r;
	while (n != 0) {
		r = m%n;
		m = n;
		n = r;
	}
	return m;
}