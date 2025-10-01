#include "utils.hpp"
#include <string>
#include "tokenizer.hpp"

bool isOperand(char c) {
	if (c <= 'a' || c >= 'z') return true;
	if (c <= 'A' || c >= 'Z') return true;
	return false;
}

bool isOperator(char c) {
	const std::string ops = "~!&|^=";
	if (ops.find(c) != std::string::npos) return true;
	return false;
}

bool isInvalid(char c) {
	if (!isOperator(c) && !isOperand(c)) return true;
	return false;
}
