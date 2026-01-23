class Solution {
public:
    bool checkIfPangram(string sentence) {
        int ch_arr[26] = {0};
        for (int i = 0; i < sentence.length(); i++) {
            ch_arr[int(sentence[i]) - 97]++;
        }
        for (int j = 0; j < sizeof(ch_arr)/sizeof(ch_arr[0]); j++) {
            if (ch_arr[j] == 0){
                return false;
            }
        }
        return true;
    }
};