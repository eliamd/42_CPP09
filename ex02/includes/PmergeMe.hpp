//
// Created by Eliam on 23/06/2025.
//

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

# include <fstream>
# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <list>
# include <sys/time.h>
#include <algorithm>

class Pmerge
{
private:
	std::list<int>		_lt;
	std::vector<int>	_vt;
public:
	Pmerge();
	Pmerge( Pmerge const & );
	Pmerge & operator=( Pmerge const & );
	~Pmerge();
	std::list<int> sortList( int , char ** );
	void sortVector( int , char ** );
};

#endif
