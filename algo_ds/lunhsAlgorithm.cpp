#include <iostream>
#include <string>
using namespace std;

int checkLunh(string creditCardNumToCheck) {
    int numOfDigits = creditCardNumToCheck.length();
    int sum = (int) creditCardNumToCheck.at(numOfDigits-1);
    int parity = numOfDigits % 2;

    for (int i = 0; i < numOfDigits - 2; i++) {
        int digit = (int) creditCardNumToCheck.at(i);
        if ((i % 2) == parity) {
            digit = digit * 2;
        }
        if (digit > 9) {
            digit = digit - 9;
        }
        sum = sum + digit;
    }
    return (sum % 10) == 0;
}

int main() {
    // fake credit numbers
    string jcb = "3566002020360505";
    cout << checkLunh(jcb) << "\n";
    string mastercard = "5105105105105100";
    cout << checkLunh(mastercard) << "\n";
    string visa = "4111111111111111";
    cout << checkLunh(visa) << "\n";
    string discover = "6011000990139424";
    cout << checkLunh(discover) << "\n";
    string ccToFail = "78423908234709";
    cout << checkLunh(ccToFail) << "\n";

    return 0;
}