#pragma once
#include <iostream>
#include <fstream>
#include <vector>

struct Token {
    int line;               // номер строки
    std::string lexem_type; // тип лексемы
    std::string lexem_name; // лексема

    Token(int cur_line, std::string type, std::string name) {
        line = cur_line;
        lexem_type = type;
        lexem_name = name;
    }
};

class LexBase
{
public:
	virtual ~LexBase() { ; }
	virtual std::vector<Token> Run(std::string filename) = 0;
    virtual void Print() = 0;
protected:
	std::ifstream file;	            // файл с программой
    std::vector<Token> m_lexems;	// вектор лексем
};

