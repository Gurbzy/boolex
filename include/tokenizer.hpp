#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

enum TokenType {
	TOKEN_END,
	TOKEN_INVALID,
	TOKEN_OPERAND,
	TOKEN_OPERATOR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
};

struct Token {
	TokenType type;
	int pos;
	char ch;
};

void init_token(Token &t, char ch);
void print_token_info(const Token &t);
void print_type(TokenType t);

class Tokenizer {
	private:
		std::vector<Token> expr;
		int tlength;
	public:
		Tokenizer(const std::string expr);
		void printinfo();
};

#endif
