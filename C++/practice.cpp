#include<iostream>
#include<cmath>
using namespace std;

bool isPrime(int n) {
    if (n <= 1)
        return false;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int digitSum(int n, int power) {
    int sum = 0;
    while (n > 0) {
        sum += pow(n % 10, power);
        n /= 10;
    }
    return sum;
}

void luckyNumber(int a, int b) {
    int total1 = 0;
    int total2 = 0;
    for (int i = a; i <= b; i++)
    {
        total1 = digitSum(i, 1);
        total2 = digitSum(i, 2);

        if (isPrime(total1) && isPrime(total2)) {
            cout << i << " ";
        }
    }
}

int main() {
    luckyNumber(120, 130);
}