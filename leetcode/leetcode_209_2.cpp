class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int min_length=INT_MAX;
        int sum=0;
        int left=0;
        for (int i=0; i<nums.size(); i++) {
            sum += nums[i];
            while (sum >= s) {
                min_length = min(min_length, i+1-left);
                sum -= nums[left++];
            }
        }
        
        return (min_length != INT_MAX)? min_length: 0;
    }
};