#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>
#include <queue>

enum TokenType {
	TOKEN_INVALID,
	TOKEN_OPERAND,
	TOKEN_OPERATOR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
};

enum Precedence {
	HASHTAG = -1,
	EQUALS,
	OR,
	XOR,
	AND,
	NOT,
	PAREN,
	OP_INVALID,
};

struct Token {
	TokenType type;
	Precedence prec;
	char ch;
};

Precedence map_prec(char ch);
Precedence getprec(const Token &t);
void init_token(Token &t, char ch, Precedence p);
void print_token_info(const Token &t);
void print_type(TokenType t);

class Tokenizer {
	private:
		std::vector<Token> expr;
		int tlength;

		std::queue<Token> ifix_to_pfix();
	public:
		Tokenizer(const std::string expr);
		void printinfo();
		void print_queue();
};

#endif
