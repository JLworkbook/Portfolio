#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;

#define NAMEMAX 32

int main () {
	int i;
	
	map<string, string> tree;
	char child[NAMEMAX], parent[NAMEMAX];
	while (scanf ("%s%s", child, parent) != EOF) {
		if (strcmp(child, "no.child") == 0) 
			break;
		
		tree[string(child)] = string(parent);
	}
	
	int parent_count_1, parent_count_2;
	int k, j;
	map<string, int> parent_list;
	char name_1[NAMEMAX], name_2[NAMEMAX];
	string temp_name;
	bool find_flag;
	while (scanf ("%s%s", name_1, name_2) != EOF) {
		find_flag = false;
		parent_list.clear();
		
		parent_count_1 = 0;
		temp_name = string(name_1);
		parent_list[temp_name] = parent_count_1++;
		while (tree.find(temp_name) != tree.end()) {
			temp_name = tree[temp_name];
			parent_list[temp_name] = parent_count_1++;
		}
		
		parent_count_2 = 0;
		temp_name = string(name_2);
		if (parent_list.find(temp_name) != parent_list.end()) {
			find_flag = true;
			
			if (parent_list[temp_name] > 1) {
				for (i=2; i<parent_list[temp_name]; i++) {
					printf ("great ");
				}
				printf ("grand ");
			}
			printf ("child\n");
		}
		else {
			parent_count_2++;
			while (tree.find(temp_name) != tree.end()) {
				temp_name = tree[temp_name];
				if (parent_list.find(temp_name) != parent_list.end()) {
					find_flag = true;
					
					if (parent_list[temp_name] == 0) {
						if (parent_count_2 > 1) {
							for (i=2; i<parent_count_2; i++) {
								printf ("great ");
							}
							printf ("grand ");
						}
						printf ("parent\n");
					}
					else {
						k = min(parent_list[temp_name], parent_count_2);
						j = parent_list[temp_name] - parent_count_2;
						if (j < 0) j = -j;
						
						if (k == 1 && j == 0) {
							printf ("sibling\n");
						}
						else if (j == 0) {
							printf ("%d cousin\n", k-1);
						}
						else {
							printf ("%d cousin removed %d\n", k-1, j);
						}
					}
						
					break;
				}
				
				parent_count_2++;
			}
		}
		
		if (!find_flag)
			printf ("no relation\n");
	}
	
	return 0;
}