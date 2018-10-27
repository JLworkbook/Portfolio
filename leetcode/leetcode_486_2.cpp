class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int len = nums.size();
        
        int dp[len][len];
        for (int i=0; i<len; i++) {
            dp[i][i] = nums[i];
        }
        
        for (int i=len-1; i>0; i--) {
            for (int j=0; j<i; j++) {
                dp[j][j+len-i] = max(dp[j][j]-dp[j+1][j+len-i], dp[j+len-i][j+len-i]-dp[j][j+len-i-1]);
            }
        }
        return (dp[0][len-1]>=0);
    }
};