//
// Created by Eliam on 23/06/2025.
//

#include "../includes/Rpn.hpp"
#include <ostream>

RPN::RPN() {
}

RPN::RPN(RPN const &other) { *this = other; }

RPN &RPN::operator=(RPN const &other) {
	if (this != &other)
		stack = other.stack;
	return *this;
}

RPN::~RPN() {
}

bool isNbOp(char key) {
	return (key >= '0' && key <= '9') || key == '+' || key == '-' || key == '*' || key == '/';
}

bool isOperator(char key) {
	return key == '+' || key == '-' || key == '*' || key == '/';
}

int calculate(char key, int v1, int v2) {
	if (key == '+')
		return v2 + v1;
	else if (key == '-')
		return v2 - v1;
	else if (key == '*')
		return v2 * v1;
	return v2 / v1;
}

bool RPN::math(std::string const &rpn) {
	std::istringstream iss(rpn);
	std::string key;

	while (getline(iss, key, ' ')) {
		if (key.size() != 1) {
			std::cerr << "Error: '" << key << "'. Key must be 1 character no more" << std::endl;
			return false;
		}
		if (!isNbOp(key[0])) {
			std::cerr  << "Error: '" << key << "'. Key must be 0-9, '+', '-', '*', or '/'." << std::endl;
			return false;
		}
		if (isOperator(key[0])) {
			if (stack.size() < 2) {
				std::cerr << "Error: Trying to calculate with a stack size < 2" << std::endl;
				return false;
			}
			int v1, v2;
			v1 = stack.top();
			stack.pop();
			v2 = stack.top();
			stack.pop();
			stack.push(calculate(key[0], v1, v2));
		} else
			stack.push(atoi(key.c_str()));
	}
	std::cout << stack.top() << std::endl;
	return true;
}
