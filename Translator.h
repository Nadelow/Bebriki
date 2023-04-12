#pragma once
#include "LexicalBlock.h"
#include "Syntaxer.h"

class Translator
{
public:
    /*
    * @brief Транслирует код из filename (Пока что есть только лексический блок)
    * @param filename: имя файла с программой
    */
    void Translate(std::string filename);

    /*
    * @brief Разбивает программу на лексемы и выводит их
    * @param filename: имя файла с программой
    * @param toPrint: true, чтобы вывести лексемы на экран, false - не выводить (по умолчанию false)
    * @returns m_lexems: вектор лексем
    */
    std::vector<Token> RunLexer(std::string filename, bool toPrint = false);

    /*
    * @brief Проверяет синтаксис программы
    * @param filename: имя файла с программой
    * @returns true - программа подходит, false - не подходит
    */
    void CheckSyntax();
private:
    Syntaxer m_synt;            // синтаксер
    LexicalBlock m_lexer;       // лексический блок
    std::vector<Token> m_lexems;// вектор лексем
};

