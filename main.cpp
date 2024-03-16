#include <iostream>
#include <string>
#include <conio.h>
#include "render.cpp"

using namespace std;

bool stringContainsChar(std::string str, char c);

int main() {
    renderAscii(1);
    cout << "press ANY BUTTON to start\n";
    _getch();
    string word = "apple";
    string guess = "";
    bool guessed = false;
    char tmp;
    while (!guessed)  {
        guessed = true;
        for (int i = 0; i < word.size(); i++) {
            if (!stringContainsChar(guess, word[i])) {
                guessed = false;
                cout << "_";
            }
            else cout << word[i];
        }
        if (guessed) {
            cout << "\nYOU WON!";
            return 0;
        }
        char tmp = _getch();
        cout << "\n";
        guess += tmp;

    }
}
bool stringContainsChar(std::string str, char c) {
    return str.find(c) != std::string::npos;
}