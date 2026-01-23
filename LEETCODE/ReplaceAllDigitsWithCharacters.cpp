class Solution {
public:
    string replaceDigits(string s) {
        for (int i = 1; i < s.length(); i++) {
            if (i % 2 == 1) {
                s[i] = char(int(s[i - 1]) + int(s[i] - '0'));
            }
        }
        return s;
    }
};