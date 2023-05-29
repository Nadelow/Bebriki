﻿#pragma once
#include <iostream>
#include <iomanip>
#include <stack>
#include <sstream>
#include "SyntBase.h"

/*
*@brief Объединение синтаксических лексем, которые описывает все синтаксичекие конструкции в языке
*/
enum syntLexemes
{
	S_LABEL,
	S_OPERAND,
	S_RATIO,
	S_LOOPEND,
	S_LET,
	S_FOR,
	S_GOTO,
	S_GOSUB,
	S_LEFTBR,
	S_RIGHTBR,
	S_IF,
	S_RETURN,
	S_END,
	S_TO,
	S_STEP,
	S_REM,
	S_PLUS,
	S_MINUS,
	S_MULT,
	S_DIV,
	S_POW,
	S_ERR,
	S_ENDM
};

/*
*@brief Объединение Нетерминалы, которые описывают все нетерминалы, которые могут встретиться в программе
*/
enum nonterminals
{
	APROGRAMM = 1,
	APRBODY,
	ASTEP,
	AOTHERSTR,
	AEXPRESS,
	ATERM,
	AMULTIPLIER,
	APRIMARY,
	AE_NODE,
	AT_NODE,
	AF_NODE,
	ARATIO,
	ALOOPEND,
	ATRANSIT,
	ARIGHTBR,
	AEND,
	ATO,
	ADOG,
	ALET,
	AIFGO,
	AKEEP,
	ALABEL,
	ACHECK,
	ACONTROL,
	AINCREASE,
	AGO,
	APLUS,
	AMINUS,
	AMULT,
	ADIV,
	AEXP,
	ASINGPLUS,
	ASINGMINUS

};

/*
* @brief Объединение Атомы,является списком возможных конструкций для реализации использования грамматики
*/
enum atoms

{
	AT_END,
	AT_NS,
	AT_LET,
	AT_GO,
	AT_KEEPGO,
	AT_RETGO,
	AT_IFGO,
	AT_KEEP,
	AT_LABEL,
	AT_CHECK,
	AT_INCREASE,
	AT_PLUS,
	AT_MINUS,
	AT_MULT,
	AT_DIV,
	AT_EXP,
	AT_SINGPLUS,
	AT_SINGMINUS
};

/*
* @brief Структура Атом,является минимальной неделимой структурой для преобразования с помощью грамматики
*/
struct atom
{
	atoms type;
	int atribute1;
	int atribute2;
	int atribute3;
	int atribute4;

};

/*
* @brief Класс Синтаксического анализатора,выполняющий синтаксический анализ программы
*/
class Syntaxer
	: public SyntBase
{
public:

	Syntaxer();
	~Syntaxer();

	/*
	* @brief Проверяет синтаксис программы и сообщает правильно она написана или нет
	* @param lexems: Вектор лексем
	* @returns m_lines: Вектор строк
	*/
	std::vector<std::vector<std::string>> Run(std::vector<Token> lexem);

protected:

	std::stack <int> m_st;				// магазин

	syntLexemes cur = S_ENDM;			// текущее состояние

	int m_strNum = 0;					// текущая строка
	int m_poz = 0;						//  текущая позиция
	int m_HOBTX = 0;
	int m_HOBT = 0;
	int m_HOBTAM = 0;

	std::vector<atom> m_TA;				// Вектор атомов

	std::vector <Token> m_lex;			// Вектор лексем

	std::vector <int> m_for_next;		// Вектор 
	std::vector <int> m_labels;			// Вектор счетчик строк
	std::vector <int> m_marks;			// Вектор меток

	static const int m_nsize = 34;
	static const int m_msize = 23;

	typedef void(Syntaxer::* func)();
	func m_synt_table[m_nsize][m_msize];

private:

	/*
	* @brief Состояние обработки начала строки
	*/
	bool f1();

	/*
	* @brief состояние обработки удаления последнего символа магазина
	*/
	void f2();

	/*
	* @brief состояние в котором происходит обработка let
	*/
	void f3();

	/*
	* @brief состояние в котором происходит обработка выражения в let
	*/
	void f4();

	/*
	*@brief состояние в котором происходит обработка rem
	*/
	void f5();

	/*
	* @brief состояние в котором происходит загрузка выражения в магазин
	*/
	void f6();

	/*
	* @brief состояние в котором происходит обработка next
	*/
	void f7();

	/*
	* @brief состояние в котором происходит переход на новую строку и загрузка атома
	*/
	void f8();

	/*
	* @brief состояние в котором происходит обработка цикла for
	*/
	void f9();

	/*
	* @brief состояние в котором происходит загрузка выражения в магазин
	*/
	void f10();

	/*
	* @brief состояние в котором происходит удаление верхушки магазина
	*/
	void f11();

	/*
	* @brief состояние в котором происходит переход на новую строку
	*/
	void f12();

	/*
	* @brief состояние в котором происходит обработка if
	*/
	bool f13();

	/*
	* @brief состояние в котором происходит загрузка терма в магазин
	*/
	void f14();

	/*
	* @brief состояние в котором происходит обработка сложения узла и терма в общем
	*/
	void f15();

	/*
	* @brief состояние в котором происходит обработка выражения в if
	*/
	void f16();

	/*
	* @brief состояние в котором происходит начало разбора выражания с наименьшим приоритетом арифмитическими операциями
	*/
	void f17();

	/*
	* @brief состояние в котором происходит начало разбора выражания с средним приоритетом арифмитическими операциями
	*/
	void f18();

	/*
	* @brief состояние в котором происходит обработка return
	*/
	void f19();

	/*
	* @brief состояние в котором происходит начало разбора выражания с делением
	*/
	void f20();

	/*
	* @brief состояние в котором происходит обработка goto
	*/
	void f21();

	/*
	* @brief состояние в котором происходит начало разбора выражания с умножением
	*/
	void f22();

	/*
	* @brief состояние в котором происходит обработка end
	*/
	void f23();

	/*
	* @brief состояние в котором происходит очистка магазина от арифметической операции и узла
	*/
	void f24();

	/*
	* @brief состояние в котором происходит завершение разбора выражания
	*/
	void f25();

	/*
	* @brief состояние в котором происходит обработка oшибок
	*/
	void f26();

	/*
	* @brief состояние в котором происходит загрузка атомов выражения
	*/
	void f27();

	/*
	* @brief состояние в котором происходит обработка gosub
	*/
	void f28();

	/*
	* @brief состояние в котором происходит удаление с верхушки магазина и сдвиг на шаг вперед
	*/
	void a();

	/*
	* @brief состояние в котором происходит удаление с верхушки магазина и сдвиг на шаг назад
	*/
	void b();

	/*
	* @brief состояние в котором происходит создание атома конца строки
	*/
	void c();

	/*
	* @brief состояние в котором происходит создание атома присваивания
	*/
	void d();

	/*
	* @brief состояние в котором происходит создание атома выражения
	*/
	void e();

	/*
	* @brief состояние в котором происходит создание атома переменной
	*/
	void f();

	/*
	* @brief состояние в котором происходит создание атома метки
	*/
	void g();

	/*
	* @brief состояние в котором происходит создание атома проверки выражения
	*/
	void h();

	/*
	* @brief состояние в котором происходит создание атома ошибки
	*/
	void i();

	/*
	* @brief состояние в котором происходит создание атома перехода
	*/
	void j();

	/*
	* @brief состояние в котором происходит создание атома перехода на другую строку
	*/
	void k();

	/*
	* @brief состояние в котором происходит создание атома сложения
	*/
	void l();

	/*
	* @brief состояние в котором происходит создание атома вычитания
	*/
	void m();

	/*
	* @brief состояние в котором происходит создание атома умножения
	*/
	void n();

	/*
	* @brief состояние в котором происходит создание атома деления
	*/
	void o();

	/*
	* @brief состояние в котором происходит изменение атомов на атом выражения
	*/
	void p();

	/*
	* @brief состояние в котором происходит создание атома единичного плюса
	*/
	void q();

	/*
	* @brief состояние в котором происходит создание атома единичного минуса
	*/
	void r();

	/*
	* @brief Функция, создающая атом по 4 входным данным ( максимальный размер) создает атом
	* @params наличие 1 - 4 атрибутов по которым будут созданы лексемы
	* @return атом
	*/
	atom createAtom(atoms type, int a1, int a2, int a3, int a4);

	/*
	* @brief  функция замены
	* @params позиция и значение которое необходимо вставить
	*/
	void replace(int depth, int value);

private:

	std::vector <bool> m_is_correct;                       // вектор результатов проверки строк

	std::vector <std::string> m_line;                      // текущая строка
	std::vector <std::vector<std::string>> m_lines;        // вектор всех строк

    std::ofstream m_out;                                   // файл вывода

	bool m_key = false;                                    // метка ключевого слова
	bool m_is_ended = false;                               // метка end

	int m_i = 0;                                           // позиция в строке
	int m_brackets = 0;                                    // счётчик скобок
	int m_gosub_return = 0;                                // счётчик gosub/return
};
