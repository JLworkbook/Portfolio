class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int temp_length=0;
        vector<int> subarray;
        int sum=0;
        bool first_flag = true;
        for (int i=0; i<nums.size(); i++) {
            if (first_flag) {
                sum += nums[i];
                subarray.push_back(nums[i]);
            }
            else {
                sum -= subarray.front();
                subarray.erase (subarray.begin());
                sum += nums[i];
                subarray.push_back(nums[i]);
            }
            
            if (sum >= s) {
                first_flag = false;
                
                while (sum-subarray.front() >= s) {
                    sum -= subarray.front();
                    subarray.erase (subarray.begin());
                }
            }
            
            if (!first_flag && subarray.size() == 1)
                return 1;
        }
        
        if (first_flag)
            return 0;
        else
            return subarray.size();
    }
};