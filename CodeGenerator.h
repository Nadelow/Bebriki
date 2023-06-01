#pragma once
#include <iostream>
#include <iomanip>
#include <stack>
#include <sstream>
#include "SyntBase.h"

class CodeGenerator :
    public SyntBase
{
public:
	CodeGenerator();

	/*
	* @brief ���������� ��������� �� Assembler � ������������ �������� ��������� �� Mini-Basic
	* @param lines: ��������� �� Mini-Basic � ���� ������� �������� �����, ��� ������ ������ - ��� �������, � ������ ������ - ��� ������ ���������
	*/
	void CodeCreator(std::vector<std::vector<std::string>>& lines);
private:
	//����������� ����� ����������� ������� �� SyntBase ��� ��������� ������
	std::vector<std::vector<std::string>> Run(std::vector<Token> lexem);

	/*
	* @brief ���� ������ �������� �������� LET, ������������ ���
	* @returns true, ���� �������������� LET, false - �����
	*/
	bool Let();
	/*
	* @brief ������ ���������� ������� ����� �������������� ������ �������� � ��������� � LET
	*/
	void LetGenVars();
	/*
	* @brief ������ ��������� � LET
	*/
	void LetGenExp();

	/*
	* @brief ���� ������ �������� �������� LET, ������������ ���
	* @returns true, ���� �������������� LET, false - �����
	*/
	bool Rem();

	/*
	* @brief ���� ������ �������� �������� LET, ������������ ���
	* @returns true, ���� �������������� LET, false - �����
	*/
	bool If();
	/*
	* @brief ������������ ��������� ����� �� ������� �������� � IF
	*/
	void IfLeft();
	/*
	* @brief ������ ���������� ������� ����� �������������� ������ �������� � ����� ��������� � IF
	*/
	void IfLGenVars();
	/*
	* @brief ������ ����� ��������� � IF
	*/
	void IfLGenExp();
	/*
	* @brief ������������ ��������� ������ �� ������� �������� � IF
	*/
	void IfRight();
	/*
	* @brief ������ ���������� ������� ����� �������������� ������ �������� � ������ ��������� � IF
	*/
	void IfRGenVars();
	/*
	* @brief ������ ������ ��������� � IF
	*/
	void IfRGenExp();

	/*
	* @brief ���� ������ �������� �������� GOSUB, ������������ ���
	* @returns true, ���� �������������� GOSUB, false - �����
	*/
	bool Gosub();

	/*
	* @brief ���� ������ �������� �������� FOR, ������������ ���
	* @returns true, ���� �������������� FOR, false - �����
	*/
	bool For();

	/*
	* @brief ���� ������ �������� �������� NEXT, ������������ ���
	* @returns true, ���� �������������� NEXT, false - �����
	*/
	bool Next();

	/*
	* @brief ���� ������ �������� �������� RETURN, ������������ ���
	* @returns true, ���� �������������� RETURN, false - �����
	*/
	bool Return();

	/*
	* @brief ���� ������ �������� �������� END, ������������ ���
	* @returns true, ���� �������������� END, false - �����
	*/
	bool End();

	/*
	* @brief ���� ������ �������� �������� GOTO, ������������ ���
	* @returns true, ���� �������������� GOTO, false - �����
	*/
	bool Goto();

private:
	std::ofstream m_out;												// ���� ������

	std::vector <std::pair<std::string, int>> m_variables;				// ������ ���������� � �� ��������� � ��������

	std::vector <std::pair<std::vector<std::string>, int>> m_inserts;	// �����. ������ ��� �������� ���. � ���. �������� ������

	std::vector <std::string> m_in_exp;									// ������� ��������� ��� �������

	std::vector<std::vector<std::string>> m_lines;						// ������ �������� ����� ������� ���������

	std::pair<std::string, std::string> m_results;						// �����. ���. ��� CodeGenerator

	int m_j;															// ������� �����
	int m_temp_point;													// ������� ����� ������ � ����������� ���������
	int m_i;															// ������� ������ � ������
	int m_var_num;														// ���������� ����� ����������

	bool m_flag;														// �������� �� ������� ���������� � m_variables
};

