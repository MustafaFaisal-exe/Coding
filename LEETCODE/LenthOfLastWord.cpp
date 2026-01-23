class Solution {
public:
    int lengthOfLastWord(string s) {
        int index = s.length() - 1, length = 0;
        bool word_found = false;
        while (index > -1) {
            if (s[index] >= 'a' && s[index] <= 'z' || s[index] >= 'A' && s[index] <= 'Z') {
                length++;
                word_found = true;
            }
            if (word_found && s[index] == ' ') {
                break;
            }
            index--;
        }
        return length;
    }
};