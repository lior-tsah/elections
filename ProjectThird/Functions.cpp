#include <iostream>
#include <fstream>
using namespace std;
#pragma warning (disable: 4996)

#include "Functions.h"
#include "Elections.h"
#include "BallotBox.h"
#include "Candidate.h"
#include "CoronaBox.h"

enum eOption { ADDBALLOTBOX = 1, ADDCITIZEN, ADDPARTY, ADDCANDIDATE, SHOWBOXES, SHOWCITIZENS,
	           SHOWPARTIES, STARTELECTIONS, SHOWRESULTS, EXIT };

void printingMenu()
{
	cout << "\t\t\tFor adding BallotBox please enter:\t\t\t 1" << endl
		<< "\t\t\tFor adding a citizen please enter:\t\t\t 2" << endl
		<< "\t\t\tFor adding a party please enter:\t\t\t 3" << endl
		<< "\t\t\tFor adding a citizen as a candidate please enter:\t 4" << endl
		<< "\t\t\tFor showing all the BallotBoxes please enter:\t\t 5" << endl
		<< "\t\t\tFor showing all the citizens please enter:\t\t 6" << endl
		<< "\t\t\tFor showing all the Political Parties please enter:\t 7" << endl
		<< "\t\t\tFor starting the elections please enter:\t\t 8" << endl
		<< "\t\t\tFor showing the results of the elections please enter:\t 9" << endl
		<< "\t\t\tFor exit please enter:\t\t\t\t\t 10" << endl << endl;
}

void operateElections(Elections& e)
{
	int option;
	ofstream outFile("Elections.txt", ios::trunc);

	cout << "\t\t\tWelcome to the menu of the elections of" << '\t'
		<<e.GetDateOfElections().monthsArray[e.GetDateOfElections().GetMonth() - 1]
		<< ' ' << e.GetDateOfElections().GetYear() << '!' << endl << endl << endl;
	do
	{
		printingMenu();
		cout << "Please enter your choice:" << endl;
		cin >> option;
		switch (option)
		{
		case ADDBALLOTBOX:
			inputBox(e);
			break;
		case ADDCITIZEN:
			inputCitizen(e);
			break;
		case ADDPARTY:
			inputParty(e);
			break;
		case ADDCANDIDATE:
			inputCandidate(e);
			break;
		case SHOWBOXES:
			e.print(e.GetAllBoxes());
			break;
		case SHOWCITIZENS:
			e.print(e.GetAllVotersArr());
			break;
		case SHOWPARTIES:
			e.print(e.GetAllPartiesArr());
			break;
		case STARTELECTIONS:
			e.ElectionWantToVote();
			cout << "Thank you for your participating!" << endl << endl;

			break;
		case SHOWRESULTS:
			outFile.close();
			e.showResults();
			if (remove("Elections.txt") != 0)
				perror("Error deleting file");
			else
				puts("File successfully deleted");
			return;
			break;
		case EXIT:
			loadToFile(e,outFile);
			return;
			break;
		default:
			cout << "Invalid option.please enter again" << endl << endl;
			break;
		}
	} while (option != EXIT && option != STARTELECTIONS&&option!=SHOWRESULTS);

	do
	{
		cout << "\t\t\tFor showing the results of the elections please enter:\t 9" << endl
			<< "\t\t\tFor exit please enter:\t\t\t\t\t 10" << endl << endl;

		
		cout << "Please enter your choice:" << endl;
		cin >> option;

		switch (option)
		{
		case SHOWRESULTS:
			outFile.close();
			e.showResults();
			if (remove("Elections.txt") != 0)
				perror("Error deleting file");
			else
				puts("File successfully deleted");
			break;
		case EXIT:
			outFile.close();
			if (remove("Elections.txt") != 0)
				perror("Error deleting file");
			else
				puts("File successfully deleted");
			return;
			break;
		default:
			cout << "Invalid option.please enter again" << endl << endl;
			break;
		}
	} while (option != EXIT && option != SHOWRESULTS);
}

void inputBox(Elections& e)
{
	string city, street, numOfBuilding;
	int isSoldiers,type;
	BallotBox* bb = nullptr;

	cin.ignore();
	cout << "Please enter the city of the ballotbox:" << endl;
	getline(cin,city);

	cout << "Please enter the street of the ballotbox:" << endl;
	getline(cin,street);

	cout << "Please enter the num of the builiding:" << endl;
	cin >> numOfBuilding;

	Adress adr(city, street, numOfBuilding);
	cout << "Please enter 1 to box for soldiers,and 0 to box to non-soldiers" << endl;

	do
	{
		cin >> isSoldiers;
		if (isSoldiers != 1 && isSoldiers != 0)
			cout << "Invalid input! please enter again!" << endl;

	} while (isSoldiers != 1 && isSoldiers != 0);

	cout << "Please enter 0 for regular BallotBox and 1 for CoronaBox" << endl;
	do
	{
		cin >> type;
		if (type != 1 && type != 0)
			cout << "Invalid input! please enter again!" << endl;

	} while (type != 1 && type != 0);

	switch (type)
	{
	case 0:
		bb = DBG_NEW BallotBox(adr, (int)e.GetAllPartiesArr().size(), isSoldiers);
		bb->SetId(e.GetAllBoxes().size()+1);
		e.addBallotBox(*bb);
		cout << "The action has been done!" << endl << endl;
		break;

	case 1:
		bb = DBG_NEW  CoronaBox(adr, (int)e.GetAllPartiesArr().size(), isSoldiers);
		bb->SetId(e.GetAllBoxes().size()+1);
		e.addBallotBox(*bb);
		cout << "The action has been done!" << endl << endl;
		break;

	default:
		cout << "Invalid option!" << endl;
		break;
	}
}

void inputCitizen(Elections& e)
{
	long long id;
	string name;
	int year, idBox, choose;
	bool isInQuarantine = false, isDressWell = true,res;
	Citizen* c = nullptr;

	cin.ignore();

	cout << "pleae enter the name of the citizen:" << endl;
	getline(cin, name);

	cout << "enter please id of the citizen(in 9 digits):" << endl;
	cin >> id;

	cout << "enter please the year of the birth of the citizen(in 4 digits):" << endl;
	cin >> year;

	cout << "please enter if you are in quarantine or not" << endl << "0 for not in quarantine and 1 for in quarantine" << endl;
	cin >> isInQuarantine;

	if (isInQuarantine == true)
	{
		cout << "are you well dressed?" << endl << "Enter 0 for no and 1 for yes!" << endl;
		cin >> isDressWell;
	}

	cout << "Enter 1 for only citizen and 2 for candidate" << endl;
	cin >> choose;
	idBox = e.relvantBoxes(year, isInQuarantine);

	bool flg = false;
	switch (choose)
	{
	case 1:

	while (!flg)
	{
		try
		{
			c = DBG_NEW  Citizen(name, id, year, e.GetAllBoxes()[idBox][0], idBox, isInQuarantine);
			c->setDressWell(isDressWell);
			res = e.addCitizen(*c);
			if (res == true)
				cout << "The action has been done!" << endl << endl;
			flg = true;
		}
		catch (long long i)
		{
			cout << id << " is not a valid id!" << endl;
			cout << "please enter id in 9 digits!" << endl;
			cin >> id;
		}
		catch (const char* yearMsg)
		{
			cout << yearMsg << endl;
			cout << "pleae enter year of birth again!" << endl;
			cin >> year;
		}
	}
	break;

	case 2:
	{
		cin.ignore();
		string nameOfParty;
		e.print(e.GetAllPartiesArr());

		cout << "Please enter the name of the party:" << endl;
		getline(cin, nameOfParty);
		Party* p = e.getPoliticalPartyByName(&res, nameOfParty);

		if (p!=nullptr)//the party is valid.
		{
			while (!flg)
			{
				try
				{
					c = DBG_NEW  Candidate(name, id, year, e.GetAllBoxes()[idBox][0], idBox, isInQuarantine, *p);
					p->GetListOfCandidates().push_back(c);
					c->setDressWell(isDressWell);
					res = e.addCitizen(*c);
					if (res == true)
						cout << "The action has been done!" << endl << endl;
					flg = true;
				}
				catch (long long i)
				{
					cout << id << " is not a valid id!" << endl;
					cout << "please enter id in 9 digits!" << endl;
					cin >> id;
				}
				catch (const char* yearMsg)
				{
					cout << yearMsg << endl;
					cout << "pleae enter year of birth again!" << endl;
					cin >> year;
				}
			}
		}
		break;
	}
	default:
		cout << "Invalid option!" << endl;
		break;
	}
}

void inputParty(Elections& e)
{
	eMonth m;
	eSide side;
	string name;
	int sideParty, month, year;

	cin.ignore();
	cout << "Please enter the name of the party:" << endl;
	getline(cin, name);

	cout << "Please enter year founded(in 4 digits):" << endl;
	cin >> year;
	cout << "Please enter month founded between 1 to 12:" << endl;

	do
	{
		cin >> month;
		if (month <= 0 || month>12)
		{
			cout << "Wrong month! please enter again!" << endl;
			cout << "Please enter month founded between 1 to 12:" << endl;
		}
	} while (month <= 0 || month>12);
	m = (eMonth)month;
	Date d(year, m);

	cout << "Please enter side of the party:" << endl;
	cout << "For LEFT enter 0,for CENTER enter 1 and for RIGHT enter 2:" << endl;
	do
	{
		cin >> sideParty;
		if (sideParty < 0 || sideParty>2)
		{
			cout << "Wrong side! please enter again!" << endl;
			cout << "For LEFT enter 0,for CENTER enter 1 and for RIGHT enter 2:" << endl;
		}
	} while (sideParty < 0 || sideParty>2);

	side = (eSide)sideParty;
	Party* pp= DBG_NEW Party(side, d, name);
	pp->setId(e.GetAllPartiesArr().size() + 1);
	bool res=e.addParty(*pp);

	if(res==true)
	cout << "The action has been done!" << endl << endl;

}

void inputCandidate(Elections& e)
{
	long id;
	string partyName;

	e.print(e.GetAllVotersArr());
	cout << endl << "Please enter the id of the citizen from the citizens below that you want to add as a candidate:" << endl;
	cin >> id;
	cout << endl;
	cin.ignore();

	e.print(e.GetAllPartiesArr());
	cout << "Please enter the name of the party from the parties below that you want to add the citizen as her candidate:" << endl;

	getline(cin, partyName);

	bool res=e.addCitizenToCandidate(id, partyName);
	if(res==true)
	cout << "The action has been done!" << endl << endl;
}


void loadToFile(Elections& e,ofstream& file)
{
	file << e.GetAllBoxes().size() << endl;

	for (auto b : e.GetAllBoxes())
		file << *b;

	file << e.GetAllPartiesArr().size();
	for (auto p : e.GetAllPartiesArr())
		file << *p;

	file << endl << e.GetAllVotersArr().size();
	for (auto av : e.GetAllVotersArr())
		file << *av;

	file.close();
	
}