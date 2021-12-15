#ifndef _D_H
#define _D_H

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

enum eMonth { January = 1, February, March, April, May, June, July, August, September, October, November, December };

class Date
{
public:
	Date() = default;
	Date(int year, eMonth month);
	friend istream& operator>>(istream& in, Date& d);
	static const char* monthsArray[12];
	friend ostream& operator<<(ostream& os, const Date& d);
	int GetMonth() const;
	int GetYear() const;
	bool SetMonth(eMonth month);
	bool SetYear(int y);

private:
	eMonth month;
	int year;

};
#endif // !_D_H

