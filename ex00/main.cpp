#include "includes/BitcoinExchange.hpp"
#include <iostream>
#include <fstream>


int main(int argc, char** argv) {
	(void)argc;

	BitcoinExchange bitcoinExchange;
	//load data.csv into class map,
	bitcoinExchange.loadExchangeRates();

	//load input.txt (argv[1]) if file exists and display prices
	std::ifstream file(argv[1]);
	if (!file.is_open()) {
		std::cout << "Error: file not found / can't be opened" << std::endl;
		return 1;
	}

	bitcoinExchange.displayPrices(argv[1]);
	return 0;
}
