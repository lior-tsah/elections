#ifndef __ADRESS_H
#define __ADRESS_H

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <string>
#include <fstream>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

class Adress
{
private:
	string city;
	string street;
	string numOfBuilding;

public:
	Adress() = default;
	Adress(const string& city, const string& street, string building);
	Adress(const Adress& other);
	Adress(Adress&& other);
	~Adress() = default;
	friend ostream& operator<<(ostream& os, const Adress& a);
	Adress(ifstream& in);
	const Adress& operator=(const Adress& other);
	const Adress& operator=(Adress&& other);
	const string& GetCity() const;
	const string& GetStreet() const;
	friend istream& operator>>(istream& in, Adress& a);
	int   GetBuilding() const;
	bool  SetCity(const string& city);
	bool  SetStreet(const string& street);
	bool  SetBuilding(string numOfBuilding);

};
#endif // !__ADRESS_H
