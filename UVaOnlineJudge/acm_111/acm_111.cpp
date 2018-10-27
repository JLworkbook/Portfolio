#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

#define STRINGMAX 100
#define MAXN 24

int LCS (int n, int correct_list[MAXN], int reply_list[MAXN]);

int main () {
	int i;
	
	char input_string[STRINGMAX];
	
	int n;
	int correct_list[MAXN];
	int reply_list[MAXN], score;
	
	/* ranking 為第一個數字應該放在第幾個順位，讀取時要注意 */
	while (fgets (input_string, STRINGMAX, stdin) != NULL) {
		if (strlen(input_string) <= 3) {
			sscanf (input_string, "%d", &n);
			
			fgets (input_string, STRINGMAX, stdin);
			correct_list[atoi(strtok (input_string, " ") )] = 1;
			for (i=2; i<=n; i++) {
				correct_list[atoi(strtok (NULL, " ") )] = i;
			}
		}
		else {
			reply_list[atoi(strtok (input_string, " ") )] = 1;
			for (i=2; i<=n; i++) {
				reply_list[atoi(strtok (NULL, " ") )] = i;
			}
			score = LCS (n, correct_list, reply_list);
			printf ("%d\n", score);
		}
	}
	
	return 0;
}

int LCS (int n, int correct_list[MAXN], int reply_list[MAXN]) {
	int i, j;

	int dp_array[MAXN][MAXN]={0};
	for (i=1; i<=n; i++) {
		for (j=1; j<=n; j++) {
			if (correct_list[i] == reply_list[j]) {
				dp_array[i][j] = dp_array[i-1][j-1] + 1;
			}
			else {
				dp_array[i][j] = max (dp_array[i-1][j], dp_array[i][j-1]);
			}
		}
	}
	
	return dp_array[n][n];
}