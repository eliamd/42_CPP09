//
// Created by Eliam on 23/06/2025.
//

#include <iostream>
#include "../includes/Rpn.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error: Invalid number of arguments" << std::endl;
		return 1;
	}
	RPN rpn;
	rpn.math(argv[1]);
}
