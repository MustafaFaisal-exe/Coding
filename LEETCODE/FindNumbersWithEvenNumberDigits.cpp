class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int temp, digits, counter = 0;
        for (int i = 0; i < nums.size(); i++) {
            temp = nums[i];
            digits = 0;
            while (temp != 0) {
                digits++;
                temp /= 10;
            }
            if (digits % 2 == 0) {
                counter++;
            }
        }
        return counter;
    }
};