#include "BigInt.h"
#include <iostream>

int main(int argc, char* argv[]) {
	BigInt num(15000000000000000), num1(3000000000000000);
	std::cout << (num / num1) << '\n';
}