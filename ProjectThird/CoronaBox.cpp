#include <iostream>
using namespace std;

#include "CoronaBox.h"


bool CoronaBox:: checkIfCitizenDressWell(Citizen& c) const
{
	if (c.getDressWell() == false)
	{
		cout << "You can't vote! Go dress yourself!" << endl << endl;
		return false;
	}
	else
		return true;
}