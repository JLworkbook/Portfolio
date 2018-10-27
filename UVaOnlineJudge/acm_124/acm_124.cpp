#include <stdio.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void DFS ();

struct VARIABLE {
	int level;
	vector<char> lock;
	bool visit;
};

map<char, VARIABLE> variables;
vector<char> orders;

int main () {
	int i;
	
	string s;
	char c1, c2, input[300];
	stringstream ss;
	
	VARIABLE temp_variable;
	temp_variable.level = 0;
	temp_variable.visit = false;
	
	int count=0;
	
	while (fgets(input, 300, stdin) != NULL) {
		if (count != 0) {
			printf ("\n");
		}
		
		variables.clear();
		
		ss.str("");
		ss.clear();
		ss << string(input);
		while (ss >> c1) {
			variables[c1] = temp_variable;
		}
		
		fgets(input, 300, stdin);
		
		ss.str("");
		ss.clear();
		ss << string(input);
		while (ss >> c1 >> c2) {
			(variables[c1].lock).push_back(c2);
			variables[c2].level++;
		}
		
		DFS ();
		
		count++;
	}
	
	return 0;
}

void DFS () {
	int i;
	
	if (orders.size() == variables.size()) {
		for (i=0; i<orders.size(); i++) {
			printf ("%c", orders[i]);
		}
		printf ("\n");
		return;
	}
	
	map<char, VARIABLE>::iterator it;
	for (it=variables.begin(); it!=variables.end(); it++) {
		if ((it->second).visit == false && (it->second).level == 0) {
			(it->second).visit = true;
			for (i=0; i<((it->second).lock).size(); i++) {
				variables[((it->second).lock)[i]].level--;
			}
			orders.push_back(it->first);
			
			DFS ();
			
			orders.pop_back();
			for (i=0; i<((it->second).lock).size(); i++) {
				variables[((it->second).lock)[i]].level++;
			}
			(it->second).visit = false;
		}
	}
	
	return;
}