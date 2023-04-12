// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Translator.h"

void Translator::Translate(std::string filename)
{
}

std::vector<Token> Translator::RunLexer(std::string filename, bool toPrint)
{
    m_lexems = m_lexer.Run(filename);

    if (toPrint)
        m_lexer.Print();

    return m_lexems;
}

void Translator::CheckSyntax()
{
    m_synt.Run(m_lexems);
}
