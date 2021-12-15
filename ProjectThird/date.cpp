#include <iostream>
using namespace std;
#pragma warning (disable: 4996)

#include "Date.h"
#include <fstream>

const char* Date::monthsArray[12] = { "January", "February", "March", "April", "May",
"June", "July", "August", "September", "October", "November", "December" };

ostream& operator<<(ostream& os, const Date& d)
{
	if (typeid(os) == typeid(ofstream))
	os << d.month <<endl<< d.year;
	else
		os << d.monthsArray[d.month] <<' '<< d.year;
	return os;
}

istream& operator>>(istream& in, Date& d)
{
	in >> (int&)d.month >> d.year;
	return in; 
}

Date::Date(int year, eMonth month)
{
	SetYear(year);
	SetMonth(month);
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetYear() const
{
	return year;
}

bool Date::SetMonth(eMonth m)
{
	if (m <eMonth::January || m> eMonth::December)
		return false;
	month = m;
	return true;
}

bool Date::SetYear(int y)
{
	int temp = y;
	int count = 0;
	while (temp > 0)
	{
		temp /= 10;
		count++;
	}
	if (count == 4)
	{
		year = y;
		return true;
	}

	else
		return false;
}