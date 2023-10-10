#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

bool isProhibited(const string& password) {
    vector<string> prohibitedWords = {"password", "admin", "123456", "qwerty", "letmein", "welcome"};

    for (const string& word : prohibitedWords) {
        if (password.find(word) != string::npos) {
            return true;
        }
    }
    return false;
}

string getPassword(int length) {
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    int charSize = characters.size();
    random_device rd;
    mt19937 gen(rd());

    string password = "";

    uniform_int_distribution<> distribution(0, charSize - 1);

    do {
        password.clear();

        for (int i = 0; i < length; i++) {
            int randomIndex = distribution(gen);
            password += characters[randomIndex];
        }
    } while (isProhibited(password));

    return password;
}

bool isStrongPassword(const string& password) {
    const int minLength = 8;
    const bool hasUppercase = any_of(password.begin(), password.end(), ::isupper);
    const bool hasLowercase = any_of(password.begin(), password.end(), ::islower);
    const bool hasDigit = any_of(password.begin(), password.end(), ::isdigit);
    const bool hasSpecialChar = password.find_first_of("!@#$%^&*") != string::npos;

    return (password.length() >= minLength) &&
           hasUppercase && hasLowercase && hasDigit && hasSpecialChar;
}

int main() {
    int length = 16;
    string password;

    do {
        password = getPassword(length);
    } while (!isStrongPassword(password));

    cout << "Generated Password: " << password << endl;

    if (isProhibited(password)) {
        cout << "The generated password contains prohibited words or patterns. Please try again." << endl;
    } else {
        cout << "This is a strong password." << endl;
    }

    return 0;
}