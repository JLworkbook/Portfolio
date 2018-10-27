class Solution {
public:
    int maximumSwap(int num) {
        int num_list[10], index=0;
        while (num/10 > 0) {
            num_list[index++]= num%10;
            num /= 10;
        }
        num_list[index++]= num%10;

        int max_char;
        int max_index;
        for (int i=index-1; i>=0; i--) {
            max_char = 0;
            max_index = i;
            for (int j=i; j>=0; j--) {
                if (max_char <= num_list[j]) {
                    max_char = num_list[j];
                    max_index = j;
                }
            }
            if (num_list[i] != num_list[max_index]) {
                swap (num_list[i], num_list[max_index]);
                break;
            }
        }
        
        int sum=0;
        for (int i=0, k=1; i<index ;i++, k*=10){
            sum += num_list[i]*k;
        }
        
        return sum;
    }
};