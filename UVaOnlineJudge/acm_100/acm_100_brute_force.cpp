#include <iostream>
#include <stdio.h>

void swap(int &a, int &b);
int cycleLength(int n);

int main() {
	int i;
	
	int a1, a2;
	while(scanf("%d %d" , &a1, &a2) != EOF) {
		printf ("%d %d ", a1, a2);
		if (a1 > a2) 
			swap(a1, a2);
		
		int maxLength=1, temp;
		for (i=a1 ; i<=a2 ;i++) {
			temp = cycleLength(i);
			if (temp > maxLength)
				maxLength = temp;
		}
		
		printf ("%d\n", maxLength);
	}
	
	return 0;
}

void swap(int &a, int &b) {
	int temp;
	
	temp = a;
	a = b;
	b = temp;
	
	return;
}

int cycleLength(int n) 
{
	int count=1;
	while (n != 1) {
		if (n%2 == 0) n /= 2;
		else n = 3*n + 1;
		
		count += 1;
	}
	return count;
}