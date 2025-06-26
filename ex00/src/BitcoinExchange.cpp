//
// Created by Eliam on 09/06/2025.
//

#include "../includes/BitcoinExchange.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _exchangeRates(other._exchangeRates)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other) {
		_exchangeRates = other._exchangeRates;
	}
	return *this;
}


void BitcoinExchange::loadExchangeRates()
{
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
				_exchangeRates[date] = std::atof(exchange_rate.c_str()); // Utilisation de std::atof
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
		// passer la premere ligne
		if (firstLine) {
			firstLine = false;
			continue;
		}

		std::istringstream iss(line);
		std::string dateStr, valueStr;

		// parse date et valeur
		if (std::getline(iss, dateStr, '|') && std::getline(iss, valueStr)) {

			if (dateStr.empty() || valueStr.empty()) {
				std::cout << "Error: invalid line format (missing date or value)" << std::endl;
				continue;
			}

			Date date(dateStr);

			// check date
			if (date.getMonth() < 1 || date.getMonth() > 12 ||
				date.getDay() < 1 || date.getDay() > 31) {
				std::cout << "Error: invalid date format for date " << dateStr << std::endl;
				continue;
			}

			//passer la valeur en float
	        float value = std::atof(valueStr.c_str());


			if (value < 0.0f || value > 1000.0f) {
				std::cout << "Error: value out of range (0-1000) for " << valueStr << std::endl;
				continue;
			}

			// multiplier
			float exchangeRate = getExchangeRate(date);
			if (exchangeRate > 0.0f) {
				std::cout << dateStr << " => " << value << " = " << value * exchangeRate << std::endl;
			} else {
				std::cout << "Error: no exchange rate found for the date " << dateStr << std::endl;
			}
		} else {
			std::cout << "Error: invalid line format (incorrect delimiter or missing data)" << std::endl;
		}
	}
}
