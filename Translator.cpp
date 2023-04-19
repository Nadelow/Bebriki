// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Translator.h"

void Translator::Translate(std::string filename)
{
    RunLexer(filename);
    CheckSyntax();
    TranslateCode();
}

std::vector<Token> Translator::RunLexer(std::string filename)
{
    m_lexems = m_lexer.Run(filename);
    m_lexer.Print();
    return m_lexems;
}

std::vector<std::vector<std::string>> Translator::CheckSyntax()
{
    m_lines = m_synt.Run(m_lexems);
    return m_lines;
}

void Translator::TranslateCode()
{
    m_gen.CodeCreator(m_lines);
    std::cout << "Translated code is in out.txt" << std::endl;
}
