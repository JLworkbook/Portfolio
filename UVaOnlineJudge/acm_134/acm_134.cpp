/* 本程式參考 http://www.cnblogs.com/devymex/archive/2010/08/23/1805874.html */

#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

enum SYMBOL {A, MOD, LA, BA, DA, PREDA, NAM, SE, PC, P, PN, PS, ST, VP, PV, UN};
bool is_vowel[26] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

/* 狀態轉換表 {初始符號, 前綴符號, 後綴符號, 推導符號} */
static SYMBOL convert_table[14][4] = {{PREDA, UN, PREDA, PREDA}, {PREDA, UN, UN, PS}, {NAM, UN, UN, PN},
	{LA, UN, PS, PN}, {MOD, UN, PS, VP}, {A, PS, PS, PS}, {PS, UN, UN, P}, {DA, UN, P, PC},
	{BA, PN, P, PC}, {VP, PN, UN, PV}, {PV, UN, PN, ST}, {PV, UN, UN, ST}, {PC, UN, UN, SE}, {ST, UN, UN, SE}};

SYMBOL wordsToSymbol (char str[100]);	
	
int main () {
	vector<SYMBOL> sentence; 
	char str[100];
	bool is_end = false;
	while (scanf ("%s", str) != EOF) {
		if (strcmp (str, "#") == 0)
			break;
		
		int len = strlen(str);
		if (str[len-1] == '.') {
			is_end = true;
			str[len-1] = '\0';
		}
		sentence.push_back(wordsToSymbol(str));
		
		if (is_end) {
			for (int i=0; i<14; i++) {
				int j=0;
				while (j < sentence.size()) {
					if (sentence[j] != convert_table[i][0]) j++;
					else if (convert_table[i][1] != UN && (j == 0 || sentence[j-1] != convert_table[i][1]) ) j++;
					else if (convert_table[i][2] != UN && (j == sentence.size()-1 || sentence[j+1] != convert_table[i][2]) ) j++;
					else {
						if (convert_table[i][2] != UN) 
							sentence.erase(sentence.begin()+(j+1) );
						sentence[j] = convert_table[i][3];
						if (convert_table[i][1] != UN) 
							sentence.erase(sentence.begin()+(j-1) );
					}
				}
			}
			if (sentence.size() == 1 && sentence[0] == SE)
				printf ("Good\n");
			else
				printf ("Bad!\n");
			
			sentence.clear();
			is_end = false;
		}
	}

	return 0;
}

SYMBOL wordsToSymbol (char str[100]) {
	int len = strlen(str);
	if (!is_vowel[str[len-1]-'a'])
		return NAM;
	
	switch (len) {
		case 1: return A;
		case 2: 
			switch (str[0]) {
				case 'g': return MOD;
				case 'b': return BA;
				case 'd': return DA;
				case 'l': return LA;
			}
		
		/* 還是要檢查有沒有符合CCVCV 或 CVCCV的格式 */
		case 5: 
			if (!is_vowel[str[0]-'a'] && !is_vowel[str[1]-'a'] && is_vowel[str[2]-'a'] && !is_vowel[str[3]-'a']) return PREDA;
			else if (!is_vowel[str[0]-'a'] && is_vowel[str[1]-'a'] && !is_vowel[str[2]-'a'] && !is_vowel[str[3]-'a']) return PREDA;
			else return UN;
	}
	
	return UN;
}