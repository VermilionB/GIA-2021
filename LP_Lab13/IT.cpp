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

	void ShowTable(IdTable& idtable) {
		int i, j, numberOP = 0;
		cout << setfill('-') << setw(87) << '-' << endl;
		cout << "   #" << " | " << "�������������" << " | " << "��� ������" << " | " << "��� ��������������"
			<< " | " << "������ � ��" << " | " << "��������" << endl;
		cout << setw(87) << '-' << endl;

		for (i = 0, j = 0; i < idtable.size; i++, j++) {
			if (idtable.table[i].idtype == OP) {
				numberOP++;
				j--;
				continue;
			}
			cout << setfill('0') << setw(4) << right << j << " | ";
			cout << setfill(' ') << setw(13) << left << idtable.table[i].id << " | ";

			switch (idtable.table[i].iddatatype) {
			case BOOL:
				cout << setw(10) << left;
				if (idtable.table[i].iddatatype == OP) cout << "-" << " | ";
				else cout << "boolean" << " | ";
				break;
			case UBYTE:
				cout << setw(10) << left;
				if (idtable.table[i].iddatatype == OP) cout << "-" << " | ";
				else cout << "ubyte" << " | ";
				break;
			case INT:
				cout << setw(10) << left;
				if (idtable.table[i].iddatatype == OP) cout << "-" << " | ";
				else cout << "integer" << " | ";
				break;
			case STR:
				cout << setw(10) << left;
				if (idtable.table[i].idtype == OP) cout << "-" << " | ";
				cout << "str" << " | ";
				break;
			default:
				cout << setw(10) << left << "unknown" << " | ";
				break;
			}

			switch (idtable.table[i].idtype) {
			case V: cout << setw(18) << left << "����������" << " | "; break;
			case F: cout << setw(18) << left << "�������" << " | "; break;
			case P: cout << setw(18) << left << "��������" << " | "; break;
			case L: cout << setw(18) << left << "�������" << " | "; break;
			case OP:
				cout << setw(18) << left << "��������" << " | ";
				numberOP++;
				break;
			default: cout << setw(18) << left << "unknown" << " | "; break;
			}
			cout << setw(11) << left << idtable.table[i].idxFirstLE << " | ";

			if ((idtable.table[i].iddatatype == INT || idtable.table[i].iddatatype == UBYTE) && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				cout << setw(18) << left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				cout << "[" << idtable.table[i].value.vstr.len << "]\"" << idtable.table[i].value.vstr.str << "\"";
			else if (idtable.table[i].iddatatype == BOOL && (idtable.table[i].idtype == V || idtable.table[i].idtype == L)) {
				cout << setw(18) << left << idtable.table[i].value.vbool;
			}
			else cout << "-";
			cout << endl;
		}

		cout << setfill('-') << setw(87) << "-" << endl;
		cout << "���������� ���������������: " << i - numberOP << endl;
		cout << setw(87) << "-" << endl;
	}
}