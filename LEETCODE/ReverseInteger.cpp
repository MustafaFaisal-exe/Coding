class Solution {
public:
    signed int reverse(signed long int x) {
        //Queue
        queue<signed long int> stack;
        int count = 0;
        while (x != 0) {
            stack.push(x % 10);
            x /= 10;
            count++;
        }
        count--;
        signed long int result = 0;
        while (!stack.empty()) {
            result += stack.front() * pow(10, count--);
            stack.pop();
        }
        if (result > 2147483647 || result < -2147483648) {
            return 0;
        }
        return result;
    }
};