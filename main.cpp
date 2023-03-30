#include <iostream>
#include "LexemBlock.h"

int main()
{
    std::string filename;

    while (filename.empty())
    {
        std::cout << "Enter file name: ";
        std::cin >> filename;
    }
    std::cout << "\n";

    LexemBlock lexer;
    std::vector<Token> lexems(lexer.Run(filename));

    if(!lexems.empty())
        for (int i = 0; i < lexems.size() - 1; i++)
            if (lexems[i].lexem_type != "rem_cont")
                std::cout << lexems[i].m_line << '\t' << lexems[i].lexem_type << '\t' << lexems[i].lexem_name << std::endl;

    return 0;
}
