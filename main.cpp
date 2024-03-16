#include <iostream>
#include <string>
#include <conio.h>
#include "render.cpp"

using namespace std;

bool stringContainsChar(std::string str, char c);

//TODO
//    load words from a file (english and slovak)
//    add logic for all the different menus
//    singleplayer/multiplayer mode
//
//

int main()
{
    system("chcp 65001");
    system("cls");
    string word = "qwe";
    string guess = "";
    string output = "";
    bool guessed = false;
    char tmp;
    int stage = 4;
    renderAscii(TITLE);
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
            renderAscii(VICTORY);
            _getch();
            return 0;
        }
        else if (stage > STAGE_10) {
            renderAscii(LOSS);
            _getch();
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
