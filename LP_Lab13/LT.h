#pragma once
#include "Error.h"
#include "Parm.h"
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffff
#define LEX_BOOLEAN 't'
#define LEX_UBYTE 't'
#define LEX_INTEGER 't'
#define LEX_STR 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_DESCRIBE 'd'
#define LEX_GIVE 'g'
#define LEX_SPEAK 's'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS 'v'
#define LEX_MINUS 'v'
#define LEX_STAR 'v'
#define LEX_DIRSLASH 'v'
#define LEX_OPERATOR 'v'
#define LEX_EQUAL '='
#define LEX_MAIN 'm'
namespace LT {
	struct Entry {
		char lexema;                                          //лексема
		int sn;                                               //номер строки в исходном тексте
		int idxTI;                                            //индекс в ТИ
		char vType = '`';                                     //тип
		int priority = -1;                                    //приоритет
	};
	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
		unsigned char* LexemText;
	};

	LexTable Create(int size);
	Entry WriteEntry(Entry& entry, char lexema, int indx, int line);
	void Add(LexTable &lextable, Entry entry);
	Entry GetEntry(LexTable* lextable, int n);
	void Delete(LexTable* lextable);
	void ShowTable(LexTable lextable, Parm::PARM parm);

}