#include "SemAnalyze.h"


namespace Semantic {
	bool SemAnalyze(Lex::LEX lex, Log::LOG log) {
		bool is_ok = true;
		int j = 0;
		std::vector<std::pair<std::string, std::vector<IT::IDDATATYPE>>> functions_parm;
		std::string function_id;
		std::vector<IT::IDDATATYPE> parms;
		std::vector<std::string> ids;
		for (int i = 0; i < lex.lextable.size; i++) {
			switch (lex.lextable.table[i].lexema) {
			case LEX_DESCRIBE:
				if (std::count(ids.begin(), ids.end(), lex.idtable.table[lex.lextable.table[i + 2].idxTI].id)) {
					Log::WriteError(log, Error::geterrorin(303, lex.lextable.table[j].sn, -1));
					is_ok = false;
				}
				ids.push_back(lex.idtable.table[lex.lextable.table[i + 2].idxTI].id);
				continue;
			case LEX_EQUAL:
				j = i + 1;
				for (j; lex.lextable.table[j].lexema != LEX_SEMICOLON; j++) {
					switch (lex.lextable.table[j].lexema) {
					case LEX_ID:
					case LEX_LITERAL:
						if ((lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype != lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype)) {
							Log::WriteError(log, Error::geterrorin(304, lex.lextable.table[j].sn, -1));
							is_ok = false;
						}
						continue;

					case LEX_LEFTSQ:
						if (lex.lextable.table[j - 1].lexema != LEX_OPERATOR && lex.lextable.table[j - 1].lexema != LEX_LEFTHESIS) {
							do {
								j++;
							} while (lex.lextable.table[j].lexema != LEX_RIGHTSQ);
						}
						continue;
					}
				}
				continue;
			case LEX_ID:
				j = i + 1;
				if (lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::F && lex.lextable.table[i - 1].lexema != LEX_FUNCTION) {
					for (const auto& elem : functions_parm) {
						if (elem.first == lex.idtable.table[lex.lextable.table[i].idxTI].id) {
							std::vector<IT::IDDATATYPE> buf = elem.second;
							while (lex.lextable.table[j].lexema != LEX_RIGHTSQ) {
								if (lex.lextable.table[j].lexema == LEX_ID || lex.lextable.table[j].lexema == LEX_LITERAL) {
									if (!buf.empty()) {
										if (lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype != buf[0]) {
											is_ok = false;
											Log::WriteError(log, Error::geterrorin(305, lex.lextable.table[j].sn, -1));
										}
										buf.erase(buf.begin());
									}
									else {
										is_ok = false;
										Log::WriteError(log, Error::geterrorin(306, lex.lextable.table[j].sn, -1));
									}
								}
								j++;
							}
							if (!buf.empty()) {
								is_ok = false;
								Log::WriteError(log, Error::geterrorin(306, lex.lextable.table[j].sn, -1));
							}
						}
					}
				}
				else if (std::count(ids.begin(), ids.end(), lex.idtable.table[lex.lextable.table[i].idxTI].id) && lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::V == 0) {
					Log::WriteError(log, Error::geterrorin(307, lex.lextable.table[i].sn, -1));
					is_ok = false;
				}
				continue;

			case LEX_FUNCTION:
				for (const auto& elem : functions_parm) {
					if (elem.first == lex.idtable.table[lex.lextable.table[i + 1].idxTI].id) {
						Log::WriteError(log, Error::geterrorin(308, lex.lextable.table[i + 1].sn, -1));
						is_ok = false;
					}
				}

				function_id = lex.idtable.table[lex.lextable.table[i + 1].idxTI].id;
				j = i + 2;
				do {
					if (lex.lextable.table[j].lexema == LEX_ID || lex.lextable.table[j].lexema == LEX_LITERAL) {
						parms.push_back(lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype);
					}
					j++;
				} while (lex.lextable.table[j].lexema != LEX_RIGHTSQ);
				functions_parm.push_back(std::make_pair(function_id, parms));
				parms.clear();

				if (lex.lextable.table[i].lexema == LEX_FUNCTION) {
					j = i + 1;
					int type = lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype;
					do {
						j++;
					} while ((lex.lextable.table[j].lexema != LEX_GIVE));
					if (lex.idtable.table[lex.lextable.table[j + 1].idxTI].iddatatype != type) {
						Log::WriteError(log, Error::geterrorin(309, lex.lextable.table[j].sn, -1));
						is_ok = false;
					}
				}
				continue;
			}
		}
		return is_ok;
	}
}