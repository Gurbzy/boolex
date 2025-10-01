#include "tokenizer.hpp"
#include "utils.hpp"

int main(int argc, const char *argv[]) {
	std::string ex1 = "wonderful wonder";
	Tokenizer t1(ex1);
	t1.printinfo();
	return 0;
}
