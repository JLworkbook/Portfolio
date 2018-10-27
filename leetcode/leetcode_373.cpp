class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int> > sort_list;
        for (int i=0; i<nums1.size(); i++) {
            for (int j=0; j<nums2.size(); j++) {
                sort_list.push_back(make_pair(nums1[i], nums2[j]));
            }
        }
        
        sort (sort_list.begin(), sort_list.end(), my_cmp);
        
        if (sort_list.size() < k)
            k = sort_list.size();
        vector<pair<int, int> > answer_list;
        for (int i=0; i<k; i++) {
            answer_list.push_back(sort_list[i]);
        }
        
        return answer_list;
    }
    
    static bool my_cmp (pair<int, int> a, pair<int, int> b) {
        return (a.first+a.second) < (b.first+b.second);
    }
};