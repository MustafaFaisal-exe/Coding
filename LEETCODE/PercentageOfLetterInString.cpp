class Solution {
public:
    int percentageLetter(string s, char letter) {
        double count = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == letter) {
                count++;
            }
        }
        return (count / s.length()) * 100;
    }
};