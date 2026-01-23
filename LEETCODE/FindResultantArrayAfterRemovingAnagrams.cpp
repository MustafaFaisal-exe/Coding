class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        string temp1, temp2;
        for (int i = 0; i < words.size() - 1; i++) {
            temp1 = "";
            temp2 = "";
            if (words[i].length() == words[i + 1].length()) {
                temp1 = words[i];
                temp2 = words[i + 1];
                sort(temp1.begin(), temp1.end());
                sort(temp2.begin(), temp2.end());
                if (temp1 == temp2) {
                    words.erase(words.begin() + i + 1);
                    i--;
                }
            }
        }
        return words;
    }
};