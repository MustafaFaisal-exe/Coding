class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int count = 0;
        vector<int> result;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != val) {
                result.push_back(nums[i]);
                ++count;
            }
        }

        nums = result;
        return count;
    }
};