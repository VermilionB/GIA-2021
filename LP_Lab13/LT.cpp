#include "stdafx.h"
#include "LT.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
using namespace Log;
using namespace std;

namespace LT {
	LexTable Create(int size) {
		LexTable* newLexTable = new LexTable;
		if (size > LT_MAXSIZE) throw ERROR_THROW(120);
		newLexTable->maxsize = size;
		newLexTable->size = 0;
		newLexTable->table = new Entry[size];
		return *newLexTable;
	}

	void Add(LexTable& lextable, Entry entry) {
		if (lextable.size + 1 > lextable.maxsize) throw ERROR_THROW(121);
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n) {
		return lextable.table[n];
	}

	void Delete(LexTable& lextable) {
		delete[] lextable.table;
	}

	Entry WriteEntry(Entry& entry, char lexema, int indx, int line) {
		entry.lexema = lexema;
		entry.idxTI = indx;
		entry.sn = line;
		return entry;
	}

	void ShowTable(LexTable lextable, Parm::PARM parm) {
		ofstream out(parm.out);
		int line = 2;
		out << "0001| ";
		for (int i = 0; i < lextable.size; i++) {
			if (lextable.table[i].lexema == ';') {
				out << lextable.table[i].lexema << endl;
				if (i + 1 == lextable.size) break;
				if (line > 999) {
					out << line << "| ";
				}
				else if (line > 99) {
					out << "0" << line << "| ";
				}
				else if (line > 9) {
					out << "00" << line << "| ";
				}
				else out << "000" << line << "| ";
				line++;
			}
			else out << lextable.table[i].lexema;
		}
		out.close();
	}
}
