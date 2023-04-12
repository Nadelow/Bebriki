#pragma once
#include "LexBase.h"

class SyntBase :
    public LexBase
{
public:
    virtual ~SyntBase() = 0;
    virtual void Run(std::vector<Token> lexem) = 0;
protected:
    std::vector<Token> m_lex; // вектор лексем
};

