//
// Created by Eliam on 12/06/2025.
//

#ifndef DATE_HPP
#define DATE_HPP
#include <string>


class Date {
private:
	int _year;
	int _month;
	int _day;
public:

	Date();
	Date(const Date &other);
	Date operator=(const Date &other);
	~Date();

	bool operator!=(const Date & date) const;
	bool operator==(const Date & date) const;

	Date(const std::string &date);
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	bool operator<(const Date &other) const;

};



#endif //DATE_HPP
