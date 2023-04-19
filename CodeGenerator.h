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
	* @brief Генерирует программу на Assembler с функционалом поданной программы на Mini-Basic
	* @param lines: Программа на Mini-Basic в виде вектора векторов строк, где каждая строка - это лексема, а каждый вектор - это строка программы
	*/
	void CodeCreator(std::vector<std::vector<std::string>>& lines);
private:
	//Определение чисто виртуальной функции из SyntBase для избежания ошибок
	std::vector<std::vector<std::string>> Run(std::vector<Token> lexem);

	/*
	* @brief Если строка содержит оператор LET, обрабатывает его
	* @returns true, если обрабатывается LET, false - иначе
	*/
	bool Let();
	/*
	* @brief Создаёт переменные которые будут использоваться вместо значений в выражении в LET
	*/
	void LetGenVars();
	/*
	* @brief Создаёт выражение в LET
	*/
	void LetGenExp();

	/*
	* @brief Если строка содержит оператор LET, обрабатывает его
	* @returns true, если обрабатывается LET, false - иначе
	*/
	bool Rem();

	/*
	* @brief Если строка содержит оператор LET, обрабатывает его
	* @returns true, если обрабатывается LET, false - иначе
	*/
	bool If();
	/*
	* @brief Обрабатывает выражение слева от булевой операции в IF
	*/
	void IfLeft();
	/*
	* @brief Создаёт переменные которые будут использоваться вместо значений в левом выражении в IF
	*/
	void IfLGenVars();
	/*
	* @brief Создаёт левое выражение в IF
	*/
	void IfLGenExp();
	/*
	* @brief Обрабатывает выражение справа от булевой операции в IF
	*/
	void IfRight();
	/*
	* @brief Создаёт переменные которые будут использоваться вместо значений в правом выражении в IF
	*/
	void IfRGenVars();
	/*
	* @brief Создаёт правое выражение в IF
	*/
	void IfRGenExp();

	/*
	* @brief Если строка содержит оператор GOSUB, обрабатывает его
	* @returns true, если обрабатывается GOSUB, false - иначе
	*/
	bool Gosub();

	/*
	* @brief Если строка содержит оператор FOR, обрабатывает его
	* @returns true, если обрабатывается FOR, false - иначе
	*/
	bool For();

	/*
	* @brief Если строка содержит оператор NEXT, обрабатывает его
	* @returns true, если обрабатывается NEXT, false - иначе
	*/
	bool Next();

	/*
	* @brief Если строка содержит оператор RETURN, обрабатывает его
	* @returns true, если обрабатывается RETURN, false - иначе
	*/
	bool Return();

	/*
	* @brief Если строка содержит оператор END, обрабатывает его
	* @returns true, если обрабатывается END, false - иначе
	*/
	bool End();

	/*
	* @brief Если строка содержит оператор GOTO, обрабатывает его
	* @returns true, если обрабатывается GOTO, false - иначе
	*/
	bool Goto();

private:
	std::ofstream m_out;												// файл вывода

	std::vector <std::pair<std::string, int>> m_variables;				// вектор переменных с их названием и адресами

	std::vector <std::pair<std::vector<std::string>, int>> m_inserts;	// вспом. вектор для перевода выр. в обр. польскую запись

	std::vector <std::string> m_in_exp;									// входное выражение для функций

	std::vector<std::vector<std::string>> m_lines;						// вектор векторов строк входной программы

	std::pair<std::string, std::string> m_results;						// вспом. пер. для CodeGenerator

	int m_j;															// счётчик строк
	int m_temp_point;													// текущий номер строки в переведённой программе
	int m_i;															// счётчик лексем в строке
	int m_var_num;														// глобальный номер переменной

	bool m_flag;														// проверка на наличие переменной в m_variables
};

