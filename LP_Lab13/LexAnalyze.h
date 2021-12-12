#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include "In.h"

namespace Lex {
	struct LEX {
		IT::IdTable idtable;
		LT::LexTable lextable;
	};

	LEX LexAnalyze(Log::LOG log, In::IN in, std::stack<std::string>& libraries);
	void Synchronize(Lex::LEX& lex);
}