#pragma once
#include "LexicalBlock.h"
#include "Syntaxer.h"
#include "CodeGenerator.h"

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
    std::vector<Token> RunLexer(std::string filename);

    /*
    * @brief Проверяет синтаксис программы
    * @returns m_lines: вектор строк
    */
    std::vector<std::vector<std::string>> CheckSyntax();

    /*
    * @brief Переводит код из Mini-Basic в Assembler
    */
    void TranslateCode();
private:
    CodeGenerator m_gen;                            // генератор кода
    Syntaxer m_synt;                                // синтаксер
    LexicalBlock m_lexer;                           // лексический блок
    std::vector<std::vector<std::string>> m_lines;  // вектор строк
    std::vector<Token> m_lexems;                    // вектор лексем
};

