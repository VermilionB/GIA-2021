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


		MFST_TRACE_START
			unsigned int start_time = clock();
		MFST::Mfst mfst(lex.lextable, GRBH::getGreibach());
		mfst.start();
		unsigned int end_time = clock();
		unsigned int search_time = end_time - start_time;
		std::cout << search_time << std::endl;
		mfst.savededucation();
		mfst.printrules();

		/*if (!Semantic::Analyze(lex, log)) {
			std::cout << "Semantic errors. Check log to get more info";
			exit(-1);
		}*/

		IT::ShowTable(lex.idtable);

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