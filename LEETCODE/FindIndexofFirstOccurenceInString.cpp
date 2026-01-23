class Solution {
public:
    int strStr(string haystack, string needle) {
        int l = 0;
        int r = needle.length() - 1;

        bool found = false;
        while (r < haystack.length()) {
            for (int i = l; i <= r; ++i) {
                if (haystack[i] != needle[i - l]) {
                    found = false;
                    break;
                } else {
                    found = true;
                }
            }
            if (found) {
                return l;
            } else {
                l++;
                r++;
            }
        }
        return -1;
    }
};