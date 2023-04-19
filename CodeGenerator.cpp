// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "CodeGenerator.h"

CodeGenerator::CodeGenerator()
{
	m_out.open("out.txt");

	m_j = 0;
	m_temp_point = 10;
	m_i = 0;
	m_var_num = 0;

	m_flag = false;
}

void CodeGenerator::CodeCreator(std::vector<std::vector<std::string>>& lines) 
{
	m_out << ".model small\n\n.data?\n\n.data\n\n.code\n\nStart:\n\n";
	m_lines = lines;
	while (m_j < m_lines.size()) 
	{
		m_temp_point++;
		m_out << "\n";
		if (Let())
			continue;
		if (Rem())
			continue;
		if (If())
			continue;
		if (Gosub())
			continue;
		if (For())
			continue;
		if (Next())
			continue;
		if (Return())
			continue;
		if (End())
			break;
		if (Goto())
			continue;
	}
	m_variables.clear();
	m_inserts.clear();
	m_out.close();
}

std::vector<std::vector<std::string>> CodeGenerator::Run(std::vector<Token> lexem)
{
	return std::vector<std::vector<std::string>>();
}

bool CodeGenerator::Rem()
{
	if (m_lines[m_j][1] == "REM") {
		m_out << "@@Label_" << (stoi(m_lines[m_j][0]) + 1) << ":\n";
		m_out << "\t\t\t\t\t;";
		for (int i = 2; i < m_lines[m_j].size(); i++)
			m_out << m_lines[m_j][i];
		m_out << "\n";
		m_temp_point++;
		m_j++;
		return true;
	}
	return false;
}

bool CodeGenerator::Gosub()
{
	if (m_lines[m_j][1] == "GOSUB") 
	{
		m_out << "@@Label_" << (stoi(m_lines[m_j][0]) + 1) << ":\n";
		m_out << "\tST 10, #" << m_temp_point << "\n";
		m_out << "\tjmp @@Label_" << stoi(m_lines[m_j][2]) + 1 << "\n";
		m_j++;
		return true;
	}
	return false;
}

bool CodeGenerator::For()
{
	if (m_lines[m_j][1] == "FOR") 
	{
		if (m_variables.size() == 0)
			m_variables.push_back({ m_lines[m_j][2], 0 });
		else {
			bool flag = false;
			for (m_var_num = 0; m_var_num < m_variables.size(); m_var_num++)
				if (m_variables[m_var_num].first == m_lines[m_j][2]) { flag = true;	break; }
			if (!flag)
				m_variables.push_back({ m_lines[m_j][2], m_variables.back().second + 1 });
		}
		m_out << "\tLD R" << m_variables[m_var_num].second << " " << m_lines[m_j][4] << "\n";
		int k = 0;
		m_out << "@@Label_" << (stoi(m_lines[m_j][0]) + 1) << ":\n";
		m_out << "\tLD R00001 " << m_lines[m_j][6] << "\n";
		while ((m_j < m_lines.size()) and (m_lines[m_j][1] != "NEXT")) 
		{
			m_j++;
			k++;
		}
		m_out << "\tSub R02 R00001 R" << m_variables.back().second << "\n";
		m_out << "\tBLTZ R02 @@Label_" << stoi(m_lines[m_j][0]) + 2 << "\n";
		m_j -= k;
		m_j++;
		return true;
	}
	return false;
}

bool CodeGenerator::Next()
{
	if (m_lines[m_j][1] == "NEXT") 
	{
		m_out << "@@Label_" << (stoi(m_lines[m_j][0]) + 1) << ":\n";
		int k = 0;
		m_temp_point++;
		while ((m_j > 0) and (m_lines[m_j][1] != "FOR")) 
		{
			m_j--;
			k++;
		}
		int t = m_variables.size() - 1;
		while (m_variables[t].first != m_lines[m_j][2])
			t--;
		if (m_lines[m_j].size() > 7) 
		{
			m_out << "\tAdd R" << m_variables[t].second << " " << m_lines[m_j][8] << "\n";
			m_out << "\tjmp @@Label_" << stoi(m_lines[m_j][0]) + 1 << '\n';
		}
		else {
			m_out << "\tinc R" << m_variables[t].second << "\n";
			m_out << "\tjmp @@Label_" << stoi(m_lines[m_j][0]) + 1 << '\n';
		}
		m_j += k;
		m_j++;
		return true;
	}
	return false;
}

bool CodeGenerator::Return()
{
	if (m_lines[m_j][1] == "RETURN") 
	{
		m_out << "@@Label_" << (stoi(m_lines[m_j][0]) + 1) << ":\n";
		m_out << "\tBR *10\n";
		m_temp_point++;
		m_j++;
		return true;
	}
	return false;
}
