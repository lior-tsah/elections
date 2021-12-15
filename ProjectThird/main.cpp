#include<iostream>
using namespace std;
#pragma warning(disable:4996)

#include "Elections.h"
#include "BallotBox.h"
#include "Functions.h"
#include <vector>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Elections e;
	operateElections(e);
	return 0;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}