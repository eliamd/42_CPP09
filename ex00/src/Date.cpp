//
// Created by Eliam on 12/06/2025.
//

#include "../includes/Date.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

Date::Date() {}

Date::Date(const Date &other): _year(other._year), _month(other._month), _day(other._day) {}

Date Date::operator=(const Date &other) {
	if (this != &other) {
		_year = other._year;
		_month = other._month;
		_day = other._day;
	}
	return *this;
}

Date::~Date() {
}

bool Date::operator!=(const Date &date) const {
	if (getYear() != date.getYear() && getMonth() != date.getMonth() && getDay() != date.getDay())
		return true;
	return false;
}

bool Date::operator==(const Date &date) const {
	if (getYear() != date.getYear() && getMonth() != date.getMonth() && getDay() != date.getDay())
		return false;
	return true;
}

int Date::getYear() const {
	return _year;
}

int Date::getMonth() const {
	return _month;
}

int Date::getDay() const {
	return _day;
}

// Constructor for year, month, and day
Date::Date(const std::string &date) {

	 int date_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	size_t pos1 = date.find('-');
	size_t pos2 = date.find('-', pos1 + 1);
    _year = std::atoi(date.substr(0, pos1).c_str());
    _month = std::atoi(date.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
    _day = std::atoi(date.substr(pos2 + 1).c_str());

	if ((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0)) {
		date_month[1] = 29;
	}

	if (_day > date_month[_month - 1])
		_day = 99;
}

bool Date::operator<(const Date &other) const {
	if (_year != other._year)
		return _year < other._year;
	if (_month != other._month)
		return _month < other._month;
	return _day < other._day;
}
