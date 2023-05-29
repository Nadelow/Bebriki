#include "Translator.h"
#include <QDebug>

void Translator::Translate(std::string filename)
{
    RunLexer(filename);
    CheckSyntax();
    if (!m_lines.empty())
        if(m_lines[0][0] != "Error")
            TranslateCode();
}

std::vector<Token> Translator::RunLexer(std::string filename)
{
    //if(m_lexer != nullptr)
    //    delete m_lexer;
    m_lexer = new LexicalBlock;
    m_lexems = m_lexer->Run(filename);
    m_lexer->Print();
    return m_lexems;
}

std::vector<std::vector<std::string>> Translator::CheckSyntax()
{
    //if(m_synt != nullptr)
    //    delete m_synt;
    m_synt = new Syntaxer;
    m_lines = m_synt->Run(m_lexems);
    return m_lines;
}

void Translator::TranslateCode()
{
    //if(m_gen != nullptr)
    //    delete m_gen;
    m_gen = new CodeGenerator;
    m_gen->CodeCreator(m_lines);
}
