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
    bool Get_lexem(int line, string lexem) {
        if (lexem.size() < 2)
            return false;
        if (lexem == "IF") {
            lexems.push_back(Token(line, string("k_if"), lexem));
            return true;
        }
        if (lexem == "LET") {
            lexems.push_back(Token(line, string("k_let"), lexem));
            return true;
        }
        if (lexem == "GOSUB") {
            lexems.push_back(Token(line, string("k_gosub"), lexem));
            return true;
        }
        if (lexem == "END") {
            lexems.push_back(Token(line, string("k_end"), lexem));
            return true;
        }
        if (lexem == "NEXT") {
            lexems.push_back(Token(line, string("k_next"), lexem));
            return true;
        }
        if (lexem == "REM") {
            lexems.push_back(Token(line, string("k_rem"), lexem));
            return true;
        }
        if (lexem == "RETURN") {
            lexems.push_back(Token(line, string("k_return"), lexem));
            return true;
        }
        if (lexem == "STEP") {
            lexems.push_back(Token(line, string("k_step"), lexem));
            return true;
        }
        if (lexem == "GOTO") {
            lexems.push_back(Token(line, string("k_goto"), lexem));
            return true;
        }
        if (lexem == "TO") {
            lexems.push_back(Token(line, string("k_to"), lexem));
            return true;
        }
        if (lexem == "FOR") {
            lexems.push_back(Token(line, string("k_for"), lexem));
            return true;
        }
        return false;
    }
    //Процедуры автомата

    int s_A1()
    {
        return A1;
    }
    int s_A1a()
    {
        lex.push_back(s);
        s.clear();
        s.reg_str++;
        return A1;
    }
    int s_A1b()
    {
        s_DA1D();
        return A1;
    }
    int s_A1c()
    {
        s_DA2D();
        return A1;
    }
    int s_A1d()
    {
        s_DA3D();
        return A1;
    }
    int s_A1e()
    {
        s_DA1E();
        return A1;
    }
    int s_A2c()
    {
        s_DA1D();
        return A2;
    }
    int s_A2g()
    {
        lex.push_back(s);
        s.clear();
        s.reg_str++;
        return A2;
    }
    int s_A2a()
    {
        s.token_class = AR_OP;
        return A2;
    }
    int s_A2b()
    {
        if (buffer[i] == '\0') {
            if (lexem.size() > 0)
                if (!(Get_lexem(line, lexem)))
                    if (isdigit(lexem[0]))
                        if (mark)
                            lexems.push_back(Token(line, string("Error"), string("Empty line")));
                        else
                            lexems.push_back(Token(line, string("Constant"), lexem));
                    else
                        lexems.push_back(Token(line, string("Variable"), lexem));
            if (lexems.back().lexem_type == string("Mark"))
                lexems.push_back(Token(line, string("Error"), string("Empty line")));
            lexem.clear();
            word = false;
            constant = false;
            return 1;
        }
        return 0;
    }
    int s_A2()
    {
        lexem.clear();
        copy.clear();
        mark = true;
        constant = false;
        word = false;
        skip_point = false;
        is_rem = false;
        return A2;
    }
    int s_A2d()
    {
        s_DA2D();
        return A2;
    }
    int s_A2e()
    {
        return A2;
    }
    int s_A2f()
    {
        return A2;
    }
    int s_A2j()
    {
        return A2;
    }
    int s_A2k()
    {
        return A2;
    }
    int s_A2h()
    {
        s.token_class = Left_bracket;
        lex.push_back(s);
        s.clear();
        s.reg_str++;
        return A2;
    }
    int s_A2l()
    {
        return A2;
    }
    int s_A2m()
    {
        return A2;
    }
    int s_A2n()
    {
        return A2;
    }
    int s_A2o()
    {
        if (s.relat_reg != "=") {
            //error
        }
        return A2;
    }
    int s_A2p()
    {
        return A2;
    }
    int s_A2q()
    {
        return A2;
    }
    int s_A2r()
    {
        return A2;
    }
    int s_A2s()
    {
        return A2;
    }
    int s_A2t()
    {
        if (buffer[i + 1] == '=') {
            lexems.push_back(Token(line, string("Bool_op"), string("<=")));	skip_point = true; return 1;
        }
        if (buffer[i + 1] == '>') {
            lexems.push_back(Token(line, string("Bool_op"), string("<>")));	skip_point = true; return 1;
        }
        if (buffer[i + 1] == '<') {
            lexems.push_back(Token(line, string("Error"), string("Error in bool operator"))); skip_point = true; return 1;
        }
        lexems.push_back(Token(line, string("Bool_op"), string("<")));
        return 0;
    }
    int s_A2u()
    {
        if (buffer[i + 1] == '=') {
            lexems.push_back(Token(line, string("Bool_op"), string(">=")));	skip_point = true; return 1;
        }
        if (buffer[i + 1] == '>') {
            lexems.push_back(Token(line, string("Error"), string("Error in bool operator"))); skip_point = true; return 1;
        }
        if (buffer[i + 1] == '<') {
            lexems.push_back(Token(line, string("Error"), string("Error in bool operator"))); skip_point = true; return 1;
        }
        lexems.push_back(Token(line, string("Bool_op"), string(">")));
        return 0;
    }
    int s_A3a()
    {
        if (mark) {
            if (isdigit(buffer[i])) {
                lexem += buffer[i];
                return 1;
            }
            else {
                if (lexem.size() > 0)
                    lexems.push_back(Token(line, string("Mark"), lexem));
                else
                    lexems.push_back(Token(line, string("Error"), string("Error in Mark")));
                mark = false;
                lexem.clear();
            }
        }
        return 0;
    }
    int s_A3()
    {
        return A3;
    }
    int s_A3d()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "REM")
            is_rem = true;
        lexem.clear();
        word = false;
        constant = false;
        return A3;
    }
    int s_A3c()
    {
        return A3;
    }
    int s_A3b()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "REM")
            is_rem = true;
        lexem.clear();
        word = false;
        constant = false;
        lexems.push_back(Token(line, string("AR_OP"), string("+")));
        return A3;
    }
    int s_A3e()
    {
        return A3;
    }
    int s_A3f()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "REM")
            is_rem = true;
        lexem.clear();
        word = false;
        constant = false;
        lexems.push_back(Token(line, string("Equality"), string("=")));
        return A3;
    }
    int s_A3g()
    {
        return A3;
    }
    int s_B1c()
    {
        return B1;
    }
    int s_B1b()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "REM") {
            is_rem = true;
            int k = 2;
            while ((buffer[k - 2] != 'R') and (buffer[k - 1] != 'E') and (buffer[k] != 'M'))
                k++;
            buffer.erase(buffer.begin(), buffer.begin() + k + 2);
            lexems.push_back(Token(line, string("rem_cont"), buffer));
        }
        lexem.clear();
        word = false;
        constant = false;
        return B1;
    }
    int s_B1a()
    {
        return B1;
    }
    int s_B1()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "REM")
            is_rem = true;
        lexem.clear();
        word = false;
        constant = false;
        lexems.push_back(Token(line, string("AR_OP"), string("*")));
        return B1;
    }
    int s_B1d()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "REM")
            is_rem = true;
        lexem.clear();
        word = false;
        constant = false;
        lexems.push_back(Token(line, string("AR_OP"), string("/")));
        return B1;
    }
    int s_B1e()
    {
        return B1;
    }
    int s_C1a()
    {
        return C1;
    }
    int s_C1()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "REM")
            is_rem = true;
        lexem.clear();
        word = false;
        constant = false;
        return C1;
    }
    int s_C2b()
    {
        return C2;
    }
    int s_C2a()
    {
        if (lexem.size() == 0) {
            if ((lexems.back().lexem_type != string("Constant")) and (lexems.back().lexem_type != string("Variable")) and (lexems.back().lexem_type != string("Right_bracket"))) {
                constant = true;
                lexem += buffer[i];
            }
            lexem.clear();
            word = false;
            constant = false;
            lexems.push_back(Token(line, string("AR_OP"), string("-")));
        }
        else {
            lexem.clear();
            word = false;
            constant = false;
            lexems.push_back(Token(line, string("AR_OP"), string("-")));
        }
        return C2;
    }
    int s_C2d()
    {
        return C2;
    }
    int s_C2()
    {
        return C2;
    }
    int s_D1c()
    {
        return D1;
    }
    int s_D1a()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    if (lexem[lexem.size() - 1] == 'E') {
                        lexem += buffer[i];
                        return 1;
                    }
                    else
                        lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "REM")
            is_rem = true;
        return 0;
    }
    int s_D1b()
    {
        return D1;
    }
    int s_D1()
    {
        return D1;
    }
    int s_D2a()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "rem")
            is_rem = true;
        lexem.clear();
        word = false;
        constant = false;
        lexems.push_back(Token(line, string("Right_bracket"), string(")")));
        return D2;
    }
    int s_D2()
    {
        return D2;
    }
    int s_D2b()
    {
        return D2;
    }
    int s_D2c()
    {
        if (lexem.size() > 0)
            if (!(Get_lexem(line, lexem)))
                if (isdigit(lexem[0]))
                    lexems.push_back(Token(line, string("Constant"), lexem));
                else
                    lexems.push_back(Token(line, string("Variable"), lexem));
        if (lexem == "rem")
            is_rem = true;
        lexem.clear();
        word = false;
        constant = false;
        lexems.push_back(Token(line, string("Left_bracket"), string("(")));
        return D2;
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
