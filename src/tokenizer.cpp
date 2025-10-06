#include "tokenizer.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <stack>
#include <iomanip>

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

void Tokenizer::print_info() {
	std::cout << "INFO:\n";
	for (int i = 0; i < tlength; i++) {
		print_token_info(expr[i]);		
	}
}

std::vector<std::string> Tokenizer::gen_subexprs() {
	std::queue<Token> pfix = this->ifix_to_pfix();
	std::vector<std::string> subexprs;
    std::stack<std::string> st;

    while (!pfix.empty()) {
        Token front = pfix.front();
        pfix.pop();

        if (isOperand(front)) {
            st.push(std::string(1, front.ch));
        }
        else if (isUnary_op(front)) {
            if (!st.empty()) {
                std::string operand = st.top(); st.pop();
				std::string op(1, front.ch);
                std::string expr = "(" + op + operand + ")";
                st.push(expr);
                subexprs.push_back(expr);
            }
        }
        else if (isBinary_op(front)) {
            // Pop right then left (since postfix)
            if (st.size() >= 2) {
                std::string right = st.top(); st.pop();
                std::string left = st.top(); st.pop();
				std::string op(1, front.ch);
                std::string expr = "(" + left + op + right + ")";
                st.push(expr);
                subexprs.push_back(expr);
            }
      	}
	}

	return subexprs;
}

void Tokenizer::print_subexprs() {
	std::vector<std::string> subexprs = this->gen_subexprs();

	for (std::string &sex : subexprs) {
		std::cout << std::setw(COLWIDTH) << std::left << sex;
	}
	std::cout << "\n";
}

std::queue<Token> Tokenizer::ifix_to_pfix() {
	// shunting yard algorithm 
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

std::map<char, int> Tokenizer::map_unique_idxs() {
	std::map<char, int> uniq_idx;
	int idxstart = 0;

	for (int i = 0; i < this->tlength; i++) {
		if (isOperand(expr[i].ch) && uniq_idx.find(expr[i].ch) == uniq_idx.end()) {
			uniq_idx[expr[i].ch] = idxstart++;
		}
	}

	return uniq_idx;
}

void Tokenizer::print_unique_vars() {
	std::map<char, int> map = this->map_unique_idxs();

	for (const auto & var : map) {
		std::cout << std::setw(COLWIDTH) << std::left << var.first;
	}
}

void Tokenizer::eval_postfix(std::queue<Token> &pfix, std::map<char, int> &var_idx, std::vector<bool> &values) {
	std::vector<bool> evaluated;

	while (!pfix.empty()) {
		Token front = pfix.front();
		pfix.pop();

		if (isOperand(front)) {
			int vidx = var_idx[front.ch];
			evaluated.push_back(values[vidx]);
		}
		else if (isBinary_op(front)) {
			bool operand1 = evaluated.back();
			evaluated.pop_back();
			bool operand2 = evaluated.back();
			evaluated.pop_back();

			bool result = perform_bin_op(operand1, operand2, front);
			evaluated.push_back(result);
			std::cout << std::setw(COLWIDTH) << std::left << result;
		}
		else if (isUnary_op(front)) {
			bool operand1 = evaluated.back();
			evaluated.pop_back();
			
			bool result = perform_unary_op(operand1, front);
			evaluated.push_back(result);
			std::cout << std::setw(COLWIDTH) << std::left << result;
		}

	}
}

void Tokenizer::print_truth_table() {
	std::map<char, int> var_idx = this->map_unique_idxs();
	int varcount = var_idx.size();
	// 2 ^ varcount possible variable permutations
	int rows = 1 << varcount;

	std::vector<bool> current_row(varcount);

	print_unique_vars();
	print_subexprs();
	for (int i = 0; i < rows; i++) {
		std::queue<Token> postfix = this->ifix_to_pfix();

		for (int j = 0; j < varcount; j++) {
			current_row[j] = (bool)(i & (1 << j));
			std::cout << std::setw(COLWIDTH) << std::left << current_row[j];
		}
		eval_postfix(postfix, var_idx, current_row);
		std::cout << "\n";
	}
}

