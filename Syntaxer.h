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
