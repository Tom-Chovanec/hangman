#include <iostream>
#include <string>
#include <conio.h>
#include "render.cpp"
#include "Wlist.cpp"

using namespace std;

bool stringContainsChar(std::string str, char c);
bool isLetter(char c);

enum language {
    EN,
    SK
};

int main() {
    system("chcp 65001");
    system("cls");
    string guess = "";
    string output = "";
    string word = "";
    language lang = EN;
    bool guessed = false;
    char tmp;
    int stage = STAGE_1;

    renderAscii(TITLE);
    if (lang == EN) cout << "press ANY BUTTON to start\n";
    else cout << "stlačte ľubovolnú klávesu pre začatie\n";

    _getch();
    system("cls");

    while (true) {
        cout << "choose a language(e/s)\n";
        tmp = _getch();
        if (tmp == 'e') lang = EN;
        else if (tmp == 's') lang = SK;
        else continue;

        if (lang == EN) word = NahodneSlovo(nacitajSlova("data/words.txt"));
        else word = NahodneSlovo(nacitajSlova("data/slova.txt"));
        
        while(!guessed) {
            guessed = true;
            for (int i = 0; i < word.size(); i++) {
                if (!stringContainsChar(guess, word[i])) {
                    guessed = false;
                    output += '_';
                }
                else output += word[i];
            }
            if (guessed) {
                if (lang == EN) renderAscii(VICTORY_EN);
                else renderAscii(VICTORY_SK);
                break;
            }
            else if (stage > STAGE_10) {
                if (lang == EN) renderAscii(LOSS_EN);
                else renderAscii(LOSS_SK);
                break;
            }

            do {
                renderAscii(stage);
                cout << output;
                tmp = _getch();
                system("cls");

                if (stringContainsChar(guess, tmp)) {
                    if (lang == EN) cout << "You already guessed that letter\n";
                    else cout << "Už si hádal toto písmeno\n";
                } 
                else if (isLetter(tmp)) continue;
                else break;
            } while (stringContainsChar(guess, tmp));

            if (!stringContainsChar(word, tmp)) stage++;
            guess += tmp;
            output = "";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        if (lang == EN) {
            cout << "The word was: " << word << "\n";
            cout << "Do you want to play again? (y/n)\n";
        } else {
            cout << "Slovo bolo: " << word << "\n";
            cout << "Chcete hrať znova? (y/n)\n";
        }
        
        while (true) {
            tmp = _getch();
            if (tmp == 'n') return 0;
            else if (tmp == 'y') {
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

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
