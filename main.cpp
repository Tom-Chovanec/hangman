#include <iostream>
#include <string>

using namespace std;

bool stringContainsChar(std::string str, char c);

int main() {
    string word = "apple";
    string guess = "";
    char tmp;
    while (guess != word)  {
        for (int i = 0; i < word.size(); i++) {
            if (!stringContainsChar(guess, word[i])) cout << "_";
            else cout << word[i];
        }
        cout << "     ";
        cin >> tmp;
        guess += tmp;

    }
    cout << "YOU WON";
}
bool stringContainsChar(std::string str, char c) {
    return str.find(c) != std::string::npos;
}