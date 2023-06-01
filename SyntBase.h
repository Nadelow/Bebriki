#pragma once
#include "LexBase.h"

class SyntBase :
    public LexBase
{
public:
    //virtual ~SyntBase() = 0;
    virtual std::vector<std::vector<std::string>> Run(std::vector<Token> lexem) = 0;
protected:
    /*
    * @brief Переопределение Run из LexBase.h для избежания ошибок
    */
    std::vector<Token> Run(std::string filename);
};

