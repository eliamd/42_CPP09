//
// Created by Eliam on 12/06/2025.
//

#include "../includes/Date.hpp"

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
	size_t pos1 = date.find('-');
	size_t pos2 = date.find('-', pos1 + 1);
	_year = std::stoi(date.substr(0, pos1));
	_month = std::stoi(date.substr(pos1 + 1, pos2 - pos1 - 1));
	_day = std::stoi(date.substr(pos2 + 1));
}

bool Date::operator<(const Date &other) const {
	if (_year != other._year)
		return _year < other._year;
	if (_month != other._month)
		return _month < other._month;
	return _day < other._day;
}
