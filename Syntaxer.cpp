// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Syntaxer.h"

Syntaxer::Syntaxer()
{
	m_st.push(ADOG);
	m_st.push(APROGRAMM);
	m_poz = 0;
	m_HOBTX = m_HOBTAM = 1;
	for (int i = 0; i < 23; i++)
	{
		m_synt_table[AF_NODE][i] = &Syntaxer::f26;
		m_synt_table[ALET][i] = &Syntaxer::d;
		m_synt_table[AIFGO][i] = &Syntaxer::e;
		m_synt_table[AKEEP][i] = &Syntaxer::f;
		m_synt_table[ALABEL][i] = &Syntaxer::g;
		m_synt_table[ACHECK][i] = &Syntaxer::h;
		m_synt_table[AINCREASE][i] = &Syntaxer::j;
		m_synt_table[AGO][i] = &Syntaxer::k;
		m_synt_table[APLUS][i] = &Syntaxer::l;
		m_synt_table[AMINUS][i] = &Syntaxer::m;
		m_synt_table[AMULT][i] = &Syntaxer::n;
		m_synt_table[ADIV][i] = &Syntaxer::o;
		m_synt_table[AEXP][i] = &Syntaxer::p;
		m_synt_table[ASINGPLUS][i] = &Syntaxer::q;
		m_synt_table[ASINGMINUS][i] = &Syntaxer::r;
	}
	m_synt_table[APRBODY][S_LABEL] = &Syntaxer::f3;
	m_synt_table[APRBODY][S_LOOPEND] = m_synt_table[APRBODY][S_END] = &Syntaxer::f2;
	m_synt_table[APRBODY][S_LET] = &Syntaxer::f4;
	m_synt_table[APRBODY][S_FOR] = &Syntaxer::f9;
	m_synt_table[APRBODY][S_GOTO] = &Syntaxer::f5;
	m_synt_table[APRBODY][S_GOSUB] = &Syntaxer::f7;
	m_synt_table[APRBODY][S_IF] = &Syntaxer::f6;
	m_synt_table[APRBODY][S_RETURN] = &Syntaxer::f8;
	m_synt_table[APRBODY][S_REM] = &Syntaxer::f12;
	m_synt_table[ASTEP][S_LABEL] = &Syntaxer::f11;
	m_synt_table[ASTEP][S_STEP] = &Syntaxer::f10;
	m_synt_table[AEXPRESS][S_OPERAND] = m_synt_table[AEXPRESS][S_LEFTBR] = &Syntaxer::f14;
	m_synt_table[AEXPRESS][S_PLUS] = &Syntaxer::f15;
	m_synt_table[AEXPRESS][S_MINUS] = &Syntaxer::f16;
	m_synt_table[ATERM][S_OPERAND] = m_synt_table[ATERM][S_LEFTBR] = &Syntaxer::f20;
	m_synt_table[AMULTIPLIER][S_OPERAND] = m_synt_table[AMULTIPLIER][S_LEFTBR] = &Syntaxer::f24;
	m_synt_table[APRIMARY][S_OPERAND] = &Syntaxer::f28;
	m_synt_table[APRIMARY][S_LEFTBR] = &Syntaxer::f27;
	m_synt_table[AE_NODE][S_LABEL] = m_synt_table[AE_NODE][S_RATIO]
		= m_synt_table[AE_NODE][S_GOTO] = m_synt_table[AE_NODE][S_RIGHTBR]
		= m_synt_table[AE_NODE][S_TO] = m_synt_table[AE_NODE][S_STEP] = &Syntaxer::f19;
	m_synt_table[AE_NODE][S_PLUS] = &Syntaxer::f17;
	m_synt_table[AE_NODE][S_MINUS] = &Syntaxer::f18;
	m_synt_table[AT_NODE][S_LABEL] = m_synt_table[AT_NODE][S_RATIO]
		= m_synt_table[AT_NODE][S_GOTO] = m_synt_table[AT_NODE][S_RIGHTBR]
		= m_synt_table[AT_NODE][S_TO] = m_synt_table[AT_NODE][S_STEP]
		= m_synt_table[AT_NODE][S_PLUS] = m_synt_table[AT_NODE][S_MINUS] = &Syntaxer::f23;
	m_synt_table[AT_NODE][S_MULT] = &Syntaxer::f21;
	m_synt_table[AT_NODE][S_DIV] = &Syntaxer::f22;
	m_synt_table[AF_NODE][S_POW] = &Syntaxer::f25;
	m_synt_table[ARATIO][S_RATIO] = &Syntaxer::b;
	m_synt_table[ALOOPEND][S_LOOPEND] = &Syntaxer::b;
	m_synt_table[ATRANSIT][S_GOTO] = &Syntaxer::b;
	m_synt_table[ARIGHTBR][S_RIGHTBR] = &Syntaxer::a;
	m_synt_table[AEND][S_END] = &Syntaxer::a;
	m_synt_table[ATO][S_TO] = &Syntaxer::a;
	m_synt_table[ADOG][S_ENDM] = &Syntaxer::c;
}

Syntaxer::~Syntaxer()
{
}

std::vector<std::vector<std::string>> Syntaxer::Run(std::vector<Token> lexems)
{
	m_lex = lexems;
	while (m_i != m_lex.size()) 
	{
		if (m_line.size() == 0) 
		{
			if (f1())
				continue;
			else
				break;
		}
		else 
		{
			if (m_lex[m_i].lexem_type == "EOF") 
			{
				break;
			}
			/*if (m_lex[m_i].m_line != m_lex[m_i - 1].m_line) 
			{
				m_line.clear();
				m_is_correct.push_back(true);
				continue;
			}*/
			if (m_lex[m_i].lexem_type == "k_let") 
			{
				f3();
				continue;
			}////with comments
			if (m_lex[m_i].lexem_type == "k_rem") 
			{
				f5();
				continue;
			}
			if (m_lex[m_i].lexem_type == "k_next") 
			{
				f7();
				continue;
			}
			if (m_lex[m_i].lexem_type == "k_for") 
			{
				f9();
				continue;
			}
			if (m_lex[m_i].lexem_type == "k_if") 
			{
				if (f13())
					continue;
			}
			if (m_lex[m_i].lexem_type == "k_gosub") 
			{
				f28();
				continue;
			}
			if (m_lex[m_i].lexem_type == "k_return") 
			{
				f19();
				continue;
			}
			if (m_lex[m_i].lexem_type == "k_end") 
			{
				f23();
				continue;
			}
			/*if (m_lex[m_i].lexem_type == "k_rem") 
			{
				m_line.clear();
				m_is_correct.push_back(true);
				do {
					m_i++;
				} while (m_lex[m_i - 1].m_line == m_lex[m_i].m_line);
				continue;
			}*/
			if (m_lex[m_i].lexem_type == "k_goto") 
			{
				f21();
				continue;
			}
			if (m_lex[m_i].lexem_type == "Error") 
			{
				m_line.clear();
				m_is_correct.push_back(false);
				m_i++;
				while (m_lex[m_i - 1].line == m_lex[m_i].line)
					m_i++;
				continue;
			}
			m_line.clear();
			m_is_correct.push_back(false);
			while (m_lex[m_i - 1].line == m_lex[m_i].line)
				m_i++;
		}
	}
	m_key = true;
	f26();
	bool err = false;
	for (int i = 0; i < m_is_correct.size(); i++)
		if (!m_is_correct[i]) { std::cout << "String " << i + 1 << " has some errors. You must fix it or destroy this string" << std::endl; m_key = false; err = true; }
	if (!m_key) std::cout << "Program contains too much exeptions, fix them" << std::endl;
	else std::cout << "Program was accepted for translation" << std::endl;
	if (err)
	{
		m_lines.clear();
		std::vector<std::string> error;
		error.push_back("Error");
		m_lines.push_back(error);
	}
	return m_lines;
}

bool Syntaxer::f1() 
{
	m_key = false;
	if (m_lex[m_i].lexem_type == "Mark") 
	{
		m_marks.push_back(std::stoi(m_lex[m_i].lexem_name));
		m_line.push_back(m_lex[m_i].lexem_name);
		m_i++;
		return true;
	}
	if (m_lex[m_i].lexem_type == "EOF") 
	{
		return false;
	}
	if (m_lex[m_i].lexem_type == "Error") 
	{
		m_is_correct.push_back(false);
		m_i++;
		while ((m_i < m_lex.size() - 1) and (m_lex[m_i - 1].line == m_lex[m_i].line))
			m_i++;
		return true;
	}
	m_is_correct.push_back(false);
	m_i++;
	while (m_lex[m_i - 1].line == m_lex[m_i].line)
		m_i++;
	return true;
}

void Syntaxer::f2()
{
	m_st.pop();
}

void Syntaxer::f3() 
{
	if (m_line.size() == 1) 
	{
		m_line.push_back(std::string("LET"));
		m_i++;
		m_brackets = 0;
		m_key = true;
		if ((m_lex[m_i].lexem_type == "Variable") and (m_lex[m_i - 1].line == m_lex[m_i].line)) 
		{
			m_line.push_back(m_lex[m_i].lexem_name);
			m_i++;
		}
		else
			m_key = false;
		if ((m_lex[m_i].lexem_type == "Equality") and (m_lex[m_i - 1].line == m_lex[m_i].line)) 
		{
			m_line.push_back(std::string("="));
			m_i++;
		}
		else
			m_key = false;
		f4();
		if ((!m_key) or (m_lex[m_i - 1].lexem_type == "Equality") or (m_lex[m_i - 1].lexem_type == "AR_OP") or (m_brackets != 0)) 
		{
			m_is_correct.push_back(false);
			while (m_lex[m_i - 1].line == m_lex[m_i].line)
				m_i++;
			m_line.clear();
			return;
		}
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;

		m_is_correct.push_back(true);
		m_lines.push_back(m_line);
		m_line.clear();
		return;
	}
	else 
	{
		m_line.clear();
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		return;
	}
}

void Syntaxer::f4()
{
	while ((m_lex[m_i].line == m_lex[m_i - 1].line) and (m_key)) 
	{
		if (m_lex[m_i].lexem_type == "Variable") 
		{
			if ((m_lex[m_i - 1].lexem_type == "Variable") or (m_lex[m_i - 1].lexem_type == "Constant") 
				or (m_lex[m_i - 1].lexem_type == "Rigth_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_i++;
			continue;
		}
		if (m_lex[m_i].lexem_type == "Constant") 
		{
			if ((m_lex[m_i - 1].lexem_type == "Variable") or (m_lex[m_i - 1].lexem_type == "Constant") 
				or (m_lex[m_i - 1].lexem_type == "Rigth_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_i++;
			continue;
		}
		if (m_lex[m_i].lexem_type == "Left_bracket") 
		{
			if ((m_lex[m_i - 1].lexem_type == "Variable") or (m_lex[m_i - 1].lexem_type == "Constant") 
				or (m_lex[m_i - 1].lexem_type == "Rigth_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_brackets++;
			m_i++;
			continue;
		}
		if (m_lex[m_i].lexem_type == "Right_bracket") 
		{
			if ((m_lex[m_i - 1].lexem_type == "AR_OP") or (m_lex[m_i - 1].lexem_type == "Left_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_brackets--;
			m_i++;
			continue;
		}
		if (m_lex[m_i].lexem_type == "AR_OP") 
		{
			if ((m_lex[m_i - 1].lexem_type == "Equality") or (m_lex[m_i - 1].lexem_type == "AR_OP") 
				or (m_lex[m_i - 1].lexem_type == "Left_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_i++;
			continue;
		}
		if (m_lex[m_i].lexem_type == "k_rem") 
		{
			if ((m_brackets != 0) or (m_lex[m_i - 1].lexem_type == "Equality") or (m_lex[m_i - 1].lexem_type == "AR_OP")) m_key = false;
			break;
		}
		m_key = false;
		m_i++;
	}
}

void Syntaxer::f5() 
{
	m_line.push_back("REM");
	int j = 0;
	m_line.push_back("");
	if (m_lex[m_i + 1].lexem_type == "rem_cont")
		for (j; j < m_lex[m_i + 1].lexem_name.size(); j++)
			m_line.back() += m_lex[m_i + 1].lexem_name[j];
	m_lines.push_back(m_line);
	m_line.clear();
	m_is_correct.push_back(true);
	while (m_lex[m_i - 1].line == m_lex[m_i].line)
		m_i++;
}

void Syntaxer::f6()
{
	m_st.pop();
	m_st.push(AOTHERSTR);
	m_st.push(0);
	m_st.push(0);
	m_st.push(0);
	m_st.push(0);
	m_st.push(AIFGO);
	m_st.push(5);
	m_st.push(ATRANSIT);
	m_st.push(5);
	m_st.push(AEXPRESS);
	m_st.push(8);
	m_st.push(ARATIO);
	m_st.push(8);
	m_st.push(AEXPRESS);
	m_poz++;
}

void Syntaxer::f7()
{
	if (m_for_next.size() > 0)m_for_next.pop_back();
	if (m_lex[m_i + 1].lexem_type != "Variable") 
	{
		m_line.clear();
		m_is_correct.push_back(false);
		do 
		{
			m_i++;
		} while (m_lex[m_i - 1].line == m_lex[m_i].line);
		return;
	}
	if (m_lex[m_i + 1].line != m_lex[m_i].line) 
	{
		m_line.clear();
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		return;
	}//err
	if ((m_lex[m_i + 2].line == m_lex[m_i].line) and (m_lex[m_i + 2].lexem_type != "k_rem")) 
	{
		m_line.clear();
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		return;
	}//err
	m_line.push_back(m_lex[m_i].lexem_name);
	m_line.push_back(m_lex[m_i + 1].lexem_name);
	m_lines.push_back(m_line);
	m_line.clear();
	m_is_correct.push_back(true);
	while (m_lex[m_i - 1].line == m_lex[m_i].line)
		m_i++;
}

void Syntaxer::f8()
{
	m_st.pop();
	m_st.push(AOTHERSTR);
	atom a = createAtom(AT_RETGO, -1, -1, -1, -1);
	m_TA.push_back(a);
	m_poz++;
}

void Syntaxer::f9()
{
	m_for_next.push_back(m_lex[m_i].line);
	m_line.push_back(m_lex[m_i].lexem_name);
	if ((m_lex[m_i + 1].line != m_lex[m_i].line) or (m_lex[m_i + 1].lexem_type != "Variable"))
	{
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		m_line.clear();
		return;
	}
	m_i++;
	m_line.push_back(m_lex[m_i].lexem_name);
	if ((m_lex[m_i + 1].line != m_lex[m_i].line) or (m_lex[m_i + 1].lexem_type != "Equality"))
	{
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		m_line.clear();
		return;
	}
	m_i++;
	m_line.push_back(m_lex[m_i].lexem_name);
	if ((m_lex[m_i + 1].line != m_lex[m_i].line) or (m_lex[m_i + 1].lexem_type != "Constant"))
	{
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		m_line.clear();
		return;
	}
	m_i++;
	m_line.push_back(m_lex[m_i].lexem_name);
	if ((m_lex[m_i + 1].line != m_lex[m_i].line) or (m_lex[m_i + 1].lexem_type != "k_to"))
	{
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		m_line.clear();
		return;
	}
	m_i++;
	m_line.push_back(m_lex[m_i].lexem_name);
	if ((m_lex[m_i + 1].line != m_lex[m_i].line) or ((m_lex[m_i + 1].lexem_type != "Constant") and (m_lex[m_i + 1].lexem_type != "Variable")))
	{
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		m_line.clear();
		return;
	}
	m_i++;
	m_line.push_back(m_lex[m_i].lexem_name);
	if (m_lex[m_i + 1].line == m_lex[m_i].line) 
	{
		if (m_lex[m_i + 1].lexem_type == "k_rem") 
		{
			m_is_correct.push_back(true);
			while (m_lex[m_i - 1].line == m_lex[m_i].line)
				m_i++;
			m_line.clear();
			return;
		}
		if (m_lex[m_i + 1].lexem_type == "k_step") 
		{
			if ((m_lex[m_i + 2].line == m_lex[m_i].line) and (m_lex[m_i + 2].lexem_type == "Constant")) 
			{
				m_is_correct.push_back(true);
				m_line.push_back(m_lex[m_i + 1].lexem_name);
				m_line.push_back(m_lex[m_i + 2].lexem_name);
				m_lines.push_back(m_line);
			}
			else
				m_is_correct.push_back(false);
			while (m_lex[m_i - 1].line == m_lex[m_i].line)
				m_i++;

			m_line.clear();
			return;
		}
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		m_line.clear();
		return;
	}
	m_lines.push_back(m_line);
	m_is_correct.push_back(true);
	while (m_lex[m_i - 1].line == m_lex[m_i].line)
		m_i++;
	m_line.clear();
}

void Syntaxer::f10()
{
	m_st.pop();
	m_st.push(AEXPRESS);
	m_poz++;
}

void Syntaxer::f11()
{
	m_st.pop();
	replace(m_st.top(), 0);
}

void Syntaxer::f12()
{
	m_st.pop();
	m_st.push(AOTHERSTR);
	m_poz++;
}

bool Syntaxer::f13() {
	m_line.push_back(m_lex[m_i].lexem_name);
	m_i++;
	m_key = true;
	m_brackets = 0;
	f16();
	m_line.push_back(m_lex[m_i].lexem_name);
	m_i++;
	if (m_lex[m_i].lexem_type == "Constant") 
	{
		if ((m_lex[m_i + 1].line == m_lex[m_i].line) and (m_lex[m_i + 1].lexem_type != "k_rem"))
			m_key = false;
		else 
		{
			m_labels.push_back(std::stoi(m_lex[m_i].lexem_name));
			m_line.push_back(m_lex[m_i].lexem_name);
			m_lines.push_back(m_line);
			m_line.clear();
			m_is_correct.push_back(true);
			while (m_lex[m_i - 1].line == m_lex[m_i].line)
				m_i++;
			return true;
		}
	}
	if ((!m_key) or (m_brackets != 0)) 
	{
		m_is_correct.push_back(false);
		while (m_lex[m_i - 1].line == m_lex[m_i].line)
			m_i++;
		m_line.clear();
		return true;
	}
	return false;
}

void Syntaxer::f14()
{
	m_st.pop();
	m_st.push(0);
	m_st.push(AE_NODE);
	m_st.push(2);
	m_st.push(ATERM);
	//m_poz++;
}

void Syntaxer::f15()
{
	m_st.pop();
	m_st.push(m_HOBT);
	m_st.push(AE_NODE);
	m_st.push(m_HOBT);
	m_st.push(0);
	m_st.push(ASINGPLUS);
	m_st.push(2);
	m_st.push(ATERM);
	m_HOBT++;
	m_poz++;
}

void Syntaxer::f16()
{
	while ((m_lex[m_i].line == m_lex[m_i - 1].line) and (m_lex[m_i].lexem_type != std::string("k_goto")) and (m_key)) 
	{
		if (m_lex[m_i].lexem_type == "Variable") {
			if ((m_lex[m_i - 1].lexem_type == "Variable") or (m_lex[m_i - 1].lexem_type == "Constant") 
				or (m_lex[m_i - 1].lexem_type == "Rigth_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_i++;
			continue;
		}
		if (m_lex[m_i].lexem_type == "Constant") 
		{
			if ((m_lex[m_i - 1].lexem_type == "Variable") or (m_lex[m_i - 1].lexem_type == "Constant") 
				or (m_lex[m_i - 1].lexem_type == "Rigth_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_i++;
			continue;
		}
		if (m_lex[m_i].lexem_type == "Left_bracket") 
		{
			if ((m_lex[m_i - 1].lexem_type == "Variable") or (m_lex[m_i - 1].lexem_type == "Constant") 
				or (m_lex[m_i - 1].lexem_type == "Right_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_brackets++;
			m_i++;
			continue;
		}
		if (m_lex[m_i].lexem_type == "Right_bracket") 
		{
			if ((m_lex[m_i - 1].lexem_type == "AR_OP") or (m_lex[m_i - 1].lexem_type == "Left_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_brackets--;
			if (m_brackets == -1) { break; }
			m_i++;
			continue;
		}
		if (m_lex[m_i].lexem_type == "AR_OP") 
		{
			if ((m_lex[m_i - 1].lexem_type == "Equality") or (m_lex[m_i - 1].lexem_type == "AR_OP") 
				or (m_lex[m_i - 1].lexem_type == "Left_bracket")) { m_key = false; break; }
			m_line.push_back(m_lex[m_i].lexem_name);
			m_i++;
			continue;
		}
		if ((m_lex[m_i].lexem_type == "Bool_op") or (m_lex[m_i].lexem_type == "Equality")) 
		{
			if ((m_lex[m_i - 1].lexem_type == "Equality") or (m_lex[m_i - 1].lexem_type == "AR_OP") 
				or (m_lex[m_i - 1].lexem_type == "Left_bracket") or (m_lex[m_i - 1].lexem_type == "Bool_op")) { m_key = false; break; }
			if (m_lex[m_i].lexem_type == "Bool_op") m_line.push_back(m_lex[m_i].lexem_name);
			else m_line.push_back(std::string("="));
			m_i++;
			continue;
		}
		m_key = false;
		m_i++;
	}
}

void Syntaxer::f17()
{
	m_st.pop();
	int v = m_st.top(); m_st.pop();
	m_st.push(m_HOBT);
	m_st.push(AE_NODE);
	m_st.push(m_HOBT);
	m_st.push(0);
	m_st.push(v);
	m_st.push(APLUS);
	m_st.push(3);
	m_st.push(ATERM);
	m_HOBT++;
	m_poz++;
}

void Syntaxer::f18()
{
	m_st.pop();
	int v = m_st.top(); m_st.pop();
	m_st.push(m_HOBT);
	m_st.push(AE_NODE);
	m_st.push(m_HOBT);
	m_st.push(0);
	m_st.push(v);
	m_st.push(AMINUS);
	m_st.push(3);
	m_st.push(ATERM);
	m_HOBT++;
	m_poz++;
}

void Syntaxer::f19()
{
	m_line.push_back(m_lex[m_i].lexem_name);
	m_key = true;
	if ((m_lex[m_i + 1].line == m_lex[m_i].line) and (m_lex[m_i + 1].lexem_type != "k_rem"))
		m_key = false;
	if (m_key) 
	{
		m_is_correct.push_back(true);
		m_lines.push_back(m_line);
	}
	else
		m_is_correct.push_back(false);
	while (m_lex[m_i - 1].line == m_lex[m_i].line)
		m_i++;
	m_line.clear();
	m_gosub_return--;
}

void Syntaxer::f20()
{
	m_st.pop();
	m_st.push(0);
	m_st.push(AT_NODE);
	m_st.push(2);
	m_st.push(AMULTIPLIER);
}

void Syntaxer::f21()
{
	m_line.push_back(m_lex[m_i].lexem_name);
	if (m_lex[m_i + 1].line == m_lex[m_i].line)
		if (m_lex[m_i + 1].lexem_type == "Constant")
			if (m_lex[m_i + 2].line != m_lex[m_i].line) 
			{
				m_line.push_back(m_lex[m_i + 1].lexem_name);
				m_lines.push_back(m_line);
				m_line.clear();
				m_is_correct.push_back(true);
				m_i += 2;
				return;
			}
	m_line.clear();
	m_is_correct.push_back(false);
	m_i++;
	while (m_lex[m_i - 1].line == m_lex[m_i].line)
		m_i++;
}

void Syntaxer::f22()
{
	m_st.pop();
	int v = m_st.top(); m_st.pop();
	m_st.push(m_HOBT);
	m_st.push(AT_NODE);
	m_st.push(m_HOBT);
	m_st.push(0);
	m_st.push(v);
	m_st.push(ADIV);
	m_st.push(3);
	m_st.push(AMULTIPLIER);
	m_HOBT++;
	m_poz++;

}

void Syntaxer::f23()
{
	m_line.push_back(m_lex[m_i].lexem_name);
	m_key = true;
	if (m_lex[m_i + 1].line == m_lex[m_i].line)
		if (m_lex[m_i + 1].lexem_type != "k_rem")
			m_key = false;
	if (m_key) 
	{
		m_is_correct.push_back(true);
		m_lines.push_back(m_line);
	}
	else
		m_is_correct.push_back(false);
	while (m_lex[m_i - 1].line == m_lex[m_i].line)
		m_i++;
	m_line.clear();
	m_is_ended = true;
}

void Syntaxer::f24()
{
	m_st.pop();
	m_st.push(0);
	m_st.push(AF_NODE);
	m_st.push(2);
	m_st.push(APRIMARY);
}

void Syntaxer::f25()
{
	m_st.pop();
	int v = m_st.top(); m_st.pop();
	m_st.push(m_HOBT);
	m_st.push(AF_NODE);
	m_st.push(m_HOBTX);
	m_st.push(0);
	m_st.push(v);
	m_st.push(AEXP);
	m_st.push(3);
	m_st.push(APRIMARY);
	m_HOBT++;
	m_poz++;
}

void Syntaxer::f26()
{
	if (!m_is_ended) 
	{
		std::cout << "Program must exist operator end, but here its missed" << std::endl;
		m_key = false;
	}
	if (m_for_next.size() > 0) 
	{
		for (int i = 0; i < m_for_next.size(); i++)
			std::cout << "All operators for must be closed by operator next, but this in line " << m_for_next[i] << " is not closed" << std::endl;
		m_key = false;
	}
	if (m_gosub_return > 0) 
	{
		std::cout << "Program must exisr operators return for all operators gosub, but this has not " << m_gosub_return << " operators return" << std::endl;
		m_key = false;
	}
	if (m_labels.size() > 0) 
	{
		bool check = false;
		while (m_labels.size() > 0) 
		{
			for (int i = 0; i < m_marks.size(); i++)
				if (m_marks[i] == m_labels[0]) 
				{
					m_labels.erase(m_labels.begin());
					check = true;
					break;
				}
			if (!check) 
			{
				std::cout << "Program is not exist label " << m_labels[0] << std::endl;
				m_key = false;
				m_labels.erase(m_labels.begin());
			}
			check = false;
		}
	}

}

void Syntaxer::f27()
{
	m_st.pop();
	//int a = m_st.top(); m_st.pop();
	m_st.pop();
	m_st.push(ARIGHTBR);
	//m_st.push(table_lexemes[m_poz].lexeme_value);
	//m_st.push(a);
	m_st.push(3);
	m_st.push(AEXPRESS);
	m_poz++;
}

void Syntaxer::f28()
{
	m_line.push_back(m_lex[m_i].lexem_name);
	m_key = true;
	if (m_lex[m_i + 1].line == m_lex[m_i].line)
		if (m_lex[m_i + 1].lexem_type != "Constant")
			m_key = false;
		else if ((m_lex[m_i + 2].line == m_lex[m_i].line) and (m_lex[m_i + 2].lexem_type != "k_rem"))
			m_key = false;

	if (m_key) 
	{
		m_is_correct.push_back(true);
		m_line.push_back(m_lex[m_i + 1].lexem_name);
		m_lines.push_back(m_line);
		m_labels.push_back(std::stoi(m_lex[m_i + 1].lexem_name));
	}
	else
		m_is_correct.push_back(false);

	while (m_lex[m_i - 1].line == m_lex[m_i].line)
		m_i++;
	m_line.clear();
	m_gosub_return++;
}

void Syntaxer::a()
{
	m_st.pop();
	m_poz++;
}

void Syntaxer::b()
{
	m_st.pop();
	m_poz--;
}

void Syntaxer::c()
{
	atom a = createAtom(AT_END, -1, -1, -1, -1);
	m_TA.push_back(a);
	m_st.pop();
}

void Syntaxer::d()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_LET, p, q, -1, -1);
	m_TA.push_back(a);
}

void Syntaxer::e()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_EXP, p, q, -1, -1);
	m_TA.push_back(a);
}

void Syntaxer::f()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_KEEP, p, q, -1, -1);
	m_TA.push_back(a);
}

void Syntaxer::g()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_LABEL, p, -1, -1, -1);
	m_TA.push_back(a);
}

void Syntaxer::h()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	int r = m_st.top();
	m_st.pop();
	int v = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_CHECK, p, q, r, v);
	m_TA.push_back(a);
}

void Syntaxer::i()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	if (q != p)
		std::cout << "Ïåðåìåííàÿ NEXT-îïåðàòîðà îòëè÷íà îò ïåðåìåííîé FOR-îïåðàòîðà. " << m_st.top() << " - ïðåäïîëàãàåìàÿ ïåðåìåííàÿ" << std::endl;
	m_st.pop();
}

void Syntaxer::j()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_INCREASE, p, q, -1, -1);
	m_TA.push_back(a);
}

void Syntaxer::k()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_GO, p, -1, -1, -1);
	m_TA.push_back(a);

}

void Syntaxer::l()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	int r = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_PLUS, p, q, r, -1);
	m_TA.push_back(a);
}

void Syntaxer::m()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	int r = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_MINUS, p, q, r, -1);
	m_TA.push_back(a);
}

void Syntaxer::n()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	int r = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_MULT, p, q, r, -1);
	m_TA.push_back(a);
}

void Syntaxer::o()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	int r = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_DIV, p, q, r, -1);
	m_TA.push_back(a);
}

void Syntaxer::p()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	int r = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_EXP, p, q, r, -1);
	m_TA.push_back(a);
}

void Syntaxer::q()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_SINGPLUS, p, q, -1, -1);
	m_TA.push_back(a);
}

void Syntaxer::r()
{
	m_st.pop();
	int p = m_st.top();
	m_st.pop();
	int q = m_st.top();
	m_st.pop();
	atom a = createAtom(AT_SINGMINUS, p, q, -1, -1);
	m_TA.push_back(a);
}

atom Syntaxer::createAtom(atoms type, int a1, int a2, int a3, int a4)
{
	atom a;
	a.type = type;
	a.atribute1 = a1;
	a.atribute2 = a2;
	a.atribute3 = a3;
	a.atribute4 = a4;
	return a;
}

void Syntaxer::replace(int depth, int value)
{
	std::stack<int> temp_st;
	int temp;
	for (int i = 0; i < depth; i++)
	{
		temp = m_st.top();
		m_st.pop();
		temp_st.push(temp);
	}
	m_st.pop();
	m_st.push(value);
	for (int i = 0; i < depth; i++)
	{
		temp = temp_st.top();
		temp_st.pop();
		m_st.push(temp);
	}
}
