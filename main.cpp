#include <iostream>
#include <string>
#include <conio.h>
#include "render.cpp"

using namespace std;

bool stringContainsChar(std::string str, char c);

int main()
{
    system("chcp 65001");
    system("cls");
    string word = "apple";
    string guess = "";
    string output = "";
    bool guessed = false;
    char tmp;
    int stage = 4;
    renderAscii(TITLE_TEXT);
    cout << "press ANY BUTTON to start\n";
    _getch();
    system("cls");
    while (!guessed) {
        guessed = true;
        for (int i = 0; i < word.size(); i++) {
            if (!stringContainsChar(guess, word[i]))
            {
                guessed = false;
                output += '_';
            }
            else
                output += word[i];
        }
        cout << "\n";
        if (guessed) {
            cout << "YOU WON!";
            return 0;
        }
        else if (stage > STAGE_10) {
            cout << "YOU LOST!";
            return 0;
        }
        

        do {
            renderAscii(stage);
            cout << output;
            tmp = _getch();
            system("cls");
            if (stringContainsChar(guess, tmp)) 
                cout << "You already guessed that letter\n";
            else break;
        } while (stringContainsChar(guess, tmp));

        if (!stringContainsChar(word, tmp))
            stage++;
        guess += tmp;
        output = "";
    }
}


bool stringContainsChar(string str, char c) {
    return str.find(c) != string::npos;
}