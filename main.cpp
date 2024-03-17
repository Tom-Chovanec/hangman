#include <iostream>
#include <string>
#include <conio.h>
#include "render.cpp"
#include "Wlist.cpp"

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
    string guess = "";
    string output = "";
    bool guessed = false;
    char tmp;
    int stage = 4;
    renderAscii(TITLE);
    cout << "press ANY BUTTON to start\n";
    _getch();
    system("cls");
    while (true) {
        string word = NahodneSlovo(nacitajSlova("data/slova.txt"));
        while(!guessed) {
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
            if (guessed) {
                renderAscii(VICTORY);
                break;
            }
            else if (stage > STAGE_10) {
                renderAscii(LOSS);
                break;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << "\nThe word was: " << word << "\n";
        cout << "Do you want to play again? (y/n)\n";
        while (true) {
            tmp = _getch();
            if (tmp == 'n') return 0;
            else if (tmp == 'y'){
                guessed = false;
                stage = STAGE_1;
                guess = "";
                output = "";
                system("cls");
                break;
            }
        }
        
    }
}


bool stringContainsChar(string str, char c) {
    return str.find(c) != string::npos;
}
