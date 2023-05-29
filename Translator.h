#pragma once
#include "LexicalBlock.h"
#include "Syntaxer.h"
#include "CodeGenerator.h"

class Translator
{
public:
    /*
    * @brief ����������� ��� �� filename (���� ��� ���� ������ ����������� ����)
    * @param filename: ��� ����� � ����������
    */
    void Translate(std::string filename);

    /*
    * @brief ��������� ��������� �� ������� � ������� ��
    * @param filename: ��� ����� � ����������
    * @param toPrint: true, ����� ������� ������� �� �����, false - �� �������� (�� ��������� false)
    * @returns m_lexems: ������ ������
    */
    std::vector<Token> RunLexer(std::string filename);

    /*
    * @brief ��������� ��������� ���������
    * @returns m_lines: ������ �����
    */
    std::vector<std::vector<std::string>> CheckSyntax();

    /*
    * @brief ��������� ��� �� Mini-Basic � Assembler
    */
    void TranslateCode();
private:
    CodeGenerator* m_gen;                            // ��������� ����
    Syntaxer* m_synt;                                // ���������
    LexicalBlock* m_lexer;                           // ����������� ����
    std::vector<std::vector<std::string>> m_lines;  // ������ �����
    std::vector<Token> m_lexems;                    // ������ ������
};

