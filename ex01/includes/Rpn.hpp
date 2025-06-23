//
// Created by Eliam on 23/06/2025.
//

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <string>


# include <fstream>
# include <iostream>
# include <sstream>
# include <string>
#include <stack>

class RPN {
private:
	std::stack<int> stack;

public:
	RPN();

	RPN(RPN const &);

	RPN &operator=(RPN const &);

	~RPN();

	bool math(std::string const &);
};


#endif //RPN_HPP
