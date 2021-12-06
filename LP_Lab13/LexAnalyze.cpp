#include "stdafx.h"
#include "LexAnalyze.h"
#include "Divide.h"
#include "FST.h"
#include "Regulars.h"

#define DIV			'|'
#define SPACE		' '
#define PLUS		'+'
#define MINUS		'-'
#define STAR		'*'
#define DIRSLASH	'/'
#define SHIFTL		'<<'
#define SHIFTR		'>>'
#define EQUAL		'='

using namespace fst;
using namespace LT;
namespace Lex {
	LEX LexAnalyze(Log::LOG log, In::IN in) {
		LEX lex;
		LexTable lexemTable = Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);

		char** word = new char* [max_word];
		for (int i = 0; i < max_word; i++)
			word[i] = new char[size_word] {NULL};

		do {
			word = divide(in.text, in.size);
		} while (word == NULL);


		for (int i = 0; word[i]; i++) {
			cout << word[i];
		}
		cout << endl;

		int indexOfLex = 0;
		int line = 1;
		int position = 0;
		int indexOfId = 0;
		int bufPos = 0;
		int countOfMain = 0;
		int literalCounter = 1;

		char* prefix = new char[10]{ "" };
		char* bufprefix = new char[10]{ "" };
		char* oldprefix = new char[10]{ "" };
		char emptyString[] = "";
		char* charclit = new char[10]{ "" };
		char* bufL = new char[TI_STR_MAXSIZE];
		char* lit = new char[5]{ "Lit " };
		char* nameOfLiteral = new char[10]{ "" };


		bool findDescribe = false;
		bool findType = false;
		bool findFunction = false;
		bool findParm = false;
		bool findMain = false;

		IT::Entry entryIT;
		for (int i = 0; word[i] != NULL; i++, indexOfLex++) {
			bool findSameID = false;

			FST describeFst(word[i], FST_DESCRIBE);
			if (execute(describeFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_DESCRIBE, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				findDescribe = true;
				continue;
			}

			FST booleanFst(word[i], FST_BOOLEAN);
			if (execute(booleanFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_BOOLEAN, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::BOOL;
				continue;
			}

			FST ubyteFst(word[i], FST_UBYTE);
			if (execute(ubyteFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_UBYTE, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::UBYTE;
				continue;
			}

			FST integerFst(word[i], FST_INTEGER);
			if (execute(integerFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_INTEGER, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::INT;
				continue;
			}

			FST stringFst(word[i], FST_STR);
			if (execute(stringFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_STR, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::STR;
				continue;
			}

			FST functionFst(word[i], FST_FUNCTION);
			if (execute(functionFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				findFunction = true;
				entryIT.idtype = IT::F;
				continue;
			}

			FST giveFst(word[i], FST_GIVE);
			if (execute(giveFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_GIVE, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				continue;
			}

			FST speakFst(word[i], FST_SPEAK);
			if (execute(speakFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_SPEAK, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				continue;
			}

			FST mainFst(word[i], FST_MAIN);
			if (execute(mainFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_MAIN, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				strcpy(oldprefix, prefix);
				strcpy(prefix, word[i]);
				strcpy(entryIT.visibility, emptyString);
				findMain = true;
				countOfMain++;
				continue;
			}

			FST literalTrueFst(word[i], FST_TRUE);
			FST literalFalseFst(word[i], FST_FALSE);
			if (execute(literalTrueFst) || execute(literalFalseFst)) {
				int value;
				if (!strcmp((char*)word[i], "true")) value = 1;
				else value = 0;

				for (int k = 0; k < idtable.size; k++) {
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::BOOL) {
						LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lexemTable, entryLT);
						findSameID = true;
						break;
					}
				}

				if (findSameID) continue;

				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::BOOL;
				entryIT.value.vbool = value;
				entryIT.idxFirstLE = indexOfLex;
				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, lit);
				word[i] = strcat(bufL, charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};

				LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, IT::IsId(idtable, word[i]), line);
				LT::Add(lexemTable, entryLT);
				continue;
			}

			FST identifFst(word[i], FST_ID);
			if (execute(identifFst)) {
				if (findFunction) {
					int idx = IT::IsId(idtable, word[i]);
					if (idx != TI_NULLIDX) {
						Log::WriteError(log, Error::geterrorin(308, line, -1));
					}
				}
				else {
					int idx = IT::IsId(idtable, word[i]);
					if (idx != TI_NULLIDX) {
						Entry entryLT = WriteEntry(entryLT, LEX_ID, idx, line);
						Add(lexemTable, entryLT);
						findFunction = false;
						continue;
					}
					strcpy(bufprefix, prefix);
					word[i] = strcat(bufprefix, word[i]);
					idx = IT::IsId(idtable, word[i]);
					if (idx != TI_NULLIDX) {
						if (findDescribe == true)
							throw ERROR_THROW_IN(122, line, position);
						Entry entryLT = WriteEntry(entryLT, LEX_ID, idx, line);
						Add(lexemTable, entryLT);
						continue;
					}
				}

				findDescribe = false;
				if (findParm) {
					entryIT.idtype = IT::P;
					idtable.table[bufPos].countOfPar++;
					strcpy(entryIT.visibility, prefix);
				}
				else if (!findFunction) {
					entryIT.idtype = IT::V;
					strcpy(entryIT.visibility, prefix);
					if (entryIT.iddatatype == IT::INT)
						entryIT.value.vint = TI_INT_DEFAULT;
					if (entryIT.iddatatype == IT::UBYTE)
						entryIT.value.vint = TI_UBYTE_DEFAULT;
					/*else if (entryIT.iddatatype == IT::BOOL)
						entryIT.value.vint = TI_BOOL_DEFAULT;*/
					else if (entryIT.iddatatype == IT::STR) {
						entryIT.value.vstr.len = 0;
						memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
					}
				}
				else {
					strcpy(oldprefix, prefix);
					strcpy(prefix, word[i]);
				}

				entryIT.idxFirstLE = indexOfLex;
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};
				findFunction = false;
				findType = false;
				Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				Add(lexemTable, entryLT);
				continue;
			}

			

			/*FST literalUbyteFst(word[i], FST_UBYTELIT);
			if (execute(literalUbyteFst)) {
				int value = atoi((char*)word[i]);
				for (int k = 0; k < idtable.size; k++) {
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::UBYTE) {
						Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						Add(lexemTable, entryLT);
						findSameID = true;
						break;
					}
				}

				if (findSameID) continue;
				Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, indexOfId++, line);
				Add(lexemTable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::UBYTE;
				entryIT.value.vint = value;
				entryIT.idxFirstLE = indexOfLex;
				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, lit);
				word[i] = strcat(bufL, charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}*/

			FST literalIntFst(word[i], FST_INTLIT);
			if (execute(literalIntFst)) {
				int value = atoi((char*)word[i]);
				for (int k = 0; k < idtable.size; k++) {
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && (idtable.table[k].iddatatype == IT::INT || idtable.table[k].iddatatype == IT::UBYTE)) {
						Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						Add(lexemTable, entryLT);
						findSameID = true;
						break;
					}
				}

				if (findSameID) continue;
				Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, indexOfId++, line);
				Add(lexemTable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxFirstLE = indexOfLex;
				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, lit);
				word[i] = strcat(bufL, charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}

			
			FST literalStringFst(word[i], FST_STRLIT);
			if (execute(literalStringFst)) {
				int length = strlen(word[i]);
				for (int k = 0; k < length; k++)
					word[i][k] = word[i][k + 1];
				word[i][length - 2] = 0;

				for (int k = 0; k < idtable.size; k++) {
					if (!(strcmp(idtable.table[k].value.vstr.str, word[i]))) {
						findSameID = true;
						Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						Add(lexemTable, entryLT);
						break;
					}
				}
				if (findSameID) continue;

				Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, indexOfId++, line);
				Add(lexemTable, entryLT);
				strcpy(entryIT.value.vstr.str, word[i]);
				entryIT.value.vstr.len = length - 2;
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::STR;
				entryIT.idxFirstLE = indexOfLex;

				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, lit);
				nameOfLiteral = strcat(bufL, (char*)charclit);
				strcpy(entryIT.id, nameOfLiteral);
				IT::Add(idtable, entryIT);
				entryIT = {};
				continue;
			}

			FST operatorFst(word[i], FST_OPERATOR);
			if (execute(operatorFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, indexOfId++, line);
				switch (word[i][0]) {
				case SHIFTL: case SHIFTR:
					entryLT.priority = 1;
					break;
				case PLUS: case MINUS:
					entryLT.priority = 2;
					break;
				case DIRSLASH: case STAR: 
					entryLT.priority = 3;
					break;
				}
				Add(lexemTable, entryLT);
				strcpy(entryIT.id, word[i]);
				entryIT.idxFirstLE = indexOfLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue;
			}

			FST semicolonFst(word[i], FST_SEMICOLON);
			if (execute(semicolonFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				continue;
			}

			FST commaFst(word[i], FST_COMMA);
			if (execute(commaFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				entryLT.priority = 1;
				Add(lexemTable, entryLT);
				continue;
			}

			FST leftBraceFst(word[i], FST_LEFTBRACE);
			if (execute(leftBraceFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				continue;
			}

			FST rightBraceFst(word[i], FST_RIGHTBRACE);
			if (execute(rightBraceFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_BRACELET, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				continue;
			}

			FST leftThesisFst(word[i], FST_LEFTHESIS);
			if (execute(leftThesisFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_LEFTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lexemTable, entryLT);
				if (idtable.table[i - 1].idtype == IT::F)
					findParm = true;
				bufPos = indexOfId - 1;
				continue;
			}

			FST rightThesisFst(word[i], FST_RIGHTHESIS);
			if (execute(rightThesisFst)) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_RIGHTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				if (findParm && word[i + 1][0] != LEX_LEFTBRACE && word[i + 2][0] != LEX_LEFTBRACE)
					strcpy(prefix, oldprefix);
				findParm = false;
				LT::Add(lexemTable, entryLT);
				continue;
			}

			FST equalFst(word[i], FST_EQUAL);
			if (execute(equalFst)) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lexemTable, entryLT);
				continue;
			}

			position += strlen(word[i]);
			if (word[i][0] == DIV) {
				line++;
				position = 0;
				indexOfLex--;
				continue;
			}

			throw ERROR_THROW_IN(108, line, position);
		}


		if (!findMain) throw ERROR_THROW(2);
		if (countOfMain > 1) throw ERROR_THROW(700);

		lex.idtable = idtable;
		lex.lextable = lexemTable;
		return lex;
	}

	void Synchronyze(Lex::LEX& lex) {
		bool* is_changed = new bool[lex.idtable.size]{ false };
		for (int i = 0; i < lex.lextable.size; i++) {
			if (lex.lextable.table[i].idxTI != -1 && !is_changed[lex.lextable.table[i].idxTI]) {
				lex.idtable.table[lex.lextable.table[i].idxTI].idxFirstLE = i;
				is_changed[lex.lextable.table[i].idxTI] = true;
			}
		}
		delete[] is_changed;
	}
}