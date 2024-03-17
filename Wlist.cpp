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

std::string NahodneSlovo(const std::vector<std::string>& zoznam) {
    srand(time(NULL));
    int index = rand() % zoznam.size();
    return zoznam[index];
}
