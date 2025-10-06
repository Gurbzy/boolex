#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>
#include <queue>
#include <map>

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

class Tokenizer {
	private:
		std::vector<Token> expr;
		int tlength;

		std::queue<Token> ifix_to_pfix();
		std::map<char, int> map_unique_idxs();
		void eval_postfix(std::queue<Token> &pfix, std::map<char, int> &var_idx, std::vector<bool> &values);
		std::vector<std::string> gen_subexprs();
	public:
		Tokenizer(const std::string expr);
		void print_info();
		void print_queue();
		void print_unique_vars();
		void print_truth_table();
		void print_subexprs();
};

#endif
