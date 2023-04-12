#pragma once
#include "LexBase.h"

class SyntBase :
    public LexBase
{
public:
    virtual ~SyntBase() = 0;
    virtual void Run(std::vector<Token> lexem) = 0;
protected:
    /*
    * @brief Переопределение Run из LexBase.h для избежания ошибок
    */
    std::vector<Token> Run(std::string filename);
protected:
    std::vector<Token> m_lex; // вектор лексем
};

