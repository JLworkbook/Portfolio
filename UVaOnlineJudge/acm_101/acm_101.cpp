#include <stdio.h>
#include <string.h>

#define STACKMAX 30

struct Block{
	int position;
	int top;
};

int main() {
	int i, j;
	
	int n;
	scanf("%d", &n);
	
	int stack_list[STACKMAX][STACKMAX], top_list[STACKMAX];
	Block block[STACKMAX];
	for (i=0; i<n; i++) {
		top_list[i] = 0;
		stack_list[i][top_list[i]] = i;
		block[i].position = i;
		block[i].top = 0;
	}
	
	int a, b;
	char command_string_1[5], command_string_2[5];
	int a_position, b_position, a_old_top;
	while (scanf("%s", command_string_1) != EOF) {
		if (strcmp(command_string_1, "quit") == 0)
			break;
		
		scanf ("%d%s%d", &a, command_string_2, &b);
		if (block[a].position == block[b].position)
			continue;
		
		a_position = block[a].position;
		if (strcmp(command_string_1, "move") == 0) {
			for (i=block[a].top+1; i<=top_list[a_position]; i++) {
				top_list[stack_list[a_position][i]] = 0;
				block[stack_list[a_position][i]].position = stack_list[a_position][i] ;
				block[stack_list[a_position][i]].top = 0 ;
			}
			top_list[a_position] = block[a].top;
		}
		
		b_position = block[b].position;
		if (strcmp(command_string_2, "onto") == 0) {	
			for (i=block[b].top+1; i<=top_list[b_position]; i++) {
				top_list[stack_list[b_position][i]] = 0;
				block[stack_list[b_position][i]].position = stack_list[b_position][i] ;
				block[stack_list[b_position][i]].top = 0 ;
			}
			top_list[b_position] = block[b].top;
		}
		
		/* pile(move) a over(onto) b */
		a_old_top = block[a].top;
		for (i=block[a].top; i<=top_list[a_position]; i++) {
			stack_list[b_position][++top_list[b_position]] = stack_list[a_position][i];
			block[stack_list[a_position][i]].position = b_position;
			block[stack_list[a_position][i]].top = top_list[b_position];
		}
		top_list[a_position] = a_old_top-1;
	}
	
	for (i=0; i<n; i++) {
		printf("%d:", i);
		for (j=0; j<=top_list[i]; j++) {
			printf (" %d", stack_list[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}