#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <map>
#include <vector>
using namespace std;

struct Equation{
	int coefficient;
	int x_exponent;
	int y_exponent;
};

int translate_to_number (char temp_number_char[82], int &temp_index);
Equation translate_to_equation (int &temp_coefficient, int &temp_x_exponent, int &temp_y_exponent);
void put_char(char answer[2][82], int &index, int poi, char word);

int main () {
	char str[2][82];
	while (scanf ("%s", str[0]) != EOF) {
		if (str[0][0] == '#') {
			break;
		}
		
		scanf ("%s", str[1]);
		
		vector<Equation> equation[2];
		char temp_number_char[82];
		int temp_index=0, temp_coefficient, temp_x_exponent=0, temp_y_exponent=0;
		bool coefficient_flag=false, x_exponent_flag=false, y_exponent_flag=false, digit_flag=false;
		for (int i=0; i<2; i++) {
			for (int j=0; j<strlen(str[i]); j++) {
				if (str[i][j] == '+' || str[i][j] == '-') {
					if (x_exponent_flag) {
						temp_x_exponent = translate_to_number(temp_number_char, temp_index);
						x_exponent_flag = false;
					}
					else if (y_exponent_flag) {
						temp_y_exponent = translate_to_number(temp_number_char, temp_index);
						y_exponent_flag = false;
					}
					else if (temp_index != 0) {
						temp_coefficient = translate_to_number(temp_number_char, temp_index);
						coefficient_flag = true;
					}
					
					if (coefficient_flag) {
						equation[i].push_back (translate_to_equation(temp_coefficient, temp_x_exponent, temp_y_exponent) );
						coefficient_flag = false;
					}
					
					temp_number_char[temp_index++] = str[i][j];
				}
				else if (isdigit(str[i][j]) ) {
					temp_number_char[temp_index++] = str[i][j];
				}
				else if (str[i][j] == 'x' || str[i][j] == 'y') {
					if (!coefficient_flag) {
						temp_coefficient = translate_to_number(temp_number_char, temp_index);
						coefficient_flag = true;
					}
					
					if (str[i][j] == 'x') {
						if (y_exponent_flag) {
							temp_y_exponent = translate_to_number(temp_number_char, temp_index);
							y_exponent_flag = false;
						}
						x_exponent_flag = true;
					}
					else {
						if (x_exponent_flag) {
							temp_x_exponent = translate_to_number(temp_number_char, temp_index);
							x_exponent_flag = false;
						}
						y_exponent_flag = true;
					}
				}
			}
			
			if (x_exponent_flag) {
				temp_x_exponent = translate_to_number(temp_number_char, temp_index);
				x_exponent_flag = false;
			}
			else if (y_exponent_flag) {
				temp_y_exponent = translate_to_number(temp_number_char, temp_index);
				y_exponent_flag = false;
			}
			else if (temp_index != 0) {
				temp_coefficient = translate_to_number(temp_number_char, temp_index);
				coefficient_flag = true;
			}
			
			if (coefficient_flag) {
				equation[i].push_back (translate_to_equation(temp_coefficient, temp_x_exponent, temp_y_exponent) );
				coefficient_flag = false;
			}
		}
		
		/* x, y, coefficient */
		map<int, map<int, int> > result;
		for (int i=0; i<equation[0].size(); i++) {
			for (int j=0; j<equation[1].size(); j++) {
				temp_coefficient = equation[0][i].coefficient*equation[1][j].coefficient; 
				temp_x_exponent = equation[0][i].x_exponent+equation[1][j].x_exponent; 
				temp_y_exponent = equation[0][i].y_exponent+equation[1][j].y_exponent;
				
				if (result.find(temp_x_exponent) == result.end()) {
					result[temp_x_exponent][temp_y_exponent] = temp_coefficient;
				}
				else if (result[temp_x_exponent].find(temp_y_exponent) == result[temp_x_exponent].end()) {
					result[temp_x_exponent][temp_y_exponent] = temp_coefficient;
				}
				else {
					result[temp_x_exponent][temp_y_exponent] += temp_coefficient;
					if (result[temp_x_exponent][temp_y_exponent] == 0) {
						result[temp_x_exponent].erase(temp_y_exponent);
					}
				}
			}
		}
		
		char answer[2][82];
		int index=0;
		int first_flag=false;
		for (map<int, map<int, int> >::reverse_iterator rit=result.rbegin(); rit!=result.rend(); rit++) {
			for (map<int, int>::iterator it=(rit->second).begin(); it!=(rit->second).end(); it++) {
				/*
					printf ("%d, %d, %d\n", it->second, rit->first, it->first);
				*/
				if (it->second == 1) {
					if (first_flag) {
						put_char (answer, index, 0, ' ');
						put_char (answer, index, 1, '+');
						put_char (answer, index, 0, ' ');
					}
					if (rit->first == 0 && it->first == 0) {
						put_char (answer, index, 1, '1');
					}
					first_flag = true;
				}
				else if (it->second == -1) {
					if (first_flag) {
						put_char (answer, index, 0, ' ');
					}
					put_char (answer, index, 1, '-');
					if (first_flag) {
						put_char (answer, index, 0, ' ');
					}
					
					if (rit->first == 0 && it->first == 0) {
						put_char (answer, index, 1, '1');
					}
					first_flag = true;
				}
				else if (it->second > 0) {
					if (first_flag) {
						put_char (answer, index, 0, ' ');
						put_char (answer, index, 1, '+');
						put_char (answer, index, 0, ' ');
					}
					sprintf (temp_number_char, "%d", it->second);
					for (int i=0; i<strlen(temp_number_char); i++) {
						put_char (answer, index, 1, temp_number_char[i]);
					}
					first_flag = true;
				}
				else if (it->second < 0) {
					if (first_flag) {
						put_char (answer, index, 0, ' ');
						put_char (answer, index, 1, '-');
						put_char (answer, index, 0, ' ');
					}
					else {
						put_char (answer, index, 1, '-');
					}
					sprintf (temp_number_char, "%d", -it->second);
					for (int i=0; i<strlen(temp_number_char); i++) {
						put_char (answer, index, 1, temp_number_char[i]);
					}
					first_flag = true;
				}
				
				
				if (rit->first != 0) {
					put_char (answer, index, 1, 'x');
					
					if (rit->first != 1) {
						sprintf (temp_number_char, "%d", rit->first);
						for (int i=0; i<strlen(temp_number_char); i++) {
							put_char (answer, index, 0, temp_number_char[i]);
						}
					}
				}
				
				if (it->first != 0) {
					put_char (answer, index, 1, 'y');
					if (it->first != 1) {
						sprintf (temp_number_char, "%d", it->first);
						for (int i=0; i<strlen(temp_number_char); i++) {
							put_char (answer, index, 0, temp_number_char[i]);
						}
					}
				}
			}
		}
		if (!first_flag) {
			put_char (answer, index, 1, '0');
		}
		
		answer[0][index] = '\0';
		answer[1][index] = '\0';
		
		printf ("%s\n", answer[0]);
		printf ("%s\n", answer[1]);
	}
	
	return 0;
}

int translate_to_number (char temp_number_char[82], int &temp_index) {
	if (temp_index == 0 || (temp_index == 1 && (temp_number_char[0] == '+' || temp_number_char[0] == '-') ) ) {
		temp_number_char[temp_index++] = '1';
	}
	
	temp_number_char[temp_index++] = '\0';
	
	int temp_number = atoi(temp_number_char);
	temp_index = 0;
	
	return temp_number;
}

Equation translate_to_equation (int &temp_coefficient, int &temp_x_exponent, int &temp_y_exponent) {
	Equation temp_equation;
	temp_equation.coefficient= temp_coefficient;
	temp_equation.x_exponent= temp_x_exponent;
	temp_equation.y_exponent= temp_y_exponent;
	
	temp_coefficient = 1;
	temp_x_exponent = 0;
	temp_y_exponent = 0;
	
	return temp_equation;
}

void put_char(char answer[2][82], int &index, int poi, char word) {
	answer[poi][index] = word;
	answer[(poi+1)%2][index] = ' ';
	index++;
	
	return;
}
