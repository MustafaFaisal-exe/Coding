class Solution {
public:
    int maximizeSum(vector<int>& nums, int k) {
        int max = *max_element(nums.begin(), nums.end());
        int total = 0;
        return (k / 2.0) * (2*max + k - 1);
    }
};