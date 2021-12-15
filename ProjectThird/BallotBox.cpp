#include<iostream>
using namespace std;
#pragma warning(disable:4996)

#include "BallotBox.h"
#include "Citizen.h"
#include "Elections.h"
#include "Candidate.h"
#include "CoronaBox.h"

int BallotBox::counter = 0;

ostream& operator<<(ostream& os, const BallotBox& bb)
{
	if (typeid(os) == typeid(ofstream))
	{
		int soldier = (int)bb.isSoldiers;
		os << (typeid(bb).name()) + 6 <<endl<< bb.id << endl << bb.adr << soldier << endl;;
	}

	else
	{
		os << (typeid(bb).name()) + 6 << endl << "id:" << bb.id << endl << bb.adr;
		if (bb.isSoldiers == true)
			os << "For Soldiers" << endl;
		else
			os << "For Non-Soldiers" << endl;
	}
	return os;
}

istream& operator>>(istream& in, BallotBox& bb)
{
	in >> bb.id;
	in>>bb.adr>>bb.isSoldiers;
	return in;
}

const BallotBox& BallotBox::operator=(const BallotBox& other)
{
	if (this != &other)
	{
		listOfVoters = other.listOfVoters;
		adr = other.adr;
		id = other.id;
		result = other.result;
		countOfVoters = other.countOfVoters;
		percentOfVoters = other.percentOfVoters;
		isSoldiers = other.isSoldiers;
	}
	return *this;
}

const BallotBox& BallotBox::operator=(BallotBox&& other)
{
	if (this != &other)
	{
		listOfVoters = other.listOfVoters;
		adr = other.adr;
		id = other.id;
		countOfVoters = other.countOfVoters;
		percentOfVoters = other.percentOfVoters;
		isSoldiers = other.isSoldiers;
	}
	return *this;
}

BallotBox::BallotBox(Adress& a, int numOfParties,bool isSoldiers)
{
	adr=a;
	for (int i = 0; i < numOfParties; i++)
		result.push_back(0);
	id = ++counter;
	this->isSoldiers = isSoldiers;
}

BallotBox::BallotBox(BallotBox&& other)
{
	*this = other;
}

BallotBox::BallotBox(const BallotBox& other, int numOfParties)
{
	this->adr = other.adr;

	result.reserve(numOfParties);
	for (int i = 0; i < numOfParties; i++)
		result.push_back(0);

	this->countOfVoters = other.countOfVoters;
	this->id = other.id;
	this->percentOfVoters = other.percentOfVoters;
	this->isSoldiers = other.isSoldiers;
	listOfVoters = other.listOfVoters;
}

void BallotBox::setIsSoldiers(bool isSoldiers)
{
	this->isSoldiers = isSoldiers;
}

bool BallotBox::SetResult(int numOfParties)
{
	for (int i = 0; i < numOfParties; i++)
		result.push_back(0);

	return true;
}

void BallotBox::updateResult(int index)
{
	this->result[index]++;
	this->countOfVoters++;
	this->updatePercent();
}

bool BallotBox::SetAdress(Adress& a)
{
	this->adr = a;
	return true;
}

bool BallotBox::SetId(int id)
{
	this->id = id;
	return true;
}

BallotBox::BallotBox(ifstream& in)
{ 
	in >> *this; 
}

const Adress& BallotBox::GetAdr() const
{
	return adr;
}

int BallotBox::GetId() const
{
	return this->id;
}
bool BallotBox::getIsSoldiers() const
{
	return isSoldiers;
}

Array<Citizen*>& BallotBox::GetListOfVoters()
{
	return listOfVoters;
}

vector<int>& BallotBox::GetResult()
{
	return this->result;
}

double BallotBox::GetPercentageOfVoters() const 
{
	return this->percentOfVoters;
}

int BallotBox::GetSizeOfVoters() const 
{
	return this->countOfVoters;
}

void BallotBox::updatePercent()
{
	this->percentOfVoters = ((double)countOfVoters / listOfVoters.size()) * 100;
}

void BallotBox::addVoter(Citizen* voter)
{
	listOfVoters += voter;

}