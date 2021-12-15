#ifndef __BALLOTBOX_H
#define __BALLOTBOX_H

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

#include "Adress.h"
#include"Citizen.h"
#include "Array.h"
#include <vector>

class BallotBox
{
protected:
	static int counter;
	Adress adr;
	Array<Citizen*> listOfVoters;
	vector<int> result;
	int countOfVoters=0;
	double percentOfVoters = 0.0;
	int id;
	bool isSoldiers;

public:
	BallotBox() = default;
	friend ostream& operator<<(ostream& os, const BallotBox& bb);
	friend istream& operator>>(istream& in, BallotBox& bb);
	BallotBox(ifstream& in);
	BallotBox(BallotBox&& other);
	BallotBox(const BallotBox& other, int numOfParties);
	BallotBox(Adress& a, int numOfParties,bool isSoldiers);
	const BallotBox& operator=(const BallotBox& other);
	const BallotBox& operator=(BallotBox&& other);
	virtual ~BallotBox() = default;

	const Adress& GetAdr() const;
	Array<Citizen*>& GetListOfVoters();
	double GetPercentageOfVoters() const;
	vector<int>& GetResult();
	int GetSizeOfVoters() const;
	int GetId() const; 
	bool SetResult(int numOfParties);
	bool SetAdress(Adress& a);
	bool SetId(int id);
	void addVoter(Citizen* voter);
	void updatePercent();
	void updateResult(int index);
	void setIsSoldiers(bool isSoldiers);
	bool getIsSoldiers() const;
};
#endif // !__BALLOTBOX_h