class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        int temp = x;
        long long int rev_x = 0;
        while (temp != 0) {
            rev_x = rev_x*10 + temp % 10;
            temp /= 10;
        }
        if (x == rev_x) {
            return true;
        } else
            return false;
    }
};