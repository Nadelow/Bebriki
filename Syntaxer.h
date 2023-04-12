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

	/*
	* @brief Проверяет синтаксис программы и сообщает правильно она написана или нет
	* @param lexems: Вектор лексем
	*/
	void start(std::vector<Token> lexems);

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
	
private:

	std::vector <bool> m_is_correct;                       // вектор результатов проверки строк

	std::vector <std::string> m_line;                      // текущая строка
	std::vector <std::vector<std::string>> m_lines;        // вектор всех строк

	bool m_key = false;                                    // метка ключевого слова
	bool m_is_ended = false;                               // метка end

	int m_i = 0;                                           // позиция в строке
	int m_brackets = 0;                                    // счётчик скобок
	int m_gosub_return = 0;                                // счётчик gosub/return
};
