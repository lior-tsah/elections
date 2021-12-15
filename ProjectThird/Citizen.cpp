#include<iostream>
using namespace std;
#pragma warning(disable:4996)

const int YEAROFELECTION = 2020;

#include "Citizen.h"
#include <string>

istream& operator>>(istream& in, Citizen& c)
{
	in.ignore();
	getline(in, c.name);
	in >>c.yearOfBirth >> c.id >> c.numOfBox >> c.Quarantine >> c.isDressWell;
	c.toIs(in);
	return in;
}

Citizen::Citizen(ifstream& in)
{
	in >> *this;
}

ostream& operator<<(ostream& os, const Citizen& c)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << endl << (typeid(c).name()) + 6 << endl << c.name<< endl << c.yearOfBirth << endl << c.id << endl << c.GetNumOfBox() << endl << c.Quarantine << endl << c.isDressWell;
		if (typeid(c) != typeid(Citizen))
			os << endl;
		c.toOs(os);
	}
	else
	{
		os << endl << (typeid(c).name()) + 6 << endl << "Name: " << c.name << " ,Year of birth: " << c.yearOfBirth << " ,id: " << c.id << endl;
		if (c.Quarantine == true)
			os << "In Quarantine" << endl;
		else
			os << "Not in Quarantine" << endl;
	}

	return os;
}

const Citizen& Citizen:: operator=(const Citizen& other)
{
	if (this != &other)
	{
		this->box = other.box;
		this->name = other.name;
		this->numOfBox = other.numOfBox;
		this->id = other.id;
		this->yearOfBirth = other.yearOfBirth;
		this->setQuarantine(other.Quarantine);
		this->isDressWell = other.isDressWell;
	}
	return *this;	
}

const Citizen&  Citizen::operator=(Citizen&& other)
{
	if (this != &other)
	{
		this->box = other.box;
		this->name = other.name;
		this->SetNumOfBox(other.numOfBox);
		this->SetId(other.id);
		this->SetYear(other.yearOfBirth);
		this->setQuarantine(other.Quarantine);
		this->isDressWell = other.isDressWell;
	}
	return *this;
}

Citizen::Citizen( Citizen&& other)
{
	*this = other;
}

Citizen::Citizen(const Citizen& other)
{
	*this = other;
}

Citizen::Citizen(const string& name, long long id, int yearOfBirth, BallotBox& box, int numOfBox, bool Quarantine) noexcept(false)//throw (long long,char*)
{
	SetId(id);
	SetName(name);
	SetYear(yearOfBirth);
	SetBox(box);
	SetNumOfBox(numOfBox);
	setQuarantine(Quarantine);
}

bool Citizen::SetBox(BallotBox& box)
{
	this->box = &box;
	return true;
}

bool Citizen::SetYear(int yearOfBirth) noexcept(false)//throw const char*
{
	if (YEAROFELECTION - yearOfBirth < 18)
		throw "You cant vote! you must be at least 18 years old!";

	this->yearOfBirth = yearOfBirth;
	return true;
}

bool Citizen::SetName(const string& name)
{
	this->name =  name;
	return true;
}

bool Citizen::SetId(long long id) noexcept(false)//throw long long
{
	long long temp = id;
	int counter = 0;
	while (temp != 0)
	{
		temp /= 10;
		counter++;
	}
	if (counter != 9)
		throw id;


	this->id = id;
	return true;
}

long long Citizen::GetId() const
{
	return this->id;
}

const string& Citizen::GetName() const 
{
	return this->name;
}

int Citizen::GetYear() const
{
	return this->yearOfBirth;
}

BallotBox* Citizen::GetBox() const 
{
	return this->box;
}

bool Citizen::getisInQuarantine() const 
{
	return this->Quarantine;

}
void Citizen::setQuarantine(bool Quarantine) 
{ 
	this->Quarantine = Quarantine; 
}

bool Citizen::getDressWell() const 
{
	return isDressWell; 
}

void Citizen::setDressWell(bool isDressWell)
{ 
	this->isDressWell = isDressWell; 
}

int Citizen::GetNumOfBox()const
{
	return this->numOfBox;
}

bool Citizen::SetNumOfBox(int numOfBox)
{
	this->numOfBox = numOfBox;
	return true;
}