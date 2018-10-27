class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        string number="";
        
        long long int new_numerator, new_denominator;
        new_numerator = numerator;
        new_denominator = denominator;
        
        bool positive_flag=true;
        if (new_numerator < 0 && new_denominator < 0) {
            new_numerator = -new_numerator;
            new_denominator = -new_denominator;
        }
        else if (new_numerator < 0) {
            new_numerator = -new_numerator;
            positive_flag = false;
        }
        else if (new_denominator < 0) {
            new_denominator = -new_denominator;
            positive_flag = false;
        }
        
        if (numerator != 0 && !positive_flag) {
            number += "-";
        }
        
        long long int quotient, remainder;
        quotient = new_numerator/new_denominator;
        remainder = new_numerator%new_denominator;
        
        number += to_string(quotient); 
        
        map<pair<int, int>, int> remainder_list;
        int index = number.size();
        if (remainder != 0) {
            number += ".";
            while (remainder != 0) {
                index++;
                quotient = (remainder*10)/new_denominator;
                remainder = (remainder*10)%new_denominator;
                
                pair<int, int> temp_pair(quotient, remainder);
                if (remainder_list.find(temp_pair) == remainder_list.end()) {
                    remainder_list[temp_pair] = index;
                    number += to_string(quotient);
                }
                else {
                    number.insert(remainder_list[temp_pair], "(");
                    number += ")";
                    break;
                }
            }
        }
        
        return number;
    }
};