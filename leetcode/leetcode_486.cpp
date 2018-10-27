class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int score=0;
        map<int, map<int, int> > record;
        score = pickOne(nums, 0, nums.size()-1, record);
        return (score >= 0)? true: false;
    }
    int pickOne(vector<int>& nums, int left, int right, map<int, map<int, int> >& record) {
        if (record.find(left) != record.end() && record[left].find(right) != record[left].end()) {
            return record[left][right];
        }
        
        if (right-left > 2) {
            record[left][right] = max(nums[left]-pickOne(nums, left+1, right, record) , nums[right]-pickOne(nums, left, right-1, record));
        }
        else if (right-left == 2) {
            int temp = min(nums[left], nums[right]);
            record[left][right] = max(nums[left], nums[right])-abs(nums[left+1]-temp);
        }
        else if (right-left == 1) {
            record[left][right] = abs(nums[left]-nums[right]);
        } 
        else {
            record[left][right] = nums[left];
        }
        return record[left][right];
    }
};