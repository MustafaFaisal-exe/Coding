class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int count = 0;
        vector<int> result;

        for (int i  = 0; i < nums.size(); ++i) {
            if (i != 0 && nums[i] > nums[i - 1]) {
                result.push_back(nums[i]);
                ++count;
            }

            if (i == 0) {
                result.push_back(nums[0]);
                ++count;
            }
        }

        nums = result;
        return count;
    }
};