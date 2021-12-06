#pragma once
#include<iostream>
#include<iomanip>
#include "Log.h"
using namespace std;

namespace fst {

	struct RELATION
	{
		char symbol;
		short nnode;
		RELATION(char c = 0x00, short ns = NULL);
	};

	struct NODE {

		short n_relation;
		RELATION* relations;
		NODE();
		NODE(short n, RELATION rel, ...);
	};

	struct FST
	{
		char* string;
		short position;
		short nstates;
		NODE* nodes;
		short* rstates;
	
		FST(char* s, short ns, NODE n, ...);
	};

	bool execute(FST& fst);
	void checking(char*, Log::LOG, int);
}