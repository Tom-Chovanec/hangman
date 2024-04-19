#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

std::vector<std::string> nacitajSlova(const std::string& subor) {
    std::ifstream infile(subor);
    std::vector<std::string> slova;
    std::string slovo;
    while (infile >> slovo) {
        slova.push_back(slovo);
    }
    return slova;
}

std::string NahodneSlovo(std::vector<std::string> slova, int difficulty) {
    std::vector<std::string> filteredWords;

    for (const auto& word : slova) {
        if (difficulty == 0) {
            if (word.length() <= 5) {
                filteredWords.push_back(word);
            }
        } else 
        if (difficulty == 1) {
            if (word.length() >= 5) {
                filteredWords.push_back(word);
            }
        }
    }
    srand(time(0));
    int randomIndex = rand() % filteredWords.size();
    return filteredWords[randomIndex];

}
