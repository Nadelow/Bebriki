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
