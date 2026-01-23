class Solution {
public:
    vector<int> sumZero(int n) {
        const int size = n;
        vector<int> arr(n);;
        for (int i = 0; i < n / 2; i++) {
            arr[i] = -1*(i + 1);
            arr[n - i - 1] = i + 1;
        }
        return arr;
    }
};