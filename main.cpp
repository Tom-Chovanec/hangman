#include <iostream>
#include <string>
#include <conio.h>
#include "render.cpp"
#include "Wlist.cpp"
#include "a.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;

bool stringContainsChar(std::string str, char c);
bool isLetter(char c);
void clearConsole();

enum language {
    EN = 2,
    SK = 12
};

enum playmode {
    SINGLEPLAYER,
    MULTIPLAYER
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    clearConsole();
    string guess = "";
    string output = "";
    playmode mode = SINGLEPLAYER;
    int difficulty = 0;
    int base = EN;
    int total = 0;
    int correct = 0;
    HangmanStage menuStage = static_cast<HangmanStage>(base);
    string word = "";
    bool guessed = false;
    bool isRunning = true;
    char tmp;
    int stage = STAGE_1;
    int x = 0, y = 0;
    float z = 0.0f;

    renderAscii(TITLE);
 
   clearConsole();
    while (isRunning) {
        while (isRunning) {
            clearConsole();
            renderAscii(menuStage);
            if (word != "") {
                if (base == EN) cout << "Last word was: " << word;
                else cout << "Posledné Slovo bolo:"  << word << endl;
            } 
            cout << "                        Score: " << correct << "/" << total << endl;
            tmp = _getch();
            if (tmp == '\r') {
                if (menuStage == TITLE_EN_PLAY || menuStage == TITLE_SK_PLAY) break;
                if (menuStage == TITLE_EN_QUIT || menuStage == TITLE_SK_QUIT) {
                    isRunning = false;
                    break;
                }
                if (menuStage == TITLE_EN_SETTINGS || menuStage == TITLE_SK_SETTINGS) {
                    menuStage = static_cast<HangmanStage>(3 + base);
                    x = 0;
                }
            }
            if (menuStage == TITLE_EN_PLAY || menuStage == TITLE_SK_PLAY || menuStage == TITLE_EN_QUIT || menuStage == TITLE_SK_QUIT || menuStage == TITLE_EN_SETTINGS || menuStage == TITLE_SK_SETTINGS) {
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
            } else {
                if (tmp == '\r') {
                    if (menuStage == SETTINGS_EN_PLAY_SP || menuStage == SETTINGS_SK_PLAY_SP) mode = SINGLEPLAYER;
                    if (menuStage == SETTINGS_EN_PLAY_MP || menuStage == SETTINGS_SK_PLAY_MP) mode = MULTIPLAYER;
                    if (menuStage == SETTINGS_EN_LANG_EN || menuStage == SETTINGS_SK_LANG_EN)  {
                        base = EN;
                        menuStage = static_cast<HangmanStage>(base + 6);
                    }
                    if (menuStage == SETTINGS_EN_LANG_SK || menuStage == SETTINGS_SK_LANG_SK) {
                        base = SK;
                        menuStage = static_cast<HangmanStage>(base + 5);
                    }

                    if (menuStage == SETTINGS_EN_DIFF_EASY || menuStage == SETTINGS_SK_DIFF_EASY) difficulty = 0;
                    if (menuStage == SETTINGS_EN_DIFF_HARD || menuStage == SETTINGS_SK_DIFF_HARD) difficulty = 1;
                    if (menuStage == SETTINGS_EN_EXIT || menuStage == SETTINGS_SK_EXIT) {
                        menuStage = static_cast<HangmanStage>(static_cast<int>(menuStage) - 9);  
                        y = 0;
                    }   
                }
                if (GetAsyncKeyState(VK_RIGHT)) {
                    y++;
                    if (y == 7 ) y = 0;
                    menuStage = static_cast<HangmanStage>(base + 3 + y);
                }
                if (GetAsyncKeyState(VK_LEFT)) {
                    y--;
                    if (y == -1) y = 6;
                    menuStage = static_cast<HangmanStage>(base + 3 + y);
                }
                if (GetAsyncKeyState(VK_UP)) {
                    y -= 2;
                    if (y < 0) y = 6;
                    menuStage = static_cast<HangmanStage>(base + 3 + y);
                }
                if (GetAsyncKeyState(VK_DOWN)) {
                    y += 2;
                    if (y == 7) y = 6;
                    if (y > 7) y = 0;
                    menuStage = static_cast<HangmanStage>(base + 3 + y);
                }

            }

        }
        if (!isRunning) break;
        if (mode == MULTIPLAYER) {
            cout << "Enter a word: ";
            cin >> word;
        } else {
            if (base == EN) word = NahodneSlovo(nacitajSlova("data/words.txt"), difficulty);
            else word = NahodneSlovo(nacitajSlova("data/slova.txt"), difficulty);
        }
        
        clearConsole();
        total++;
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
                if (base == EN) renderAscii(VICTORY_EN);
                else renderAscii(VICTORY_SK);
                correct++;
                break;
            } else if (stage > STAGE_10) {
                if (base == EN) renderAscii(LOSS_EN);
                else renderAscii(LOSS_SK);
                break;
            }

            do {
                renderAscii(stage);
                cout << output;
                tmp = _getch();
                clearConsole();

                if (!isLetter(tmp)) continue;
                else if (stringContainsChar(guess, tmp)) {
                    if (base == EN) cout << "You already guessed that letter\n";
                    else cout << "Už si hádal toto písmeno\n";
                } 
                else break;
            } while (stringContainsChar(guess, tmp));

            if (difficulty == 0)  {
                if (!stringContainsChar(word, tmp)) 
                    stage++;
            } else if (!stringContainsChar(word, tmp)) 
                z += 1.5f;
                stage = STAGE_1 + static_cast<int>(z);
            guess += tmp;
            output = "";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        guessed = false;
        stage = STAGE_1;
        guess = "";
        output = "";
        x = 0;
        clearConsole();
    }
}


bool stringContainsChar(string str, char c) {
    return str.find(c) != string::npos;
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void clearConsole() {
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    SetConsoleCursorPosition( hStdOut, homeCoords );
}