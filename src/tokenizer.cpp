#include "tokenizer.hpp"
#include <iostream>

Tokenizer::Tokenizer(std::string ex) {
	this->cursor = 0;
	this->expr = ex;
	this->elength = ex.length();
}


void
Tokenizer::printinfo() {
	std::cout << "INFO:\n";
	std::cout << "EX:\t" << expr << "\n";
	std::cout << "LENGTH:\t" << elength << "\n";
}
