#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
using namespace std;

struct Tree {
	int value;
	Tree* left;
	Tree* right;
};

Tree* initial_node ();

int main() {
	int i;
	
	vector<Tree*> level_order_traversal;
	vector<int> path;
	Tree* root = initial_node();
	
	char tmp_char, tmp_num[5], tmp_num_index;
	int value;
	int tree_finish_flag=0, not_complete_flag=0;
	while (scanf ("%c", &tmp_char) != EOF) {
		if (tmp_char == '(') {
			path.clear();
			tmp_num_index = 0;
			while (scanf ("%c", &tmp_char)) {
				if (isdigit(tmp_char)) {
					tmp_num[tmp_num_index++] = tmp_char;
				}
				else
					break;
			}
			if (tmp_char == ')') {
				tree_finish_flag = 1;
			}
			else {
				tmp_num[tmp_num_index] = '\0';
				value = atoi(tmp_num);
				
				while (scanf ("%c", &tmp_char)) {
					if (tmp_char == 'L') path.push_back(1);
					else if (tmp_char == 'R') path.push_back(0);
					else break;
				}
			}
		}
		
		if (tree_finish_flag) {
			int bottom=0;
			level_order_traversal.clear();
			level_order_traversal.push_back(root);
			while (bottom < level_order_traversal.size()) {
				if (level_order_traversal[bottom]->value != -1) {
					if (level_order_traversal[bottom]->left != NULL) {
						level_order_traversal.push_back(level_order_traversal[bottom]->left);
					}
					if (level_order_traversal[bottom]->right != NULL) {
						level_order_traversal.push_back(level_order_traversal[bottom]->right);
					}
				}
				else {
					not_complete_flag = 1;
					break;
				}
				bottom++;
			}

			if (!not_complete_flag) {
				for (i=0; i<level_order_traversal.size(); i++) {
					if (i != 0)
						printf (" ");
					printf ("%d", level_order_traversal[i]->value);
				}
				printf ("\n");
			}
			else {
				printf ("not complete\n");
			}
			root = initial_node();
			not_complete_flag = 0;
			tree_finish_flag = 0;
		}
		else if (tmp_char == ')') {
			Tree* now_node = root;
			for (i=0; i<path.size(); i++) {
				if (path[i]) {
					if (now_node->left == NULL) {
						now_node->left = initial_node();
					}
					now_node = now_node->left;
				}
				else {
					if (now_node->right == NULL) {
						now_node->right = initial_node();
					}
					now_node = now_node->right;
				}
			}
			if (now_node->value == -1) {
				now_node->value = value;
			}
			else {
				not_complete_flag = 1;
			}
		}
	}
	
	return 0;
}

Tree* initial_node () {
	Tree* node = new Tree;
	node->value = -1;
	node->left = NULL;
	node->right = NULL;
	
	return node;
}