#pragma once
#define ID_MAXSIZE 10
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x00000000
#define TI_UBYTE_DEFAULT 0x00
#define TI_BOOL_DEFAULT false
#define TI_STR_DEFAULT 0x00

#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255

namespace IT {
	enum IDDATATYPE { STR = 1, BOOL = 2, UBYTE = 3 };
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, OP = 5 };

	struct Entry {
		int idxFirstLE;
		char visibility[ID_MAXSIZE];
		char id[ID_MAXSIZE];

		IDDATATYPE iddatatype;
		IDTYPE idtype;
		int countOfPar = 0;
		union {
			int vint = 0;
			bool vbool;
			struct {
				int len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr;
		} value;
	};

	struct IdTable {
		int maxsize;
		int size;
		Entry* table;
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);

	void Delete(IdTable& idtable);
	void ShowTable(IdTable& idtable, std::ostream& out);
}