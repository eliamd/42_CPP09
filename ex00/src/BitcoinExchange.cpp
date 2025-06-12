//
// Created by Eliam on 09/06/2025.
//

#include "../includes/BitcoinExchange.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <__ostream/basic_ostream.h>

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::loadExchangeRates() {
	std::ifstream csvData;
	csvData.open("data_files/data.csv");
	if (!csvData.is_open()) {
		std::cout << "Error: file not found / can't be opened" << std::endl;
		return;
	}
	std::string line;
	bool firstLine = true;
	while (getline(csvData, line)) {
		if (line.empty())
			continue;
		if (firstLine) {
			firstLine = false;
			continue;
		}
		std::istringstream iss(line);
		std::string date, exchange_rate;
		if (std::getline(iss, date, ',') && std::getline(iss, exchange_rate, ',')) {
			if (!date.empty() && !exchange_rate.empty()) {
				_exchangeRates[date] = std::stof(exchange_rate);
			}
		}
	}
}

float BitcoinExchange::getExchangeRate(const Date &date) {
	if (_exchangeRates.empty()) {
		std::cout << "Error: exchange rates not loaded" << std::endl;
		return 0.0f;
	}

	std::map<Date, float>::const_iterator it = _exchangeRates.upper_bound(date);
	if (it == _exchangeRates.begin()) {
		std::cout << "Error: no exchange rate found for the given date" << std::endl;
		return 0.0f;
	}

	--it;
	return it->second;
}


void BitcoinExchange::displayPrices(const char *inputFileName) {
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open()) {
		std::cout << "Error: could not open file " << inputFileName << std::endl;
		return;
	}
	std::string line;
	bool firstLine = true;
	while (std::getline(inputFile, line)) {
		if (firstLine) {
			firstLine = false;
			continue;
		}
		std::istringstream iss(line);
		std::string dateStr, valueStr;
		if (std::getline(iss, dateStr, '|') && std::getline(iss, valueStr)) {
			if (dateStr.empty() || valueStr.empty()) {
				std::cout << "Error: invalid line format" << std::endl;
				continue;
			}
			Date date(dateStr);
			if (date.getMonth() > 12 || date.getMonth() < 1 || date.getDay() < 1 || date.getDay() > 31) {
				std::cout << "Error: invalid date format" << std::endl;
				continue;
			}
			float value = std::stof(valueStr);
			if (value < 0.0f || value > 1000.0f) {
				std::cout << "Error: value out of range (0-1000)" << std::endl;
				continue;
			}
			float exchangeRate = getExchangeRate(date);
			if (exchangeRate > 0.0f) {
				std::cout << dateStr << "=> " << value << " = " << value * exchangeRate << std::endl;
			} else {
				std::cout << "Error: no exchange rate found for the date " << dateStr << std::endl;
			}
		} else {
			std::cout << "Error: invalid line format" << std::endl;
		}
	}
}
