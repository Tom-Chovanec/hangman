#include <iostream>
#include <string>
#include <conio.h>
#include "render.cpp"
#include "Wlist.cpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;

bool stringContainsChar(std::string str, char c);
bool isLetter(char c);

enum language {
    EN,
    SK
};

enum playmode {
    SINGLEPLAYER,
    MULTIPLAYER
};

int main() {
    system("chcp 65001");
    system("cls");
    string guess = "";
    string output = "";
    playmode mode = SINGLEPLAYER;
    int base = 5;
    HangmanStage menuStage = static_cast<HangmanStage>(base);
    string word = "";
    language lang = EN;
    bool guessed = false;
    bool isRunning = true;
    char tmp;
    int stage = STAGE_1;
    int x = 0;

    renderAscii(TITLE);
 
   system("cls");
    while (isRunning) {
        while (isRunning) {
            system("cls");
            renderAscii(menuStage);
            tmp = _getch();
            if (tmp == '\r') {
                if (menuStage == TITLE_EN_PLAY || menuStage == TITLE_SK_PLAY) break;
                if (menuStage == TITLE_EN_QUIT || menuStage == TITLE_SK_QUIT) {
                    isRunning = false;
                    break;
                }
            }
            if (GetAsyncKeyState(VK_RIGHT)) {
                x++;
                if (x == 3) x = 0;
                menuStage = static_cast<HangmanStage>(base + x);
            }
            if (GetAsyncKeyState(VK_LEFT)) {
                x--;
                if (x == -1) x = 2;
                menuStage = static_cast<HangmanStage>(base + x);
            }
        }
        if (!isRunning) break;
        if (mode == MULTIPLAYER) {
            cout << "Ent;er a word: ";
            cin >> word;
            system("cls");
        }
        else {
            if (lang == EN) word = NahodneSlovo(nacitajSlova("data/words.txt"));
            else word = NahodneSlovo(nacitajSlova("data/slova.txt"));
        }
        
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
            } else if (stage > STAGE_10) {
                if (lang == EN) renderAscii(LOSS_EN);
                else renderAscii(LOSS_SK);
                break;
            }

            do {
                renderAscii(stage);
                cout << output;
                tmp = _getch();
                system("cls");

                if (!isLetter(tmp)) continue;
                else if (stringContainsChar(guess, tmp)) {
                    if (lang == EN) cout << "You already guessed that letter\n";
                    else cout << "Už si hádal toto písmeno\n";
                } 
                else break;
            } while (stringContainsChar(guess, tmp));

            if (!stringContainsChar(word, tmp)) stage++;
            guess += tmp;
            output = "";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        guessed = false;
        stage = STAGE_1;
        guess = "";
        output = "";
        x = 0;
        system("cls");
    }
}


bool stringContainsChar(string str, char c) {
    return str.find(c) != string::npos;
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
