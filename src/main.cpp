#include "tokenizer.hpp"
#include "utils.hpp"
#include <iostream>

int main(int argc, const char *argv[]) {
	if (argc < 2) {
		std::cout << "TOO FEW ARGUMENTS\n";
		std::cout << "USAGE: ./boolex <'EXPRESSION'> EX: ./boolex '(p | q) = (!q & !p)'\n";
		return 1;
	}

	std::string cmd_expr = argv_append(argc, argv);
	Tokenizer t1(cmd_expr);

	if (!t1.checkValid()) {
		std::cout << "INVALID EXPRESSION\n";
		t1.print_info();
		return 1;
	}

	t1.print_truth_table();
	return 0;
}
