//
// Created by Eliam on 09/06/2025.
//

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <map>
#include "Date.hpp"



class BitcoinExchange {
private:
	std::map<Date, float> _exchangeRates;
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange & operator=(const BitcoinExchange& other);

	void loadExchangeRates();
	float getExchangeRate(const Date&);
	void displayPrices(const char *inputFileName);

};



#endif //BITCOINEXCHANGE_HPP
