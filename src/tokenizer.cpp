#include "tokenizer.hpp"
#include "utils.hpp"
#include <iostream>


void init_token(Token &t, char ch, int pos) {
	t.ch = ch;
	t.pos = pos;

	if (isOperand(ch))  { t.type = TOKEN_OPERAND;	}
	if (isOperator(ch)) { t.type = TOKEN_OPERATOR;	}
	if (isInvalid(ch))  { t.type = TOKEN_INVALID;	}
	if (ch == '(') { t.type = TOKEN_LPAREN; } 
	if (ch == ')') { t.type = TOKEN_RPAREN; }
	if (ch == '?') { t.type = TOKEN_END; }
}

void print_type(TokenType T) {
	switch (T) {
		case TOKEN_END: std::cout << "TOKEN_END"; break;
		case TOKEN_INVALID: std::cout << "TOKEN_INVALID"; break;
		case TOKEN_OPERAND: std::cout << "TOKEN_OPERAND"; break;
		case TOKEN_OPERATOR: std::cout << "TOKEN_OPERATOR"; break;
		case TOKEN_LPAREN: std::cout << "TOKEN_LPAREN"; break;
		case TOKEN_RPAREN: std::cout << "TOKEN_RPAREN"; break;
	}
}

void print_token_info(const Token &t) {
	std::cout << "(" << t.ch << ")  :  "; print_type(t.type); std::cout << std::endl; 
}

Tokenizer::Tokenizer(const std::string ex) {
	this->tlength = 0;
	
	int elen = ex.length();

	for (int i = 0; i < elen; i++) {
		if (ex[i] == ' ') continue;
		Token t;
		init_token(t, ex[i], i);
		
		expr.push_back(t);
		this->tlength++;
	}
}

void Tokenizer::printinfo() {
	std::cout << "INFO:\n";
	for (int i = 0; i < tlength; i++) {
		print_token_info(expr[i]);		
	}
}


