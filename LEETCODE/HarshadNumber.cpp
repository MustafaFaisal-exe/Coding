class Solution {
public:
    int sumOfTheDigitsOfHarshadNumber(int x) {
        int temp = x;
        int sum_digit = 0;
        while (temp != 0) {
            sum_digit += temp % 10;
            temp /= 10;
        }
        if (x % sum_digit == 0) {
            return sum_digit;
        } else{
            return -1;
        }
    }
};