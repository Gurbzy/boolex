#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>

enum TokenType {
	TOKEN_END,
	TOKEN_INVALID,
	TOKEN_OPERAND,
	TOKEN_OPERATOR,
};

struct Token {
	TokenType type;
	std::string text;
	int length;
};

class Tokenizer {
	private:
		std::string expr;
		int elength;
		int cursor;
	public:
		Tokenizer(std::string expr);
		void printinfo();
};
#endif

