#pragma once
#include "LexicalBlock.h"

class Translator
{
public:
    /*
    * @brief Транслирует код из filename (Пока что есть только лексический блок)
    * @param filename: имя файла с программой
    */
    void Translate(std::string filename)
    {
        ;
    }

    /*
    * @brief Разбивает программу на лексемы и выводит их
    * @param filename: имя файла с программой
    * @param toPrint: true, чтобы вывести лексемы на экран, false - не выводить (по умолчанию false)
    * @returns m_lexems: вектор лексем
    */
    std::vector<Token> GetLexems(std::string filename, bool toPrint = false)
    {
        m_lexems = m_lexer.Run(filename);

        if (toPrint)
            m_lexer.Print();

        return m_lexems;
    }

    /*
    * @brief Проверяет синтаксис программы
    * @param filename: имя файла с программой
    * @returns true - программа подходит, false - не подходит
    */
    bool CheckSyntax(std::string filename)
    {
        return true;
    }
private:
    LexicalBlock m_lexer;       // лексический блок
    std::vector<Token> m_lexems;// вектор лексем
};

