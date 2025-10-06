#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include "utils.hpp"
#include "tokenizer.hpp"

bool isOperand(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isOperator(char c) {
	const std::string ops = "~!&|^=";
	return (ops.find(c) != std::string::npos);
}

bool isOperand(Token t) {
	return (t.ch >= 'a' && t.ch <= 'z') || (t.ch >= 'A' && t.ch <= 'Z');
}

bool isOperator(Token t) {
	const std::string ops = "~!&|^=";
	return (ops.find(t.ch) != std::string::npos); 
}

bool isBinary_op(Token t) {
	const std::string bops = "&|^=";
	return (bops.find(t.ch) != std::string::npos); 
}

bool isUnary_op(Token t) {
	const std::string uops = "!~";
	return (uops.find(t.ch) != std::string::npos); 
}

bool isInvalid(char c) {
	return !isOperand(c) && !isOperator(c) && c != '(' && c != ')';
}

bool perform_bin_op(bool a, bool b, Token t) {
	assert(isOperator(t) &&  "token in binary perform_op was not operator");
	switch (t.ch) {
		case '&': return a & b;
		case '|': return a | b;
		case '^': return a ^ b;
		case '=': return a == b;
		default: 
			std::cout << "fatal error, unknown bin_op token: " << t.ch << "\n";
			return false;
	}

	return false;
}

bool perform_unary_op(bool a, Token t) {
	assert(isOperator(t) &&  "token in unary perform_op was not operator");

	switch (t.ch) {
		case '!': return !a;
		case '~': return !a;
		default:
			std::cout << "fatal error, unknown unary_op token: " << t.ch << "\n";
			return false;
	}

	return false;
}


Precedence map_prec(char ch) {
	switch (ch) {
		case '(': return PAREN; break;
		case ')': return PAREN; break;
		case '#': return HASHTAG; break;
		case '!': return NOT; break;
		case '~': return NOT; break;
		case '|': return OR; break;
		case '&': return AND; break;
		case '^': return XOR; break;
		case '=': return EQUALS; break;
		default: return OP_INVALID;
	}
	return OP_INVALID;
}

Precedence getprec(const Token &t) {
	return t.prec;
}

void init_token(Token &t, char ch, Precedence p) {
	t.ch = ch;
	p = map_prec(ch);
	t.prec  = p;

	if (isOperand(ch))  { t.type = TOKEN_OPERAND;	}
	if (isOperator(ch)) { t.type = TOKEN_OPERATOR;	}
	if (isInvalid(ch))  { t.type = TOKEN_INVALID;	}
	if (ch == '(') { t.type = TOKEN_LPAREN; } 
	if (ch == ')') { t.type = TOKEN_RPAREN; }
}

void print_type(TokenType T) {
	switch (T) {
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

std::string argv_append(int argc, const char *argv[]) {
	std::ostringstream ss;

	for (int i = 0; i < argc; i++) {
		if (i > 0) ss << argv[i];
	}

	return ss.str();
}
