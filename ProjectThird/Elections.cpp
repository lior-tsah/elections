#include <iostream>
using namespace std;
#pragma warning (disable: 4996)

#include "Elections.h"
#include "BallotBox.h"
#include "Functions.h"
#include "Candidate.h"
#include "CoronaBox.h"
#include <string>
#include <vector>
#include <filesystem>

bool Elections::operator+=(Citizen& c)
{
	return this->addCitizen(c);
}

const Elections& Elections::operator=(const Elections& other)
{
	if (this != &other)
	{
		this->dateElection = other.dateElection;
		resOfElections = other.resOfElections;
		allVoters = other.allVoters;
		parties = other.parties;
		boxes = other.boxes;
	}
	return *this;
}

const Elections& Elections::operator=(Elections&& other)
{
	if (this != &other)
	{
		this->dateElection = other.dateElection;
		this->boxes = other.boxes;
		this->allVoters = other.allVoters;
		this->parties = other.parties;
		this->resOfElections = other.resOfElections;
	}
	return *this;
}

void Elections::initialParties()
{
	Date d1(1948, eMonth::May);
	parties.reserve(10);

	parties.push_back(DBG_NEW Party(eSide::RIGHT, d1, "Likud"));
	parties.push_back(DBG_NEW Party(eSide::CENTER, d1, "Haavoda"));
	parties.push_back(DBG_NEW Party(eSide::LEFT, d1, "Meretz"));

	initialAllVoters();

	parties[0]->GetListOfCandidates().push_back(allVoters[0]);
	parties[0]->GetListOfCandidates().push_back(allVoters[1]);
	parties[1]->GetListOfCandidates().push_back(allVoters[2]);
	parties[1]->GetListOfCandidates().push_back(allVoters[3]);
	parties[2]->GetListOfCandidates().push_back(allVoters[4]);
	parties[2]->GetListOfCandidates().push_back(allVoters[5]);
}

void Elections::initialAllVoters()
{
	allVoters.reserve(11);

	allVoters.push_back(DBG_NEW Candidate("Bibi Netanyahu", 123456789, 1949, boxes[0][0], 0, true,*parties[0]));
	allVoters[0]->setDressWell(true);
	boxes[0]->GetListOfVoters() += allVoters[0];

	allVoters.push_back(DBG_NEW Candidate("Gideon Saar", 123443211, 1950, boxes[0][0], 0, false, *parties[0]));
	allVoters[1]->setDressWell(false);
	boxes[0]->GetListOfVoters() += allVoters[1];

	allVoters.push_back(DBG_NEW Candidate("David Levi", 123321145, 1951, boxes[0][0], 0, false,*parties[1]));
	allVoters[2]->setDressWell(false);
	boxes[0]->GetListOfVoters() += allVoters[2];

	allVoters.push_back(DBG_NEW Candidate("Lior Tsah", 156654367, 1994, boxes[0][0], 0, true, *parties[1]));
	allVoters[3]->setDressWell(true);
	boxes[0]->GetListOfVoters() += allVoters[3];

	allVoters.push_back(DBG_NEW Candidate("Alon Agam", 312517725, 1949, boxes[0][0], 0, false ,*parties[2]));
	allVoters[4]->setDressWell(true);
	boxes[0]->GetListOfVoters() += allVoters[4];

	allVoters.push_back(DBG_NEW Candidate("Moshe Cohen", 121213456, 1949, boxes[0][0], 0, false, *parties[2]));
	allVoters[5]->setDressWell(true);
	boxes[0]->GetListOfVoters() += allVoters[5];

	allVoters.push_back(DBG_NEW Citizen("Gideon levi", 123553211, 1950, boxes[1][0], 1, false));
	allVoters[6]->setDressWell(false);
	boxes[1]->GetListOfVoters() += allVoters[6];

	allVoters.push_back(DBG_NEW Citizen("David Cohen", 123327745, 1951, boxes[1][0], 1, true));
	allVoters[7]->setDressWell(false);
	boxes[1]->GetListOfVoters() += allVoters[7];

	allVoters.push_back(DBG_NEW Citizen("Lior Kats", 150054367, 1994, boxes[1][0], 1, false));
	allVoters[8]->setDressWell(true);
	boxes[1]->GetListOfVoters() += allVoters[8];

	allVoters.push_back(DBG_NEW Citizen("Alon Mangisto", 312512225, 1994, boxes[1][0], 1, true));
	allVoters[9]->setDressWell(false);
	boxes[1]->GetListOfVoters() += allVoters[9];

	allVoters.push_back(DBG_NEW Citizen("Moshe Tibi", 959691456, 1953, boxes[1][0], 1, false));
	allVoters[10]->setDressWell(true);
	boxes[1]->GetListOfVoters() += allVoters[10];
}

void Elections::initialBoxes()
{
	Adress a1("Tel Aviv", "Ibn Gabirol", "56");
	Adress a2("Holon", "Hamelacha", "120");
	Adress a3("Tel Aviv", "Levy Eschol", "10");
	Adress a4("Holon", "Rothchild", "14");

	boxes.reserve(10);
	boxes.push_back(DBG_NEW CoronaBox(a1, 4, true));
	boxes.push_back(DBG_NEW BallotBox(a2, 4, false));
	boxes.push_back(DBG_NEW BallotBox(a3, 4, true));
	boxes.push_back(DBG_NEW CoronaBox(a4, 4 , false));
}

Elections::~Elections()
{
	for (auto p : parties)
		delete p;

	parties.clear();

	for (auto b : boxes)
		delete b;

	boxes.clear();

	for (auto a : allVoters)
		delete a;

	allVoters.clear();
}

Elections::Elections(const Elections& other)
{
	*this = other;
}

Elections::Elections(Elections&& other)
{
	*this = other;
}

void Elections::loadFromFile(ifstream& f)
{
	string type;
	int numOfBoxes, numOfParties, numOfVoters;

	f >> numOfBoxes;
	for (int i = 0; i < numOfBoxes; i++)
	{
		f >> type;
		if (type == "CoronaBox")
			boxes.push_back(DBG_NEW CoronaBox(f));
		else
			boxes.push_back(DBG_NEW BallotBox(f));

		boxes[i]->GetResult().push_back(0);
	}
	
	f >> numOfParties;
	for (int i = 0; i < numOfParties; i++)
		parties.push_back(DBG_NEW Party(f));

	f >> numOfVoters;
	for (int i = 0; i < numOfVoters; i++)
	{
		f >> type;
		if (type == "Citizen")
			allVoters.push_back(DBG_NEW Citizen(f));
		else
			allVoters.push_back(DBG_NEW Candidate(f));
	}

	for (auto c:allVoters)
	{

		if (typeid(*c) == typeid(Candidate))
		{
			for (auto p : parties)
			{
				if (((Candidate*)c)->getNameParty() == (*p).GetName())
				{
					//Party *pp = new Party(*p);
					((Candidate*)c)->setParty(*p);
					break;
				}
			}
		}
		for (auto b : boxes)
		{
			if (c->GetNumOfBox() == b->GetId() - 1)
			{
				c->SetBox(*b);
				b->GetListOfVoters() += c;
				break;
			}
		}
	}

	for (auto b : boxes)
	{
		for (int i = 0; i < parties.size(); i++)
			b->GetResult().push_back(0);
	}



	f.close();
}

Elections::Elections()
{
	Date d(2020, eMonth::April);
	SetDateOfElections(d);
	ifstream f("Elections.txt");
	if (!(f.is_open())||(f.peek()==EOF))//|| (length==0))//checking if the file is empty or now exist.
	{
		initialBoxes();
		initialParties();
	}
	else
		loadFromFile(f);
}

void Elections::updateBoxesAdresses(Citizen& c, int numOfBox)//updating the boxes adresses when allocating a citizen/boxes.
{
	c.SetBox(*boxes[numOfBox]);
}



bool Elections::addCitizen(Citizen& citizenToAdd)//adding a citizen to the voters array.
{
	allVoters.push_back(&citizenToAdd);

	for (int i = 0; i < allVoters.size(); i++)
		updateBoxesAdresses(*allVoters[i], allVoters[i]->GetNumOfBox());//updating the box of the new  citizen.

	boxes[citizenToAdd.GetNumOfBox()]->addVoter(&citizenToAdd);//adding the citizen to the list of the voters of his box.
	return true;

}

Party* Elections::getPoliticalPartyByName(bool* res, const string& namePoliticalParty) const//checking if the party is exist.
{
	for (int i = 0; i < parties.size(); i++)
	{
		if (parties[i]->GetName()==namePoliticalParty)
		{
			*res = true;
			return parties[i];
		}
	}
	//the party is not exist.
	*res = false;
	cout << "your party is not exist!" << endl
		<< "The action has not been done!" << endl << endl;
	return nullptr;
}

Candidate* Elections:: getCitizenById(bool* res, long long id) const //checking if the voter is exist.
{
	for (auto p : allVoters)
	{
		if (p->GetId() == id)
		{
			*res = true;
			return (Candidate*)p;
		}
	}
	/*
	for(int i=0;i<allVoters.size();i++)
	{
		if (allVoters[i]->GetId() == id)
		{
			*res = true;
			return (Candidate*)&allVoters[i];
		}
	}
	*/

	//the voter is not exist.
	cout << "your voter is not exist!" << endl
		<< "The action has not been done!" << endl << endl;
	*res = false;
	return nullptr;
}

void Elections::isIdIsAvaillable(bool* res, long long id) const//checking when adding a citizen that the DBG_NEW  id is availlavble.
{
	for (int i = 0; i < allVoters.size(); i++)
	{
		if (allVoters[i]->GetId() == id)
		{
			*res = false;
			cout << "This id is already exists!" << endl
				<< "your actions has not been done!" << endl << endl;
			return;
		}
	}
	//the id is availlable.
	*res = true;
}

void Elections::checkIfCitizenAlreadyCandidate(bool* res, long long id) const //checking when adding a citizen as a candidate if he is already a candidate for other party.
{
	*res = true;
	for (int i = 0; i < parties.size() && *res == true; i++)
	{
		{
			for (int j = 0; j < parties[i]->GetListOfCandidates().size(); j++)
			{				
				if (parties[i]->GetListOfCandidates()[j]->GetId() == id)//he is already a candidate
				{
					cout << parties[i]->GetListOfCandidates()[j]->GetName() << " is already a candidate!" << endl
						<< "The action has not been done!" << endl << endl;
					*res = false;
					return;
				}
			}
		}
	}
}

bool Elections::addCitizenToCandidate(long long id, const string& nameOfParty) 
{
	bool res;
	Candidate* citizenToAdd = getCitizenById(&res, id);
	if (res == true)//the citizen is exist in the allvoters array
	{
		checkIfCitizenAlreadyCandidate(&res, id);
		if (res == true)//the citizen is not a candidate of other parties
		{
			Party* party = getPoliticalPartyByName(&res, nameOfParty);
			if (res == true)//if the wanted party is exists
			{
				party->addCandidate(*citizenToAdd);
				citizenToAdd->setParty(*party);
				return true;
			}

			else
				return false;//the wanted party is not existing
		}
		else//the citizen is already a candidate for one of the parties
			return false;
	}
	else//the citizen is not exist in the allvoters array
		return false;
}

void Elections::showResults()
{
	for (int k = 0; k <parties.size(); k++)
		resOfElections.push_back(0);


	resOfElections.size();

	cout << "The results of elections in year: " << GetDateOfElections().GetYear() << "\tin month: "
		<< dateElection.monthsArray[GetDateOfElections().GetMonth() - 1] << "\tare:" << endl << endl;

	for (int i = 0; i < boxes.size(); i++)
	{
		cout << "The results in BallotBox #" << i + 1 << " are:" << endl << endl;
		for (int j = 0; j < resOfElections.size(); j++)
		{
			resOfElections[j] += boxes[i]->GetResult()[j];
			cout << parties[j]->GetName() << " recived:" << boxes[i]->GetResult()[j] << " votes" << endl;
		}
		cout << "The percentage of the voters in BallotBox #" << i + 1 << " is:" << boxes[i]->GetPercentageOfVoters() << '%' << endl << endl;
	}

	cout << endl;

	cout << "The final Results are: " << endl;
	for (int l = 0; l < parties.size(); l++)
	{
		cout << parties[l]->GetName() << " recived: " << resOfElections[l] << " votes" << endl;
	}
	cout << endl << endl;
}

Date& Elections::GetDateOfElections()
{
	return this->dateElection;
}

void Elections::ElectionWantToVote()//asking all the voters if they want to vote.
{
	int idOfParty;
	char answer;

	for (int i = 0; i < allVoters.size(); i++)
	{
		cout << allVoters[i]->GetName() << "-Would you like to vote?" << endl
			 << "For Yes enter 'Y' and for No enter 'N'" << endl;

			cin >> answer;

		if (answer == 'y' || answer == 'y')
		{
			if (typeid (allVoters[i]->GetBox()[0]) == typeid(CoronaBox))
			{
				BallotBox* bb = allVoters[i]->GetBox();
				bool answer=((CoronaBox&)*bb).checkIfCitizenDressWell(*allVoters[i]);
				if (answer == false)
					continue;
			}
			print(parties);
				cout << "Please choose a party by id:" << endl;
				cin >> idOfParty;
					if (idOfParty > 0 && idOfParty <= parties.size())//good id of the party.
					allVoters[i]->GetBox()->updateResult(idOfParty-1);

			else//wrong id of the party.
			{
				while (idOfParty <= 0 || idOfParty>parties.size())
				{
					cout << "you entered wrong id! please try again:" << endl;
					cin >> idOfParty;
				}
				allVoters[i]->GetBox()->updateResult(idOfParty-1);
			}
		}

		else if (answer == 'n' || answer == 'N')//dont want to vote.
			continue;

		else//wrong input.
		{
			while (answer != 'n' && answer && 'N' && answer != 'y' && answer != 'Y')
			{
				cout << "wrong input! please enter again:" << endl;
				cin >> answer;
			}
			if (answer == 'Y' || answer == 'y')
			{
				print(parties);
				cout << "Please choose a party by id:" << endl;
				cin >> idOfParty;
				if (idOfParty > 0 && idOfParty <= parties.size())//good id of the party.
					allVoters[i]->GetBox()->updateResult(idOfParty-1);

				else//wrong id of the party.
				{
					while (idOfParty <= 0 || idOfParty>parties.size())
					{
						cout << "you entered wrong id! please try again:" << endl;
						cin >> idOfParty;
					}
					allVoters[i]->GetBox()->updateResult(idOfParty-1);
				}
			}
			else if (answer == 'n' || answer == 'N')//dont want to vote.
				continue;
		}
		
	}
}

bool Elections::SetDateOfElections(Date& d)
{
	dateElection = d;
	return true;
}

vector<Party*>& Elections::GetAllPartiesArr()
{
	return parties;
}

void Elections::addBallotBox(BallotBox& boxToAdd)
{
	boxes.push_back(&boxToAdd);

}

bool Elections::addParty(Party& partyToAdd)
{
	if (partyToAdd.GetDateFounded().GetMonth() > eMonth::December|| partyToAdd.GetDateFounded().GetMonth() < eMonth::January)
	{
		cout << "Wrong month" << endl;
		cout << "The action has not been done" << endl << endl;
		return false;
	}
	
	else
	{
		parties.push_back(&partyToAdd);
		for (auto b : boxes)
			b->GetResult().push_back(0);
		//for (int i = 0; i < boxes.size(); i++)//putting the new party in all boxes array.
			//boxes[i]->SetResult((int)parties.size());
		return true;
	}
}

vector<int>& Elections::GetResults()
{
	return this->resOfElections;
}

vector<Citizen*>& Elections::GetAllVotersArr()
{
	return this->allVoters;
}

vector<BallotBox*>& Elections::GetAllBoxes()
{
	return this->boxes;
}

int Elections::relvantBoxes(int year, bool isInQuaratine) const 
{
	if (dateElection.GetYear() - year <= 21 && dateElection.GetYear() >= 18)//boxes for soldiers.
	{
		for (int i = 0; i < boxes.size(); i++)
		{
			if (isInQuaratine == true && boxes[i]->getIsSoldiers() == true && typeid(*boxes[i]) == typeid(CoronaBox))//coronaBoxes for soldiers.
				return i;
			else if (isInQuaratine == false && boxes[i]->getIsSoldiers() == true && typeid(*boxes[i]) == typeid(BallotBox))//regular boxes for soldiers.
				return i;
		}

	}
	else//boxes for non soldiers.
		for (int i = 0; i < boxes.size(); i++)
		{
			if (isInQuaratine == false && boxes[i]->getIsSoldiers() == false && typeid(boxes[i][0]) == typeid(BallotBox))//regular boxes.
				return i;
			else if (isInQuaratine == true && boxes[i]->getIsSoldiers() == false && typeid(boxes[i][0]) == typeid(CoronaBox))//coronaBoxes.
				return i;
		}
}
