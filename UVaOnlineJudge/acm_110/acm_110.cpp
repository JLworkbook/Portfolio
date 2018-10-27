#include <stdio.h>
#include <vector>
using namespace std;

char alphabet[10]={'a','b','c','d','e','f','g','h','i','j'};
void print_tab (int level);
void generate_if_else (int n, int level, vector<char> element_list);
void generate_code (int n);

int main () {
	int i;
	
	int M, n;
	scanf ("%d", &M);
	for (i=0; i<M; i++) {
		scanf ("%d", &n);
		generate_code (n);
		
		if (i != M-1)
			printf ("\n");
	}
	
	return 0;
}

void print_tab (int level) {
	int i;
	
	for (i=0; i<level; i++) {
		printf ("\t");
	}
	
	return;
}

void generate_if_else (int n, int level, vector<char> element_list) {
	int i;
	
	if (level == n) {
		print_tab (level);
		printf ("writeln(");
		for (i=0; i<n; i++) {
			if (i != 0)
				printf (",");
			printf ("%c", element_list[i]);
		}
		printf (")\n");
		
		return;
	}
	
	print_tab (level);
	printf ("if %c < %c then\n", element_list[level-1], element_list[level]);
	generate_if_else (n, level+1, element_list);
	
	swap (element_list[level-1], element_list[level]);
	for (i=0; i<level-1; i++) {
		print_tab (level);
		printf ("else if %c < %c then\n", element_list[level-(i+2)], element_list[level-(i+1)]);
		generate_if_else (n, level+1, element_list);
		
		swap (element_list[level-(i+2)], element_list[level-(i+1)]);
	}
	
	print_tab (level);
	printf ("else\n");
	generate_if_else (n, level+1, element_list);
	
	return;
}

void generate_code (int n) {
	int i;
	
	printf ("program sort(input,output);\n");
	printf ("var\n");
	
	for (i=0; i<n; i++) {
		if (i != 0)
			printf (",");
		printf ("%c", alphabet[i]);
	}
	printf (" : integer;\n");
	printf ("begin\n");
	printf ("\treadln(");
	for (i=0; i<n; i++) {
		if (i != 0)
			printf (",");
		printf ("%c", alphabet[i]);
	}
	printf (");\n");
	
	vector<char> element_list;
	for (i=0; i<n; i++) {
		element_list.push_back(alphabet[i]);
	}
	generate_if_else (n, 1, element_list);
	
	printf ("end.\n");
	
	return;
}
