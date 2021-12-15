#ifndef __E_H
#define __E_H

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
#include "Adress.h"
#include "Party.h"
#include <vector>
#include <fstream>

class Elections
{
private:
	vector<Citizen*> allVoters;
	vector<int> resOfElections;
	vector<Party*> parties;
	vector<BallotBox*> boxes;
	Date dateElection;

public:
	Elections();
	Elections(const Elections& other);
	Elections(Elections&& other);
	~Elections();
	const Elections& operator=(const Elections& other);
	bool operator+=(Citizen& c);
	const Elections& operator=(Elections&& other);
	void initialAllVoters();
	void initialParties();
	void initialBoxes();

	template<typename Container>
	void print(const Container& cont)
	{
		for (auto const& x : cont)
			std::cout << *x << endl;

		std::cout << '\n';
	}
	vector<int>& GetResults();
	vector<Citizen*>& GetAllVotersArr();
	vector<BallotBox*>& GetAllBoxes();
	Party* getPoliticalPartyByName(bool* res, const string& namePoliticalParty) const;
	Candidate* getCitizenById(bool* res, long long id) const;
	Date& GetDateOfElections();
	vector<Party*>& GetAllPartiesArr();
	void isIdIsAvaillable(bool* res, long long id) const;
	void checkIfCitizenAlreadyCandidate(bool* res, long long id) const;
	bool addCitizenToCandidate(long long id, const string& nameOfParty);
	bool addParty(Party& PartyToAdd);
	void showResults();
	void ElectionWantToVote();
	bool SetDateOfElections(Date& d);
	void addBallotBox( BallotBox& boxToAdd);
	bool addCitizen(Citizen& citizenToAdd);
	void updateBoxesAdresses(Citizen& c, int numOfBox);
	int relvantBoxes(int year, bool inQuaratine) const;
	void loadFromFile(ifstream& f);
};
#endif // !__E_H
