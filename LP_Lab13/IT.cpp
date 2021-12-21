#include "stdafx.h"
#include "IT.h"
#include "Error.h"
using namespace std;

namespace IT {
	IdTable Create(int size) {
		IdTable* table = new IdTable;
		if (size < TI_MAXSIZE) throw ERROR_THROW(203);
		table->maxsize = size;
		table->size = 0;
		table->table = new Entry[size];
		return *table;
	}

	void Add(IdTable& idtable, Entry entry) {
		if (idtable.size + 1 > idtable.maxsize) throw ERROR_THROW(204);

		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n) {
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0) return i;
		}

		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable) {
		delete[] idtable.table;
	}

	void ShowTable(IdTable& idtable, std::ostream& out) {
		int i, j, numberOP = 0;
		out << setfill('-') << setw(87) << '-' << endl;
		out << "   #" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора"
			<< " | " << "Индекс в ТЛ" << " | " << "Значение" << endl;
		out << setw(87) << '-' << endl;

		for (i = 0, j = 0; i < idtable.size; i++, j++) {
			if (idtable.table[i].idtype == OP) {
				numberOP++;
				j--;
				continue;
			}
			out << setfill('0') << setw(4) << right << j << " | ";
			out << setfill(' ') << setw(13) << left << idtable.table[i].id << " | ";

			switch (idtable.table[i].iddatatype) {
			case BOOL:
				out << setw(10) << left;
				if (idtable.table[i].iddatatype == OP) out << "-" << " | ";
				else out << "boolean" << " | ";
				break;
			case UBYTE:
				out << setw(10) << left;
				if (idtable.table[i].iddatatype == OP) out << "-" << " | ";
				else out << "ubyte" << " | ";
				break;
			case STR:
				out << setw(10) << left;
				if (idtable.table[i].idtype == OP) out << "-" << " | ";
				out << "str" << " | ";
				break;
			default:
				out << setw(10) << left << "unknown" << " | ";
				break;
			}

			switch (idtable.table[i].idtype) {
			case V: out << setw(18) << left << "переменная" << " | "; break;
			case F: out << setw(18) << left << "функция" << " | "; break;
			case P: out << setw(18) << left << "параметр" << " | "; break;
			case L: out << setw(18) << left << "литерал" << " | "; break;
			case OP:
				out << setw(18) << left << "оператор" << " | ";
				numberOP++;
				break;
			default: out << setw(18) << left << "unknown" << " | "; break;
			}
			out << setw(11) << left << idtable.table[i].idxFirstLE << " | ";

			if (idtable.table[i].iddatatype == UBYTE && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				out << setw(18) << left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				out << "[" << idtable.table[i].value.vstr.len << "]\"" << idtable.table[i].value.vstr.str << "\"";
			else if (idtable.table[i].iddatatype == BOOL && (idtable.table[i].idtype == V || idtable.table[i].idtype == L)) {
				out << setw(18) << left << idtable.table[i].value.vbool;
			}
			else out << "-";
			out << endl;
		}

		out << setfill('-') << setw(87) << "-" << endl;
		out << "Количество идентификаторов: " << i - numberOP << endl;
		out << setw(87) << "-" << endl;
	}
}