#include <iostream>
#include <stdio.h>
#define MAX 10001

void swap(int &a, int &b);
int cycleLength (unsigned long long int n);

int cycle_length_array[MAX]={0};

int stack[MAX];
int top=-1;
void push(unsigned long long int n);
unsigned long long int pop();

int main() {
	int i;
	
	int a1, a2;
	while(scanf("%d %d" , &a1, &a2) != EOF) {
		printf ("%d %d ", a1, a2);
		if (a1 > a2) 
			swap(a1, a2);
		
		int maxLength=1, temp;
		for (i=a1 ; i<=a2 ;i++) {
			int temp_cycle_length = cycleLength(i);
			if (temp_cycle_length > maxLength)
				maxLength = temp_cycle_length;
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

/* 邊做邊記錄曾經碰過的數字，以節省計算量 */
int cycleLength (unsigned long long int n) {
	int cycle_length_count=1;
	while (n != 1) {
		if (n < MAX && cycle_length_array[n] != 0) {
			cycle_length_count = cycle_length_array[n];
			n = 1;
		}
		else {
			push(n);
			n = (n%2 == 0)? n/2: n*3+1 ;
		}
	}
	int temp_pop;
	while (top != -1) {
		cycle_length_count++;
		temp_pop = pop();
		if (temp_pop < MAX) {
			cycle_length_array[temp_pop] = cycle_length_count;
		}
	}
	
	return cycle_length_count;
}

void push(unsigned long long int n){
	if (top < MAX)
		stack[++top] = n;
	return;
}
unsigned long long int pop() {
	if (top != -1) {
		top--;
		return stack[top+1];
	}
	return -1;
}
