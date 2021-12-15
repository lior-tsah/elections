#include<iostream>
using namespace std;
#pragma warning(disable:4996)

#include "Adress.h"
#include <string>


ostream& operator<<(ostream& os, const Adress& a)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << a.city << endl;
		os << a.street << endl;
		os << a.numOfBuilding << endl;
	}
	else
		os << "city: " << a.city << " , street: " << a.street << " , numOfBuilding: " << a.numOfBuilding << endl;
	return os;
}

Adress::Adress(ifstream& in) 
{
	in >> *this;
}

istream& operator>>(istream& in, Adress& a)
{
	in.ignore();
	getline(in, a.city);
	getline(in, a.street);
	getline(in, a.numOfBuilding);
	return in;
}

Adress::Adress(const Adress& other)
{
	*this = other;
}

Adress::Adress(Adress&& other)
{
	*this = other;
}

Adress::Adress(const string& city, const string& street, string building)
{
	SetCity(city);
	SetStreet(street);
	SetBuilding(building);
}

const string& Adress::GetCity() const
{
	return this->city;
}

const string& Adress::GetStreet() const
{
	return this->street;
}

int Adress::GetBuilding() const
{
	return stoi(numOfBuilding);
}

bool Adress::SetCity(const string& city)
{
	this->city = city;
	return true;
}

bool Adress::SetStreet(const string& street)
{
	this->street = street;
	return true;
}

bool Adress::SetBuilding(string numOfBuilding)
{
	this->numOfBuilding = numOfBuilding;
	return true;
}

const Adress& Adress:: operator=(const Adress& other)
{
	if (this != &other)
	{
		city = other.city;
		street = other.street;
		this->numOfBuilding = other.numOfBuilding;
	}
	return *this;
}

const Adress& Adress::operator=(Adress&& other)
{
	if (this != &other)
	{
		this->city = other.city;
		this->street = other.street;
		this->numOfBuilding = other.numOfBuilding;
	}
	return *this;
}
