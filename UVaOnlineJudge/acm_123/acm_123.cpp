#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <sstream>
using namespace std;

#define STRINGLENGTH 200 

int main () {
	int i, j;
	
	set<string> non_keywords;
	
	char str[STRINGLENGTH];
	while (scanf ("%s", str) != EOF) {
		if (strcmp(str, "::") == 0)
			break;
		
		non_keywords.insert(string(str));
	}
	fgets(str, STRINGLENGTH, stdin);
	
	stringstream ss;
	string s;
	string title_list[202][17];
	int title_num=0, word_num[202];
	while (fgets(str, STRINGLENGTH, stdin) != NULL) {
		s = string(str);
		transform(s.begin(), s.end(), s.begin(),::tolower);
		
		ss.str("");
		ss.clear();
		ss << s;
		word_num[title_num] = 0;
		while (ss >> s) {
			title_list[title_num][word_num[title_num]++] = s;
		}
		title_num++;
	}
	
	map<string, vector<int> > keywords;
	for (i=0; i<title_num; i++) {
		for (j=0; j<word_num[i]; j++) {
			if (non_keywords.find(title_list[i][j]) == non_keywords.end()) {
				keywords[title_list[i][j]].push_back(i);	
			}
		}
	}
	
	int title_index, repeat_count, temp_count;
	map<string, vector<int> >::iterator it;
	for (it=keywords.begin(); it!=keywords.end(); it++) {
		//printf ("%s", (it->first).c_str());
		for (i=0; i<(it->second).size(); i++) {
			title_index = (it->second)[i];
			temp_count = 0;
			if (i != 0 && title_index == (it->second)[i-1]) {
				repeat_count++;
			}
			else {
				repeat_count = 1;
			}
			
			for (j=0; j<word_num[title_index]; j++) {
				if (j != 0)
					printf (" ");
				
				if (title_list[title_index][j] == it->first) {
					temp_count++;
					if (temp_count == repeat_count) {
						s = title_list[title_index][j];
						transform(s.begin(), s.end(), s.begin(),::toupper);
						printf ("%s", s.c_str());
					}
					else {
						printf ("%s", title_list[title_index][j].c_str());
					}
				}
				else 
					printf ("%s", title_list[title_index][j].c_str());
			}
			printf ("\n");
		}
	}
	
	
	
	return 0;
}