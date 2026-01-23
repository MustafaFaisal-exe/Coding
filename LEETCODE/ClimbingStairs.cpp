class Solution {
public:
    int climbStairs(int n) {
        int f = 0;
        int s = 1;
        for (int i = 0; i < n; ++i) {
            int tmp = s;
            s = f+s;
            f = tmp;
        }
        return s;
    }
};