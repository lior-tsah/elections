#ifndef __PP_H
#define __PP_H
#include "Date.h"
#include"Citizen.h"
#include <vector>
#include<fstream>

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

enum eSide { LEFT, CENTER, RIGHT };

class Candidate;

class Party
{
private:
	static const char* sideOfParty[3];
	vector<Citizen*> listCandidates;
	string name;
	eSide side;
	Date founded;
	int id;
	static int counter;

public:
	Party(eSide side, Date founded, const string& name);
	Party(const Party& other);
	Party(Party&& other);
	const Party& operator=(const Party& other);
	const Party& operator=(Party&& other);
	friend ostream& operator<<(ostream& os, const Party& p);
	bool operator>(const Party& other);
	~Party() = default;
	friend istream& operator>>(istream& in, Party& p);
	Party(ifstream& in) { in >> *this; }
	vector <Citizen*>& GetListOfCandidates();
	bool SetName(const string& name);
	bool SetSide(eSide side);
	bool SetDateFounded(Date& date);
	void addCandidate(Citizen& candidate);
	eSide GetSide() const;
	const Date& GetDateFounded() const;
	const string& GetName() const;
	operator const char*() { return name.c_str(); }
	void setId(int id) { this->id = id; }

};
#endif // !__PP_H
