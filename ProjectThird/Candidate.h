#ifndef  __Candidate_H
#define __Candiadte_H

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

#include "Citizen.h"
#include "Party.h"
#include<string>

class Candidate :public Citizen
{
private:
	Party* party = nullptr;
	string nameOfParty;

public:
	Candidate(const Citizen& other, Party& party);
	Candidate(const string& name, long long id, int yearOfBirth, BallotBox& box, int numOfBox, bool Quarantine, Party& party);
	Candidate(const Candidate& other);
	Candidate(ifstream& in);
	virtual ~Candidate() { delete party; }

	Party* getParty();
	string getNameParty()const;
	void setParty(Party& p);
	virtual const Candidate& operator =(const Candidate& other);
	virtual const Candidate& operator=(Candidate&& other);
	virtual void toOs(ostream& os)const override;
	virtual void toIs(istream& in)override;
};
#endif // ! __Candidate_h
