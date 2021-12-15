#include<iostream>
using namespace std;
#pragma warning(disable:4996)

#include "Candidate.h"
#include <string>

string Candidate::getNameParty()const
{
	return nameOfParty;
}

Candidate::Candidate(ifstream& in): Citizen(in)
{
	toIs(in);
}


void Candidate::toOs(ostream& os)const
{
	os << party->operator const char *();
}

void Candidate:: toIs(istream& in) 
{
	in.ignore();
	getline(in, this->nameOfParty);
}

Candidate::Candidate(const Citizen& other, Party& party) :Citizen(other)
{
	this->party = DBG_NEW Party(party);
}

Candidate::Candidate(const string& name, long long id, int yearOfBirth, BallotBox& box, int numOfBox, bool Quarantine, Party& party) 
	      :Citizen(name, id, yearOfBirth, box, numOfBox, Quarantine)
{
	this->party = DBG_NEW Party(party);
}

Candidate::Candidate(const Candidate& other) : Citizen(other)
{
	this->party = other.party;
}

Party* Candidate::getParty()
{
	return party;
}

void Candidate::setParty(Party& p)
{
	party = DBG_NEW Party(p);
}

const Candidate& Candidate:: operator =(const Candidate& other)
{
	if (this != &other)
	{
		Citizen::operator=(other);
		this->party = other.party;
	}
	return *this;
}

const Candidate& Candidate::operator=(Candidate&& other)
{
	if (this != &other)
	{
		Citizen::operator=(other);
		this->party = other.party;
	}
	return *this;
}
