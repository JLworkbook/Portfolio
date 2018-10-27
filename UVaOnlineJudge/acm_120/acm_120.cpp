#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

/* 把當前最大數翻轉到最前面，再翻轉到最後面，其他依此類推 */

void flip (int n, vector<int> &pancakes);

int main () {
	int i, j ,k;
	
	vector<int> pancakes, sorted_pancakes;
	vector<int> tmp_plant;
	int diameter;
	
	char tmp_char, tmp_digit[5];
	int tmp_digit_position=0;
	while (scanf ("%c", &tmp_char) != EOF) {
		if (isdigit(tmp_char)) {
			tmp_digit[tmp_digit_position++] = tmp_char;
		}
		else {
			if (tmp_digit_position > 0) {
				tmp_digit[tmp_digit_position]='\0';
				diameter = atoi(tmp_digit);
				pancakes.push_back(diameter);
				tmp_digit_position = 0;
			}
			
			if (tmp_char == '\n') {
				sorted_pancakes.assign(pancakes.begin(), pancakes.end());
				sort (sorted_pancakes.begin(), sorted_pancakes.end());
				
				for (i=0; i<pancakes.size(); i++) {
					if (i != 0)
						printf (" ");
					printf ("%d", pancakes[i]);
				}
				printf ("\n");
				
				int max_index;
				for (i=sorted_pancakes.size()-1; i>0; i--) {
					for (j=0; j<i; j++) {
						if (pancakes[j] == sorted_pancakes[i]) {
							max_index = j;
							break;
						}
					}
					if (j == 0) {
						flip (i, pancakes);
						printf ("%d ", sorted_pancakes.size()-i);
					}
					else if (j < i) {
						flip (j, pancakes);
						flip (i, pancakes);
						printf ("%d %d ", sorted_pancakes.size()-j, sorted_pancakes.size()-i);
					}
					
					/*
					for (int S=0; S<pancakes.size(); S++) {
						if (S != 0)
							printf (" ");
						printf ("%d", pancakes[S]);
					}
					printf ("\n");
					*/
				}
				printf ("0\n");	
				
				pancakes.clear();
			}
		}
	}
	

	return 0;
}

void flip (int n, vector<int> &pancakes) {
	int i;
	
	for (i=0; i<(n+1)/2; i++) {
		swap (pancakes[i], pancakes[n-i]);
	}
	
	return;
}