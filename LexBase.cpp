// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "LexBase.h"

LexBase::~LexBase()
{
}

void LexBase::Print()
{
    if (!m_lexems.empty())
        for (int i = 0; i < m_lexems.size() - 1; i++)
            if (m_lexems[i].lexem_type != "rem_cont")
                std::cout << m_lexems[i].line << '\t' << m_lexems[i].lexem_type << '\t' << m_lexems[i].lexem_name << std::endl;
}
