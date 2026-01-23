class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int return_abs = INT_MAX, current_abs;
        for (int i = 0; i < nums.size(); i++) {
            if (target == nums[i]) {
                current_abs = abs(i - start);
                if (current_abs < return_abs){
                    return_abs = current_abs;
                }
            }
        }
        return return_abs;
    }
};