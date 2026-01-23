class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int highest;
        for (int i = 0; i < arr.size(); i++) {
            highest = 0;
            for (int j = i + 1; j < arr.size(); j++) {
                if (arr[j] > highest) {
                    highest = arr[j];
                }
            }
            if (highest == 0) {
                arr[i] = -1;
            } else {
                arr[i] = highest;
            }
        }
        return arr;
    }
};