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
    
    Parser() {
        for (int i = 0; i < state_number; i++)
            for (int j = 0; j < class_number; j++)
                table[i][j] == &Parser::Error;

        table[A1][Digit] = &Parser::s_E2a; table[A1][Space] = &Parser::s_A1; table[A1][EndOfString] = &Parser::s_A1; table[A1][EndOfFile] = &Parser::Exit1;
        table[A2][Alpha] = &Parser::s_C2a; table[A2][Digit] = &Parser::s_D1a; table[A2][AR_OP] = &Parser::s_A2a; table[A2][Bool] = &Parser::s_H1a; table[A2][Left_bracket] = &Parser::s_A2h;
        table[A2][Right_braket] = &Parser::s_A3b; table[A2][Dot] = &Parser::s_D6; table[A2][Space] = &Parser::s_A2; table[A2][EndOfString] = &Parser::s_A1; table[A2][EndOfFile] = &Parser::Exit1;
        table[A3][Alpha] = &Parser::s_B1a; table[A3][Digit] = &Parser::s_D1a; table[A3][AR_OP] = &Parser::s_A2a; table[A3][Bool] = &Parser::s_H1a; table[A3][Left_bracket] = &Parser::s_A2h;
        table[A3][Right_braket] = &Parser::s_A3b; table[A3][Dot] = &Parser::s_D6; table[A3][Space] = &Parser::s_A3; table[A3][EndOfString] = &Parser::s_A1; table[A3][EndOfFile] = &Parser::Exit1; Exit1();

        table[B1][Alpha] = &Parser::s_M1; table[B1][Space] = &Parser::s_B1;

        table[C1][Alpha] = &Parser::s_C2d; table[C1][Space] = &Parser::s_C1;
        table[C2][Alpha] = &Parser::s_B1b; table[C2][Digit] = &Parser::s_A3a; table[C2][AR_OP] = &Parser::s_A2g; table[C2][Bool] = &Parser::s_H1b; table[C2][Left_bracket] = &Parser::s_A2k;
        table[C2][Right_braket] = &Parser::s_A3c; table[C2][Space] = &Parser::s_C2; table[C2][EndOfString] = &Parser::s_A1a; table[C2][EndOfFile] = &Parser::Exit2;

        table[D1][Alpha] = &Parser::s_M2; table[D1][Digit] = &Parser::s_D1b; table[D1][AR_OP] = &Parser::s_A2c; table[D1][Bool] = &Parser::s_H1c; table[D1][Left_bracket] = &Parser::s_A2u;
        table[D1][Right_braket] = &Parser::s_A3d; table[D1][Dot] = &Parser::s_D2c; table[D1][Space] = &Parser::s_D1; table[D1][EndOfString] = &Parser::s_A1b; table[D1][EndOfFile] = &Parser::Exit3;
        table[D2][Alpha] = &Parser::s_M3; table[D2][Digit] = &Parser::s_D2a; table[D2][AR_OP] = &Parser::s_A2d; table[D2][Bool] = &Parser::s_H1d; table[D2][Left_bracket] = &Parser::s_A2m;
        table[D2][Right_braket] = &Parser::s_A3e; table[D2][Space] = &Parser::s_D2; table[D2][EndOfString] = &Parser::s_A1c; table[D2][EndOfFile] = &Parser::Exit4;
        table[D3][Digit] = &Parser::s_D5a; table[D3][AR_OP] = &Parser::s_D4a; table[D3][Space] = &Parser::s_D3;
        table[D4][Digit] = &Parser::s_D5b; table[D4][Space] = &Parser::s_D4;
        table[D5][Alpha] = &Parser::s_B1c; table[D5][Digit] = &Parser::s_D5c; table[D5][AR_OP] = &Parser::s_A2e; table[D5][Bool] = &Parser::s_H1e; table[D5][Left_bracket] = &Parser::s_A2n;
        table[D5][Right_braket] = &Parser::s_A3f; table[D5][Space] = &Parser::s_D5; table[D5][EndOfString] = &Parser::s_A1d; table[D5][EndOfFile] = &Parser::Exit5;
        table[D6][Digit] = &Parser::s_D2b; table[D6][Space] = &Parser::s_D6;

        table[E1][Digit] = &Parser::s_E2b; table[E1][Space] = &Parser::s_E1;
        table[E2][Alpha] = &Parser::s_B1e; table[E2][Digit] = &Parser::s_E2c; table[E2][AR_OP] = &Parser::s_A2f; table[E2][Bool] = &Parser::s_H1f; table[E2][Left_bracket] = &Parser::s_A2j;
        table[E2][Right_braket] = &Parser::s_A3g; table[E2][Space] = &Parser::s_E2; table[E2][EndOfString] = &Parser::s_A1e; table[D1][EndOfFile] = &Parser::Exit6;

        table[F1][Alpha] = &Parser::s_F2a; table[F1][Space] = &Parser::s_F1;
        table[F2][Digit] = &Parser::s_F3a; table[F2][Bool] = &Parser::s_A2o; table[F2][Space] = &Parser::s_F2;
        table[F3][Bool] = &Parser::s_A2o; table[F3][Space] = &Parser::s_F3;

        table[G1][Alpha] = &Parser::s_G1; table[G1][Digit] = &Parser::s_G1; table[G1][AR_OP] = &Parser::s_G1; table[G1][Bool] = &Parser::s_G1; table[G1][Left_bracket] = &Parser::s_G1;
        table[G1][Right_braket] = &Parser::s_G1; table[G1][Dot] = &Parser::s_G1; table[G1][Space] = &Parser::s_G1; table[G1][EndOfString] = &Parser::s_A1; table[G1][EndOfFile] = &Parser::Exit1;

        table[H1][Alpha] = &Parser::s_C2b; table[H1][Digit] = &Parser::s_D1c; table[H1][AR_OP] = &Parser::s_A2g; table[H1][Bool] = &Parser::s_A2p; table[H1][Left_bracket] = &Parser::s_A2k;
        table[H1][Right_braket] = &Parser::s_A3c; table[H1][Dot] = &Parser::s_D6a; table[H1][Space] = &Parser::s_H1; table[H1][EndOfString] = &Parser::s_A1a; table[H1][EndOfFile] = &Parser::Exit2;

    }
}
int main()
{


    return 0;
}
