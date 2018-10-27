#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
using namespace std;

int main () {
	int i;
	
	char tmp_c;
	char tmp_string[100], tmp_string_len;
	int tmp_sum, tmp_num;
	
	vector<int> stack;
	int target_integer, find_target_flag;
	int tree_level, tree_level_child[10000];
	while (scanf("%d", &target_integer) != EOF) {
		tree_level = 0;
		do {
			scanf ("%c", &tmp_c);
		} while (tmp_c != '(');
		tree_level++;
		
		for (i=0; i<10000; i++) {
			tree_level_child[i] = 0;
		}
		
		find_target_flag = 0;
		tmp_string_len = 0;
		tmp_sum = 0;
		while (tree_level > 0) {
			scanf ("%c", &tmp_c);
			
			if (tmp_c == '-' || isdigit(tmp_c)) {
				tmp_string[tmp_string_len++] = tmp_c;
			}
			else {
				if (tmp_string_len > 0) {
					tmp_string[tmp_string_len] = '\0';
					tmp_num = atoi(tmp_string);
					tmp_string_len = 0;
					
					tree_level_child[tree_level-1] = 1;
					stack.push_back (tmp_num);
					tmp_sum += tmp_num;
				}
				
				if (tmp_c == '(') {
					tree_level++;
				}
				else if (tmp_c == ')') {
					if (tree_level == stack.size()) {
						if (!tree_level_child[tree_level]) {
							if (tmp_sum == target_integer) {
								find_target_flag = 1;
							}
						}
						tmp_sum -= stack.back();
						stack.pop_back();
					}
					tree_level_child[tree_level] = 0;
					tree_level--;
				}
			}
		}
		
		if (find_target_flag) {
			printf ("yes\n");
		}
		else {
			printf ("no\n");
		}
	}
	
	return 0;
}