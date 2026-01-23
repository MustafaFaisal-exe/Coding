class Solution {
public:
    int sumBase(int n, int k) {
        int base = 0;
        if (k != 10){
            for (int counter = 0; n != 0; counter++) {
                base += n % k * pow(10, counter);
                n /= k;
            }
        } else {
            base = n;
        }

        int sumbase = 0;
        while (base != 0) {
            sumbase += base % 10;
            base /= 10;
        }
        return sumbase;
    }
};