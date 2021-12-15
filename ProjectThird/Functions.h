#ifndef __F_H
#define __F_H
#include "Elections.h"


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

void printingMenu();
void inputCitizen(Elections& e);
void inputBox(Elections& e);
void inputParty(Elections& e);
void inputCandidate(Elections& e);
void operateElections(Elections& e);
void loadToFile(Elections& e,ofstream& file);
#endif // !__F_H
