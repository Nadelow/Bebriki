#pragma once
#include <iostream>
#include <vector>
template<typename T>
class Translator
{
public:
	virtual ~Translator() { ; }
	virtual T Run(std::string filename) = 0;
};

