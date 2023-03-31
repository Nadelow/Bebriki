// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "Translator.h"

int main()
{
    std::string filename;

    while (filename.empty())
    {
        std::cout << "Enter file name: ";
        std::cin >> filename;
    }
    std::cout << "\n";

    Translator trans;
    trans.GetLexems(filename, false);

    return 0;
}