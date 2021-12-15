#ifndef __CITIZEN_H
#define __CITIZEN_H


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

class BallotBox;

class Citizen
{
protected:
	BallotBox* box = nullptr;
	string name;
	long long id;
	int numOfBox;
	int yearOfBirth;
	bool Quarantine, isDressWell;

public:
	friend ostream& operator<<(ostream& os, const Citizen& c);
	Citizen(const string& name, long long id, int yearOfBirth, BallotBox& box, int numOfBox, bool isInQuarantine) noexcept(false);//long long,char*
	Citizen(Citizen&& other);
	Citizen(const Citizen& other);
	Citizen(ifstream& in);
	virtual ~Citizen() = default;

	friend istream& operator>>(istream& in, Citizen& c);
	virtual const Citizen& operator=(const Citizen& other);
	virtual const Citizen& operator=(Citizen&& other);
	bool SetName(const string& name);
	bool SetId(long long id);
	bool SetYear(int yearOfBirth);
	bool SetBox(BallotBox& box);
	bool SetNumOfBox(int numOfBox);
	const string& GetName() const;
	long long GetId() const;
	int GetYear() const;
	BallotBox* GetBox() const;
	int GetNumOfBox() const;
	bool getisInQuarantine() const;
	void setQuarantine(bool Quarantine);
	bool getDressWell() const;
	void setDressWell(bool isDressWell);
	virtual void toOs(ostream& os)const {};
	virtual void toIs(istream& in) {};
};

#endif // !__CITIZEN_H
