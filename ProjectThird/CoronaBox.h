#ifndef __CoronaBox_H
#define __CoronaBox_H

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

#include "BallotBox.h"

class CoronaBox: public BallotBox
{
public:
	CoronaBox(ifstream& in) :BallotBox(in) {  }
	bool checkIfCitizenDressWell(Citizen& c) const;
	CoronaBox(Adress& a, int numOfParties,bool isSoldiers) :BallotBox(a, numOfParties,isSoldiers) {};
	CoronaBox(BallotBox& other, int numOfParties) :BallotBox(other, numOfParties) { };
};


#endif // !__CorunaBox_H
