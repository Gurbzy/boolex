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
	IFF,
	IMPLICATION,
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

struct varIDX {
	char var;
	int idx;

};

class Tokenizer {
	private:
		std::vector<Token> expr;
		int tlength;

		std::queue<Token> ifix_to_pfix();
		std::vector<varIDX> map_unique_idxs();
		void eval_postfix(std::queue<Token> &pfix, std::vector<varIDX>  &var_idx, std::vector<bool> &values);
		std::vector<std::string> gen_subexprs();
		bool isUnique(std::vector<varIDX> &vidx, char c);
		int find_idx(std::vector<varIDX> &vidx, char c);
		bool isValid(std::queue<Token> &pfix);
		bool isValid();
	public:
		Tokenizer(const std::string expr);
		void print_info();
		void print_queue();
		void print_unique_vars();
		void print_truth_table();
		void print_subexprs();
		bool checkValid();
};

#endif
