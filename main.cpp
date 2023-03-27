#include <iostream>
#include <fstream>
#include <algorithm>
#include<string>
#include<Windows.h>
#include<sstream>
#include<vector>
#include<stack>
#include<list>
using namespace std;

enum SymbolicTokenClass { Alpha, Digit, AR_OP, Bool, Dot, Left_bracket, Right_braket, Space, EndOfString, EndOfFile, Error, END, FOR, GOSUB, GOTO, IF, LET, NEXT, REM, RETURN, STEP, TO };
enum States { A1, A2, A3, B1, C1, C2, D1, D2, D3, D4, D5, D6, E1, E2, F1, F2, F3, G1, H1, Stop };

struct LexemToken
{
    SymbolicTokenClass token_class;
    string reg_data;
    int number_reg; // регистр числа
    string relat_reg;// регистр отношения
    string variable_reg;// регистр переменной
    int detect_reg;// регистр обнаружения
    string token_reg;// регистр лексемы
    int reg_str = 1;// номер строки

    void clear()
    {
        number_reg = 0;
        reg_data.clear();
        relat_reg.clear();
        variable_reg.clear();
        detect_reg = 0;
        token_reg.clear();

    }

};

struct Token {
    int line;
    string lexem_type;
    string lexem_name;

    Token(int m_line, string type, string name) {
        line = m_line;
        lexem_type = type;
        lexem_name = name;
    }

};

string toString(int val)
{
    ostringstream oss;
    oss << val;
    return oss.str();

}

const int state_number = 19; //  число состояний без s_Stop
const int class_number = 11; //  число символов входного алфавита
ifstream file("input.txt");
//
class Parser
{
    LexemToken s;
    int ch;
    typedef int(Parser::* function_pointer)();
    function_pointer table[state_number][class_number];
    string data;
    string buffer;
    string lexem;
    string copy;
    int line = 0;
    int i = 0;
    bool mark = true;
    bool constant = false;
    bool word = false;
    bool skip_point = false;
    bool is_rem = false;
public:
    vector <Token> lexems;
    vector<LexemToken> lex;
    vector<int> konst;
    vector<string> var;

    SymbolicTokenClass identification(int c) {
        ch = c;
        if ((ch >= 192 && ch <= 255)) { return Alpha; }
        else if (isalpha(ch)) { return Alpha; }
        else if (isdigit(ch)) { return Digit; }
        else if (ch == '+' || ch == '-' || ch == '/' || ch == '%' || ch == '*') { return AR_OP; }
        else if (ch == '>' || ch == '<' || ch == '=' || ch == '!') { return Bool; }
        else if (ch == ' ') { return Space; }
        else if (ch == '\n') { return EndOfString; }
        else if (ch == EOF) { return EndOfFile; }
        //else { return Error; }
    }
}
int main()
{


    return 0;
}
