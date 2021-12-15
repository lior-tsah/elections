#include <iostream>
using namespace std;
#pragma warning (disable: 4996)

#include "Party.h"
#include "Candidate.h"
#include <string>
#include <vector>

const char* Party::sideOfParty[3] = { "Left","Center","Right" };

int Party::counter = 0;

istream& operator>>(istream& in, Party& p)
{
	in >> p.id;
	in >>(int&)p.side;
	in.ignore();
	getline(in, p.name);
	in >> p.founded;
	return in;
}

bool Party::operator>(const Party& other)
{
	if (listCandidates.size() > other.listCandidates.size())
		return true;
	else
		return false;
}

ostream& operator<<(ostream& os, const Party& p)
{
	if (typeid(os) == typeid(ofstream))
		os << endl << p.id << endl << p.side << endl << p.name << endl << p.founded;
	else
		os << endl <<"Id: "<<p.id<< " ,Side: " << p.sideOfParty[p.side] << " ,Name: " << p.name << " ,Founded: " << p.founded;
	return os;
}

const Party& Party::operator=(const Party& other)
{
	if (this != &other)
	{
		listCandidates = other.listCandidates;

		this->name = other.name;
		this->SetSide(other.side);
		this->founded = other.founded;
		this->id = other.id;
	}
	return *this;
}

const Party& Party::operator=(Party&& other)
{
	if (this != &other)
	{
		this->listCandidates = other.listCandidates;
		
		this->name = other.name;
		
		this->SetSide(other.side);
		this->SetDateFounded(other.founded);
		this->id = other.id;
	}
	return *this;
}

Party::Party(const Party& other)
{
	*this = other;
}

Party::Party(Party&& other)
{
	*this = other;
}

Party::Party(const eSide side, Date founded, const string& name)
{
	SetSide(side);
	SetDateFounded(founded);
	SetName(name);
	listCandidates.reserve(10);
	id = ++counter;
}

eSide Party::GetSide() const
{
	return this->side;
}

const Date& Party::GetDateFounded() const 
{
	return this->founded;
}

vector <Citizen*>& Party::GetListOfCandidates()
{
	return this->listCandidates;
}

const string& Party::GetName() const 
{
	return this->name;
}

void Party::addCandidate(Citizen &candidate)
{
	listCandidates.push_back(&candidate);
}

bool Party::SetName(const string& name)
{
	this->name = name;
	return true;
}

bool Party::SetSide(eSide side)
{
	if (side<LEFT || side>RIGHT)
		return false;
	else
	{
		this->side = side;
		return true;
	}
}

bool Party::SetDateFounded(Date& date)
{
	this->founded = date;
	return true;
}
