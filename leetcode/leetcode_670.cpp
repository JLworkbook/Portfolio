class Solution {
public:
    int maximumSwap(int num) {
        char str[1000];
        sprintf (str, "%d", num);
        
        char max_char;
        int max_index;
        for (int i=0; i<strlen(str); i++) {
            max_char = '0';
            max_index = i;
            for (int j=i; j<strlen(str); j++) {
                if (max_char <= str[j]) {
                    max_char = str[j];
                    max_index = j;
                }
            }
            if (str[i] != str[max_index]) {
                swap (str[i], str[max_index]);
                break;
            }
        }
        
        return atoi(str);
    }
};