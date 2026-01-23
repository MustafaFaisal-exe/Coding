#include <iostream>
using namespace std;

void generateCombinations(string str, int index, string current) {
    if (index == str.length()) {
        cout << "[" << current << "]" << endl;
        return;
    }
    
    // include
    generateCombinations(str, index + 1, current + str[index]);

    // exclude
    generateCombinations(str, index + 1, current);
}

int main() {
    string a = "abc";
    generateCombinations(a, 0, "");
    return 0;
}