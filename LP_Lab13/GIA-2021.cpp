#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "FST.h"
#include "Divide.h"
#include "LexAnalyze.h"
#include "LT.h"
#include "Polish.h"
#include "MFST.h"
#include "GRBH.h"
#include "SemAnalyze.h"
#include "Generation.h"

using namespace fst;
using namespace Lex;
using namespace LT;

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG log = Log::INITLOG;
	try {
		std::stack<std::string> libraries;
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест: ", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);

		LEX lex = LexAnalyze(log, in, libraries);

		MFST::SyntaxAnalyze(lex, log, *log.stream);


		if (Semantic::SemAnalyze(lex, log) == 0) {
			std::cout << "Semantic errors. Check log to get more info";
			exit(-1);
		}

		IT::ShowTable(lex.idtable, *log.stream);
		Synchronize(lex);

		PolishStart(lex);
		Synchronize(lex);
		Log::WriteLexTableLog(lex.lextable, log);
		ShowTable(lex.lextable, *log.stream);
		Gen::Generator Gener(lex.lextable, lex.idtable, parm.out, libraries);
		Log::Close(log);

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	};
}