#include "stdafx.h"	
#include "Log.h"	
#include <time.h>
#include "FST.h"

#pragma warning(disable:4996)
using namespace std;

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new ofstream;
		log.stream->open(logfile);
		if (log.stream->fail())
			throw ERROR_THROW(112);
		wcscpy_s(log.logfile, logfile);
		return log;
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;
		int i = 0;
		while (ptr[i] != "")
			*log.stream << ptr[i++];
		*log.stream << endl;
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char temp[100];
		int i = 0;
		while (ptr[i] != L"")
		{
			wcstombs(temp, ptr[i++], sizeof(temp));
			*log.stream << temp;
		}
		*log.stream << endl;
	}
	void WriteLog(LOG log)
	{
		tm* timeinf;
		time_t timet;
		time(&timet);
		timeinf = localtime(&timet);
		char temp[100];
		strftime(temp, sizeof(temp), "\n------------ПРОТОКОЛ------------\n ----%d.%m.%y %T----\n ", timeinf);
		*log.stream << temp;
	}

	void WriteIn(LOG log, In::IN in)
	{
			*log.stream << "\n---- Исходные данные ----\n" << in.text
			<< "\n\nВсего символов: " << in.size
			<< "\n\nВсего строк: " << in.lines
			<< "\n\nПропущено: " << in.ignore << endl;
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char in_text[PARM_MAX_SIZE];
		char out_text[PARM_MAX_SIZE];
		char log_text[PARM_MAX_SIZE];
		wcstombs(in_text, parm.in, PARM_MAX_SIZE);
		wcstombs(out_text, parm.out, PARM_MAX_SIZE);
		wcstombs(log_text, parm.log, PARM_MAX_SIZE);
		*log.stream << "\n ---- Параметры ---- \n\n-in: " << in_text
			<< "\n-out: " << out_text
			<< "\n-log: " << log_text << endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream)
		{
			*log.stream << "\nОшибка " << error.id
				<< ": " << error.msg
				<< "\nСтрока " << error.inext.line
				<< " позиция " << error.inext.col << endl;
			Close(log);
		}
		else
		{
			cout << "\nОшибка " << error.id
				<< ": " << error.msg
				<< "\nСтрока " << error.inext.line
				<< " позиция " << error.inext.col << endl;
		}
	}

	void WriteLexTableLog(LT::LexTable& lextable, LOG log) {
		int i = 0;
		*log.stream << "\n\t\tТаблица лексем" << std::endl;
		*log.stream << std::setfill('-') << std::setw(90) << '-' << std::endl;
		*log.stream << "   #" << " | " << "Лексема" << std::setfill(' ') << std::setw(20) << ' ' << std::left
			<< " | " << "Строка" << std::setw(21) << ' ' << std::left << " | " << "Индекс в ТИ" << std::endl;
		*log.stream << std::setfill('-') << std::setw(90) << '-' << std::endl;
		for (i = 0; i < lextable.size; i++) {
			
			*log.stream << std::setfill('0') << std::setw(4) << std::right << i << " | " << std::setfill(' ')
				<< std::setw(24) << std::left << lextable.table[i].lexema << "   | " << std::setw(24) << std::left
				<< lextable.table[i].sn << "    | ";
			if (lextable.table[i].idxTI == LT_TI_NULLIDX)
				*log.stream << "-" << std::endl;
			else
				*log.stream << std::setw(23) << lextable.table[i].idxTI << std::endl;
		}
		
		*log.stream << std::setfill('-') << std::setw(90) << '-' << std::endl;
		*log.stream << "\tВсего лексем: " << i << std::endl;
		*log.stream << std::setfill('-') << std::setw(90) << '-' << std::endl;
	}

		
	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
	}
}