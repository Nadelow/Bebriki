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
