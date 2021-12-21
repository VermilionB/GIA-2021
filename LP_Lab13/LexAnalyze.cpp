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
#define SHIFTL		"<<"
#define SHIFTR		">>"
#define MORE		"greater"
#define LESS		"less"
#define EQU			"=="
#define NEQU		"!="
#define EQUAL		'='

using namespace fst;
using namespace LT;
namespace Lex {
	LEX LexAnalyze(Log::LOG log, In::IN in, std::stack<std::string>& libraries) {
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

		int is_circuit = 0;
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
		char* lit = new char[5]{ "Lit" };
		char* nameOfLiteral = new char[10]{ "" };

		stack<std::string> functions_stack;
		bool findDescribe = false;
		bool findType = false;
		bool findFunction = false;
		bool findParm = false;
		bool findStrLib = false;
		bool findMathLib = false;
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

			FST speakfnFst(word[i], FST_SPEAKFN);
			if (execute(speakfnFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_SPEAKFN, LT_TI_NULLIDX, line);
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
				functions_stack.push(word[i]);
				findMain = true;
				countOfMain++;
				continue;
			}

			FST circuitFst(word[i], FST_CIRCUIT);
			if (execute(circuitFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_CIRCUIT, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				is_circuit++;
				continue;
			}

			FST endFst(word[i], FST_END);
			if (execute(endFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_END, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				continue;
			}
			FST providedFst(word[i], FST_PROVIDED);
			if(execute(providedFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_PROVIDED, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				is_circuit++;
				continue;
			}
			FST elseFst(word[i], FST_ELSE);
			if (execute(elseFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_ELSE, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				is_circuit++;
				continue;
			}

			FST strcopyFst(word[i], FST_STRCOPY);
			if(execute(strcopyFst) && findStrLib) {
				if (int idx = IT::IsId(idtable, word[i]) == TI_NULLIDX) {
					entryIT.idtype = IT::F;
					entryIT.iddatatype = IT::STR;
					entryIT.idxFirstLE = indexOfLex;
					strcpy(entryIT.id, word[i]);
					IT::Add(idtable, entryIT);
					entryIT = {};
				}
				findFunction = true;
				Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				Add(lexemTable, entryLT);
				findFunction = false;

				continue;
			}

			FST strlenFst(word[i], FST_STRLEN);
			if (execute(strlenFst) && findStrLib) {
				if (int idx = IT::IsId(idtable, word[i]) == TI_NULLIDX) {
					entryIT.idtype = IT::F;
					entryIT.iddatatype = IT::UBYTE;
					entryIT.idxFirstLE = indexOfLex;
					strcpy(entryIT.id, word[i]);
					IT::Add(idtable, entryIT);
					entryIT = {};
				}
				findFunction = true;

				Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				Add(lexemTable, entryLT);
				findFunction = false;

				continue;
			}
			

			FST randomFst(word[i], FST_RANDOM);
			if (execute(randomFst) && findMathLib) {
				if (int idx = IT::IsId(idtable, word[i]) == TI_NULLIDX) {
					entryIT.idtype = IT::F;
					entryIT.iddatatype = IT::UBYTE;
					entryIT.idxFirstLE = indexOfLex;
					strcpy(entryIT.id, word[i]);
					IT::Add(idtable, entryIT);
					entryIT = {};
				}
				findFunction = true;

				Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				Add(lexemTable, entryLT);
				findFunction = false;

				continue;
			}

			FST expFst(word[i], FST_EXP);
			if (execute(expFst) && findMathLib) {
				if (int idx = IT::IsId(idtable, word[i]) == TI_NULLIDX) {
					entryIT.idtype = IT::F;
					entryIT.iddatatype = IT::UBYTE;
					entryIT.idxFirstLE = indexOfLex;
					strcpy(entryIT.id, word[i]);
					IT::Add(idtable, entryIT);
					entryIT = {};
				}
				findFunction = true;

				Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				Add(lexemTable, entryLT);
				findFunction = false;

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
						Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						Add(lexemTable, entryLT);
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

				Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, IT::IsId(idtable, word[i]), line);
				Add(lexemTable, entryLT);
				continue;
			}
			FST operatorFst(word[i], FST_OPERATOR);
			FST shiftRightFst(word[i], FST_SHIFTR);
			FST shiftLeftFst(word[i], FST_SHIFTL);
			FST greaterFst(word[i], FST_GREATER);
			FST lessFst(word[i], FST_LESS);

			if (execute(operatorFst) || execute(shiftLeftFst) || execute(shiftRightFst) || execute(greaterFst) || execute(lessFst)) {
				strcpy(entryIT.id, word[i]);
				entryIT.idxFirstLE = indexOfLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);

				std::map <std::string, int> mapping;
				mapping[SHIFTL] = 1;
				mapping[SHIFTR] = 2;
				mapping[EQU] = 3;
				mapping[NEQU] = 4;
				mapping[MORE] = 5;
				mapping[LESS] = 6;

				switch (mapping[word[i]]) {
				case 1:
					entryLT.priority = 1;
					entryLT.ops = operations::OSHIFTL;
					break;
				case 2:
					entryLT.priority = 1;
					entryLT.ops = operations::OSHIFTR;
					break;
				case 3:
					entryLT.priority = 0;
					entryLT.ops = operations::OEQU;
					break;
				case 4:
					entryLT.priority = 0;
					entryLT.ops = operations::ONEQU;
					break;
				case 5:
					entryLT.priority = 0;
					entryLT.ops = operations::OMORE;
					break;
				case 6:
					entryLT.priority = 0;
					entryLT.ops = operations::OLESS;
					break;
				}

				switch (word[i][0]) {
				case PLUS:
					entryLT.priority = 2;
					entryLT.ops = operations::OPLUS;
					break;
				case MINUS:
					entryLT.priority = 2;
					entryLT.ops = operations::OMINUS;
					break;
				case DIRSLASH:
					entryLT.priority = 3;
					entryLT.ops = operations::ODIV;
					break;
				case STAR:
					entryLT.priority = 3;
					entryLT.ops = operations::OMUL;
					break;
				}
				Add(lexemTable, entryLT);
				continue;
			}

			FST identifFst(word[i], FST_ID);
			if (execute(identifFst)) {
				if (findParm) {
					entryIT.idtype = IT::P;
					findFunction = false;
				}
				else if (findFunction) {
					entryIT.idtype = IT::F;
					functions_stack.push(word[i]);
				}
				else {
					entryIT.idtype = IT::V;
					int idx = IT::IsId(idtable, word[i]);
					if (idx != TI_NULLIDX) {
						Entry entryLT = WriteEntry(entryLT, LEX_ID, idx, line);
						Add(lexemTable, entryLT);
						entryIT = { };
						
						continue;
					}
					if (entryIT.iddatatype == IT::UBYTE)
						entryIT.value.vint = TI_UBYTE_DEFAULT;
					else if (entryIT.iddatatype == IT::STR) {
						entryIT.value.vstr.len = 0;
						memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
					}
				}

				entryIT.idxFirstLE = indexOfLex;
				if (entryIT.idtype != IT::F && !functions_stack.empty()) {
					strcpy(bufprefix, functions_stack.top().c_str());
					word[i] = strcat(bufprefix, word[i]);
				}
				strcpy(entryIT.id, word[i]);
				int idx = IT::IsId(idtable, word[i]);
				if (idx == TI_NULLIDX)
					IT::Add(idtable, entryIT);
				Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				Add(lexemTable, entryLT);
				entryIT = { };
				//findFunction = false;
				continue;
			}

			FST literalUbyteFst(word[i], FST_UBYTELIT);
			if (execute(literalUbyteFst)) {
				int value = atoi((char*)word[i]);
				if (value > 255 || value < 0) {
					Log::WriteError(log, Error::geterrorin(206, line, -1));
				}
				
				for (int k = 0; k < idtable.size; k++) {
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::UBYTE) {
						Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						Add(lexemTable, entryLT);
						findSameID = true;
						break;
					}
				}

				if (findSameID) continue;
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::UBYTE;
				entryIT.value.vint = value;
				entryIT.idxFirstLE = indexOfLex;
				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, lit);
				word[i] = strcat(bufL, charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, IT::IsId(idtable, word[i]), line);
				Add(lexemTable, entryLT);
				entryIT = {};
				continue;
			}

			FST ubyteLitHexFst(word[i], FST_UBLITHEX);
			if (execute(ubyteLitHexFst)) {
				char* numBuf = new char;
				int j = 0;
				for (int k = 0; k < strlen(word[i] - 1); k++, j++) {
					numBuf[j] = word[i][k];
				}
				numBuf[strlen(numBuf) - 1] = '\0';
				int value = strtol(numBuf, NULL, 16);
				
				if (value > 255 || value < 0) {
					Log::WriteError(log, Error::geterrorin(206, line, -1));
				}

				for (int k = 0; k < idtable.size; k++) {
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::UBYTE) {
						Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						Add(lexemTable, entryLT);
						findSameID = true;
						break;
					}
				}

				if (findSameID) continue;
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::UBYTE;
				entryIT.value.vint = value;
				entryIT.idxFirstLE = indexOfLex;
				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, lit);
				word[i] = strcat(bufL, charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, IT::IsId(idtable, word[i]), line);
				Add(lexemTable, entryLT);
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
				int k = 0;
				for (k = 0; k < idtable.size; k++) {
					if (!(strcmp(idtable.table[k].value.vstr.str, word[i])))
						break;
				}
				Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
				Add(lexemTable, entryLT);
				entryIT = {};
				continue;
			}

			FST strlibFst(word[i], FST_STRINGLIB);
			if (execute(strlibFst)) {
				libraries.push("str");
				findStrLib = true;
				continue;
			}

			FST mathlibFst(word[i], FST_MATHLIB);
			if (execute(mathlibFst)) {
				libraries.push("math");
				findMathLib = true;
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

			FST leftSqFst(word[i], FST_LEFTSQ);
			if (execute(leftSqFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_LEFTSQ, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				Add(lexemTable, entryLT);
				if (findFunction)
					findParm = true;
				continue;
			}

			FST rightSqFst(word[i], FST_RIGHTSQ);
			if (execute(rightSqFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_RIGHTSQ, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				findParm = false;
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
				Add(lexemTable, entryLT);
				
				continue;
			}

			FST rightThesisFst(word[i], FST_RIGHTHESIS);
			if (execute(rightThesisFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_RIGHTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				
				Add(lexemTable, entryLT);
				continue;
			}

			FST equalFst(word[i], FST_EQUAL);
			if (execute(equalFst)) {
				Entry entryLT = WriteEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				Add(lexemTable, entryLT);
				continue;
			}

			position += strlen(word[i]);
			if (word[i][0] == DIV) {
				line++;
				position = 0;
				indexOfLex--;
				continue;
			}

			throw ERROR_THROW_IN(205, line, position);
		}


		if (!findMain) throw ERROR_THROW(302);
		if (countOfMain > 1) throw ERROR_THROW(301);

		lex.idtable = idtable;
		lex.lextable = lexemTable;
		return lex;
	}

	void Synchronize(LEX& lex) {
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