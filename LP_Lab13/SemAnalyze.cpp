//#include "SemAnalyze.h"
//
//namespace Semantic {
//	bool Analyze(Lex::LEX lex, Log::LOG log) {
//		/*bool is_ok = true;
//		int j = 0;
//		std::vector<std::string> functions_id;
//		for (int i = 0; i < lex.lextable.size; i++) {
//			switch (lex.lextable.table[i].lexema) {
//			case LEX_EQUAL:
//				j = i + 1;
//				for (j; lex.lextable.table[j].lexema != LEX_SEMICOLON; j++) {
//					switch (lex.lextable.table[j].lexema) {
//					case LEX_ID:
//					case LEX_LITERAL:
//						if ((lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype != lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype)) {
//							Log::WriteError(log, Error::geterrorin(312, lex.lextable.table[j].sn, -1));
//							is_ok = false;
//						}
//						continue;
//
//					case LEX_LEFTHESIS:
//						if (lex.idtable.table[lex.lextable.table[j - 1].idxTI].idtype == IT::F) {
//							do {
//								j++;
//							} while (lex.lextable.table[j].lexema != LEX_RIGHTHESIS);
//						}
//						continue;
//					}
//				}
//				continue;
//			case LEX_FUNCTION:
//				if (std::count(functions_id.begin(), functions_id.end(), lex.idtable.table[lex.lextable.table[i + 1].idxTI].id)) {
//					Log::WriteError(log, Error::geterrorin(307, lex.lextable.table[i + 1].sn, -1));
//					is_ok = false;
//				}
//				functions_id.push_back(lex.idtable.table[lex.lextable.table[i + 1].idxTI].id);
//
//				j = i + 1;
//				int type = lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype;
//				do {
//					j++;
//				} while ((lex.lextable.table[j].lexema != LEX_GIVE));
//				int returned_v = lex.idtable.table[lex.lextable.table[j + 1].idxTI].iddatatype;
//				if (returned_v != type) {
//					Log::WriteError(log, Error::geterrorin(314, lex.lextable.table[j].sn, -1));
//					is_ok = false;
//				}
//			}
//		}
//
//		return is_ok;*/
//		bool sem_ok = true;
//
//		for (int i = 0; i < lex.lextable.size; i++)
//		{
//			switch (lex.lextable.table[i].lexema)
//			{
//			case LEX_DESCRIBE:
//			{
//				if (lex.lextable.table[i + 1].lexema != LEX_UBYTE || lex.lextable.table[i + 1].lexema != LEX_STR)
//				{
//					sem_ok = false;
//					Log::WriteError(log, Error::geterrorin(303, lex.lextable.table[i].sn, 0));
//				}
//			}
//			case LEX_DIRSLASH:
//			{
//				int k = i;
//				if (lex.lextable.table[i + 1].lexema == LEX_ID)
//				{
//					for (k; k > 0; k--)
//					{
//						if (lex.lextable.table[k].lexema == LEX_ID)
//						{
//							if (lex.idtable.table[lex.lextable.table[k].idxTI].id == lex.idtable.table[lex.lextable.table[i + 1].idxTI].id)
//							{
//								if (lex.lextable.table[k + 2].lexema == LEX_LITERAL && lex.idtable.table[lex.lextable.table[k + 2].idxTI].value.vint == 0)
//								{
//									sem_ok = false;
//									Log::WriteError(log, Error::geterrorin(311, lex.lextable.table[k].sn, 0));
//								}
//							}
//						}
//					}
//				}
//				if (lex.lextable.table[i + 1].lexema == LEX_LITERAL)
//				{
//					if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].value.vint == 0)
//					{
//						sem_ok = false;
//						Log::WriteError(log, Error::geterrorin(311, lex.lextable.table[k].sn, 0));
//					}
//				}
//				break;
//			}
//			case LEX_EQUAL: // âûðàæåíèå
//			{
//				if (i > 0 && lex.lextable.table[i - 1].idxTI != TI_NULLIDX) // ëåâûé îïåðàíä
//				{
//					IT::IDDATATYPE lefttype = lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype;
//					bool ignore = false;
//
//					for (int k = i + 1; lex.lextable.table[k].lexema != LEX_SEMICOLON; k++)
//					{
//						if (k == lex.lextable.size)
//							break; // ñèíòàêñ îøèáêà - íåò ;
//						if (lex.lextable.table[k].idxTI != TI_NULLIDX) // åñëè èä - ïðîâåðèòü ñîâïàäåíèå òèïîâ
//						{
//							if (!ignore)
//							{
//								IT::IDDATATYPE righttype = lex.idtable.table[lex.lextable.table[k].idxTI].iddatatype;
//								if (lefttype != righttype) // òèïû äàííûõ â âûðàæåíèè íå ñîâïàäàþò
//								{
//									Log::WriteError(log, Error::geterrorin(314, lex.lextable.table[k].sn, 0));
//									sem_ok = false;
//									break;
//								}
//							}
//							// åñëè ëåêñåìà ñðàçó ïîñëå èäåíòèô ñêîáêà - ýòî âûçîâ ôóíêöèè
//							if (lex.lextable.table[k + 1].lexema == LEX_LEFTHESIS)
//							{
//								ignore = true;
//								continue;
//							}
//							// çàêðûâàþùàÿ ñêîáêà ïîñëå ñïèñêà ïàðàìåòðîâ
//							if (ignore && lex.lextable.table[k + 1].lexema == LEX_RIGHTHESIS)
//							{
//								ignore = false;
//								continue;
//							}
//						}
//						if (lefttype == IT::IDDATATYPE::STR) // ñïðàâà òîëüêî ëèòåðàë, èä èëè âûçîâ ñòðîêîâîé ô-öèè
//						{
//							char l = lex.lextable.table[k].lexema;
//							if (l == LEX_PLUS || l == LEX_MINUS || l == LEX_STAR) // âûðàæåíèÿ íåäîïóñòèìû
//							{
//								Log::WriteError(log, Error::geterrorin(316, lex.lextable.table[k].sn, 0));
//								sem_ok = false;
//								break;
//							}
//						}
//					}
//				}
//				break;
//			}
//			case LEX_ID: // ïðîâåðêà òèïà âîçâðàùàåìîãî çíà÷åíèÿ  
//			{
//				IT::Entry e = lex.idtable.table[lex.lextable.table[i].idxTI];
//
//				if (i > 0 && lex.lextable.table[i - 1].lexema == LEX_FUNCTION)
//				{
//					if (e.idtype == IT::IDTYPE::F) //ôóíêöèÿ, íå ïðîöåäóðà
//					{
//						for (int k = i + 1; ; k++)
//						{
//							char l = lex.lextable.table[k].lexema;
//							if (l == LEX_GIVE)
//							{
//								int next = lex.lextable.table[k + 1].idxTI; // ñëåä. çà return
//								if (next != TI_NULLIDX)
//								{
//									// òèï ôóíêöèè è âîçâðàùàåìîãî çíà÷åíèÿ íå ñîâïàäàþò
//									if (lex.idtable.table[next].iddatatype != e.iddatatype)
//									{
//										Log::WriteError(log, Error::geterrorin(714, lex.lextable.table[k].sn, 0));
//										sem_ok = false;
//										break;
//									}
//								}
//								break; // íàøëè exit
//							}
//
//							if (k == lex.lextable.size) break;
//						}
//					}
//				}
//				if (lex.lextable.table[i + 1].lexema == LEX_LEFTSQ && lex.lextable.table[i - 1].lexema != LEX_FUNCTION) // èìåííî âûçîâ
//				{
//					if (e.idtype == IT::IDTYPE::F /*|| e.idtype == IT::IDTYPE::*/) // òî÷íî ôóíêöèÿ
//					{
//						int paramscount = NULL;
//						// ïðîâåðêà ïåðåäàâàåìûõ ïàðàìåòðîâ
//						for (int j = i + 1; lex.lextable.table[j].lexema != LEX_RIGHTSQ; j++)
//						{
//							// ïðîâåðêà ñîîòâåòñòâèÿ ïåðåäàâàåìûõ ïàðàìåòðîâ ïðîòîòèïàì
//							if (lex.lextable.table[j].lexema == LEX_ID || lex.lextable.table[j].lexema == LEX_LITERAL)
//							{
//								paramscount++;
//								if (e.value.params.count == NULL)
//									break;
//								IT::IDDATATYPE ctype = lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype;
//								if (ctype != e.value.params.types[paramscount - 1])
//								{
//									// Íåñîâïàäåíèå òèïîâ ïåðåäàâàåìûõ ïàðàìåòðîâ
//									Log::WriteError(log, Error::geterrorin(309, lex.lextable.table[i].sn, 0));
//									sem_ok = false;
//									break;
//								}
//							}
//							if (j == lex.lextable.size)
//								break;
//						}
//						if (paramscount != e.value.params.count)
//						{
//							// Êîëè÷åñòâî ïåðåäàâàåìûõ è ïðèíèìàåìûõ ïàðàìåòðîâ íå ñîâïàäàåò
//							Log::WriteError(log, Error::geterrorin(715, lex.lextable.table[i].sn, 0));
//							sem_ok = false;
//						}
//						if (paramscount > 9)
//						{
//							// Ñëèøêîì ìíîãî ïàðàìåòðîâ â âûçîâå
//							Log::WriteError(log, Error::geterrorin(716, lex.lextable.table[i].sn, 0));
//							sem_ok = false;
//						}
//					}
//				}
//				break;
//			}
//			//	case LEX_MORE:	case LEX_LESS: case LEX_EQUALS:   case LEX_NOTEQUALS:
//			//	{
//			//		// ëåâûé è ïðàâûé îïåðàíä - ÷èñëîâîé òèï
//			//		bool flag = true;
//			//		if (i > 1 && lex.lextable.table[i - 1].idxTI != TI_NULLIDX)
//			//		{
//			//			if (lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype != IT::IDDATATYPE::NUM)
//			//				flag = false;
//			//		}
//			//		if (lex.lextable.table[i + 1].idxTI != TI_NULLIDX)
//			//		{
//			//			if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].iddatatype != IT::IDDATATYPE::NUM)
//			//				flag = false;
//			//		}
//			//		if (!flag)
//			//		{
//			//			// ñòðîêà èëè íåèçâåñòíûé èä â óñëîâèè
//			//			Log::WriteError(log, Error::geterrorin(317, lex.lextable.table[i].sn, 0));
//			//			sem_ok = false;
//			//		}
//			//		break;
//			//	}
//			//	}
//			//}
//
//			return sem_ok;
//			}
//	}
//}