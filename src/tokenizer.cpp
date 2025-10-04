#include "tokenizer.hpp"
#include "utils.hpp"
#include <iostream>
#include <queue>

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

Tokenizer::Tokenizer(const std::string ex) {
	this->tlength = 0;
	
	int elen = ex.length();

	for (int i = 0; i < elen; i++) {
		if (ex[i] == ' ') continue;
		Token t;
		init_token(t, ex[i], map_prec(ex[i]));
		
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

std::queue<Token> Tokenizer::ifix_to_pfix() {
	std::vector<Token> shuntstack;
	std::queue<Token>  shuntqueue;

	Token dummy = { TOKEN_OPERATOR, HASHTAG, '#' };
	shuntstack.push_back(dummy);

	for (int i = 0; i < this->tlength; i++) {
		if (expr[i].type == TOKEN_OPERAND) {
			shuntqueue.push(expr[i]);
		}

		else if (expr[i].type == TOKEN_LPAREN) {
			shuntstack.push_back(expr[i]);
		}

		else if (expr[i].type == TOKEN_RPAREN) {
			while (shuntstack.back().type != TOKEN_LPAREN) {
				Token popped = shuntstack.back();
				shuntstack.pop_back();
				shuntqueue.push(popped);
			}
			// remove RPAREN
			shuntstack.pop_back();
		}

		else if (isOperator(expr[i].ch)) {
			while (!shuntstack.empty()) {
				Token top = shuntstack.back();

				if (isOperator(top.ch) && top.prec >= expr[i].prec) {
					Token popped = shuntstack.back();
					shuntstack.pop_back();
					shuntqueue.push(popped);
				}
				else {
					break;
				}
			}

			shuntstack.push_back(expr[i]);
		}
	}

	while (!shuntstack.empty() && shuntstack.back().ch != '#') {
		Token popped = shuntstack.back();
		shuntstack.pop_back();
		shuntqueue.push(popped);
	}
	
	shuntstack.clear();
	return shuntqueue;
}

void Tokenizer::print_queue() {
	std::queue<Token> pfix = this->ifix_to_pfix();
	
	std::cout << "\nparsed postfix: \n";
	while (!pfix.empty()) {
		Token popped = pfix.front();
		print_token_info(popped);
		pfix.pop();
	}
	std::cout << "\n";
}

