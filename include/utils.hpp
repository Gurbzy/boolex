#ifndef UTILS_HPP
#define UTILS_HPP

#include "tokenizer.hpp"
#include <string>

const int COLWIDTH = 20;
const std::string ops = "<>@!&|^=";
const std::string bops = "<>@&|^=";
const std::string uops = "!";

bool isOperand(char c);
bool isOperator(char c);
bool isInvalid(char c);
bool isOperand(Token t);
bool isOperator(Token t);

bool implication_forward(bool a, bool b);
bool implication_backward(bool a, bool b);
bool iff(bool a, bool b);

bool isUnary_op(Token t);
bool isBinary_op(Token t);
bool perform_bin_op(bool a, bool b, Token t);
bool perform_unary_op(bool a, Token t);

Precedence map_prec(char ch);
Precedence getprec(const Token &t);

void init_token(Token &t, char ch, Precedence p);
void print_token_info(const Token &t);
void print_type(TokenType t);

std::string argv_append(int argc, const char *argv[]);

#endif
