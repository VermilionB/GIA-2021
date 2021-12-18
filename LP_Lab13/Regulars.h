#pragma once
#include "FST.h"
using namespace fst;

#define FST_DESCRIBE 9, \
	NODE(1, RELATION('d', 1)), NODE(1, RELATION('e', 2)), NODE(1, RELATION('s', 3)), NODE(1, RELATION('c', 4)), NODE(1, RELATION('r', 5)), NODE(1, RELATION('i', 6)), NODE(1, RELATION('b', 7)), NODE(1, RELATION('e', 8)), NODE()
#define FST_BOOLEAN 8, \
	NODE(1, RELATION('b', 1)), NODE(1, RELATION('o', 2)), NODE(1, RELATION('o', 3)), NODE(1, RELATION('l', 4)), NODE(1, RELATION('e', 5)), NODE(1, RELATION('a', 6)), NODE(1, RELATION('n', 7)), NODE()
#define FST_UBYTE 6, \
	NODE(1, RELATION('u', 1)), NODE(1, RELATION('b', 2)), NODE(1, RELATION('y', 3)), NODE(1, RELATION('t', 4)), NODE(1, RELATION('e', 5)), NODE()
#define FST_INTEGER 8, \
	NODE(1, RELATION('i', 1)), NODE(1, RELATION('n', 2)), NODE(1, RELATION('t', 3)), NODE(1, RELATION('e', 4)), NODE(1, RELATION('g', 5)), NODE(1, RELATION('e', 6)), NODE(1, RELATION('r', 7)), NODE()
#define FST_STR 4, \
	NODE(1, RELATION('s', 1)), NODE(1, RELATION('t', 2)), NODE(1, RELATION('r', 3)), NODE()
#define FST_FUNCTION 9,	\
	NODE(1, RELATION('f', 1)),\
	NODE(1, RELATION('u', 2)),\
	NODE(1, RELATION('n', 3)),\
	NODE(1, RELATION('c', 4)),\
	NODE(1, RELATION('t', 5)),\
	NODE(1, RELATION('i', 6)),\
	NODE(1, RELATION('o', 7)),\
	NODE(1, RELATION('n', 8)),\
	NODE()
#define FST_MAIN 5, \
	NODE(1, RELATION('m', 1)), NODE(1, RELATION('a', 2)), NODE(1, RELATION('i', 3)), NODE(1, RELATION('n', 4)), NODE()
#define FST_GIVE 5, \
	NODE(1, RELATION('g', 1)), NODE(1, RELATION('i', 2)), NODE(1, RELATION('v', 3)), NODE(1, RELATION('e', 4)), NODE()
#define FST_SPEAK 6, \
	NODE(1, RELATION('s', 1)), NODE(1, RELATION('p', 2)), NODE(1, RELATION('e', 3)), NODE(1, RELATION('a', 4)), NODE(1, RELATION('k', 5)), NODE()
#define FST_SPEAKFN 8, \
	NODE(1, RELATION('s', 1)), NODE(1, RELATION('p', 2)), NODE(1, RELATION('e', 3)), NODE(1, RELATION('a', 4)), NODE(1, RELATION('k', 5)), NODE(1, RELATION('f', 6)), NODE(1, RELATION('n', 7)), NODE()
#define FST_ID 1,	\
	NODE(26,	\
	RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0), RELATION('e', 0), RELATION('f', 0),\
	RELATION('g', 0), RELATION('h', 0), RELATION('i', 0), RELATION('j', 0), RELATION('k', 0), RELATION('l', 0),\
	RELATION('m', 0), RELATION('n', 0), RELATION('o', 0), RELATION('p', 0), RELATION('q', 0), RELATION('r', 0),\
	RELATION('s', 0), RELATION('t', 0), RELATION('u', 0), RELATION('v', 0), RELATION('w', 0), RELATION('x', 0),\
	RELATION('y', 0), RELATION('z', 0))

#define FST_UBYTELIT 1,	\
	NODE(10,	\
	RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0), RELATION('5', 0),\
    RELATION('6', 0), RELATION('7', 0), RELATION('8', 0), RELATION('9', 0), RELATION('0', 0))
	
#define FST_STRLIT 3,	\
	NODE(1, RELATION('\'', 1)),\
	NODE(154, \
			RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1),\
			RELATION('e', 1), RELATION('f', 1), RELATION('g', 1), RELATION('h', 1),\
			RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),\
			RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1),\
			RELATION('q', 1), RELATION('r', 1), RELATION('s', 1), RELATION('t', 1),\
			RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),\
			RELATION('y', 1), RELATION('z', 1),\
			RELATION('A', 1), RELATION('B', 1), RELATION('C', 1), RELATION('D', 1),\
			RELATION('E', 1), RELATION('F', 1), RELATION('G', 1), RELATION('H', 1),\
			RELATION('I', 1), RELATION('J', 1), RELATION('K', 1), RELATION('L', 1),\
			RELATION('M', 1), RELATION('N', 1), RELATION('O', 1), RELATION('P', 1),\
			RELATION('Q', 1), RELATION('R', 1), RELATION('S', 1), RELATION('T', 1),\
			RELATION('U', 1), RELATION('V', 1), RELATION('W', 1), RELATION('X', 1),\
			RELATION('Y', 1), RELATION('Z', 1),\
			RELATION('à', 1), RELATION('á', 1), RELATION('â', 1), RELATION('ã', 1),\
			RELATION('ä', 1), RELATION('å', 1), RELATION('¸', 1), RELATION('æ', 1),\
			RELATION('ç', 1), RELATION('è', 1), RELATION('é', 1), RELATION('ê', 1),\
			RELATION('ë', 1), RELATION('ì', 1), RELATION('í', 1), RELATION('î', 1),\
			RELATION('ï', 1), RELATION('ð', 1), RELATION('ñ', 1), RELATION('ò', 1),\
			RELATION('ó', 1), RELATION('ô', 1), RELATION('õ', 1), RELATION('ö', 1),\
			RELATION('÷', 1), RELATION('ø', 1), RELATION('ù', 1), RELATION('ü', 1),\
			RELATION('û', 1), RELATION('ú', 1), RELATION('ý', 1), RELATION('þ', 1),\
			RELATION('ÿ', 1),\
			RELATION('À', 1), RELATION('Á', 1), RELATION('Â', 1), RELATION('Ã', 1),\
			RELATION('Ä', 1), RELATION('Å', 1), RELATION('¨', 1), RELATION('Æ', 1),\
			RELATION('Ç', 1), RELATION('È', 1), RELATION('É', 1), RELATION('Ê', 1),\
			RELATION('Ë', 1), RELATION('Ì', 1), RELATION('Í', 1), RELATION('Î', 1),\
			RELATION('Ï', 1), RELATION('Ð', 1), RELATION('Ñ', 1), RELATION('Ò', 1),\
			RELATION('Ó', 1), RELATION('Ô', 1), RELATION('Õ', 1), RELATION('Ö', 1),\
			RELATION('×', 1), RELATION('Ø', 1), RELATION('Ù', 1), RELATION('Ü', 1),\
			RELATION('Û', 1), RELATION('Ú', 1), RELATION('Ý', 1), RELATION('Þ', 1),\
			RELATION('ÿ', 1),\
			RELATION('0', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1),\
			RELATION('4', 1), RELATION('5', 1), RELATION('6', 1), RELATION('7', 1),\
			RELATION('8', 1), RELATION('9', 1),\
			RELATION(' ', 1), RELATION(',', 1), RELATION('.', 1), RELATION(';', 1),\
			RELATION('-', 1), RELATION('+', 1), RELATION('*', 1), RELATION('/', 1),\
			RELATION('=', 1), RELATION(':', 1), RELATION(')', 1), RELATION('(', 1),\
			RELATION('}', 1), RELATION('{', 1), RELATION(']', 1), RELATION('[', 1),\
			RELATION('!', 1), RELATION('?', 1), RELATION('#', 1), RELATION('&', 1),\
			RELATION('>', 1), RELATION('<', 1), RELATION('[', 1), RELATION(']', 1),\
			RELATION('^', 1), \
			RELATION('\'', 2)),\
	NODE()

#define FST_TRUE 5, \
	NODE(1, RELATION('t', 1)), NODE(1, RELATION('r', 2)), NODE(1, RELATION('u', 3)), NODE(1, RELATION('e', 4)), NODE()
#define FST_FALSE 6, \
	NODE(1, RELATION('f', 1)), NODE(1, RELATION('a', 2)), NODE(1, RELATION('l', 3)), NODE(1, RELATION('s', 4)), NODE(1, RELATION('e', 5)), NODE()

#define FST_OPERATOR 2,	\
	NODE(6, RELATION('+', 1), RELATION('-', 1), RELATION('*', 1), RELATION('/', 1), RELATION('<<', 1), RELATION('>>', 1)),\
	NODE()

#define FST_PLUS 2,	\
	NODE(1, RELATION('+', 1)),\
	NODE()

#define FST_MINUS 2,	\
	NODE(1, RELATION('-', 1)),\
	NODE()

#define FST_STAR 2,	\
	NODE(1, RELATION('*', 1)),\
	NODE()

#define FST_DIRSLASH 2,	\
	NODE(1, RELATION('/', 1)),\
	NODE()
#define FST_SHIFTL 3,	\
	NODE(1, RELATION('<', 1)), NODE(1, RELATION('<', 2)),\
	NODE()
#define FST_SHIFTR 3,	\
	NODE(1, RELATION('>', 1)), NODE(1, RELATION('>', 2)),\
	NODE()
#define FST_SEMICOLON 2,	\
	NODE(1, RELATION(';', 1)),\
	NODE()

#define FST_COMMA 2,	\
	NODE(1, RELATION(',', 1)),\
	NODE()

#define FST_LEFTBRACE 2,	\
	NODE(1, RELATION('{', 1)),\
	NODE()

#define FST_RIGHTBRACE 2,	\
	NODE(1, RELATION('}', 1)),\
	NODE()

#define FST_LEFTSQ 2,	\
	NODE(1, RELATION('[', 1)),\
	NODE()

#define FST_RIGHTSQ 2,	\
	NODE(1, RELATION(']', 1)),\
	NODE()

#define FST_LEFTHESIS 2,	\
	NODE(1, RELATION('(', 1)),\
	NODE()

#define FST_RIGHTHESIS 2,	\
	NODE(1, RELATION(')', 1)),\
	NODE()

#define FST_EQUAL 2,	\
	NODE(1, RELATION('=', 1)),\
	NODE()

#define FST_CIRCUIT 8,	\
	NODE(1, RELATION('c', 1)),\
	NODE(1, RELATION('i', 2)),\
	NODE(1, RELATION('r', 3)),\
	NODE(1, RELATION('c', 4)),\
	NODE(1, RELATION('u', 5)),\
	NODE(1, RELATION('i', 6)),\
	NODE(1, RELATION('t', 7)),\
	NODE()

#define FST_STRINGLIB 12,	\
	NODE(1, RELATION('#', 1)),\
	NODE(1, RELATION('u', 2)),\
	NODE(1, RELATION('s', 3)),\
	NODE(1, RELATION('e', 4)),\
	NODE(1, RELATION('l', 5)),\
	NODE(1, RELATION('i', 6)),\
	NODE(1, RELATION('b', 7)),\
	NODE(1, RELATION('_', 8)),\
	NODE(1, RELATION('s', 9)),\
	NODE(1, RELATION('t', 10)),\
	NODE(1, RELATION('r', 11)),\
	NODE()

#define FST_STRLEN 8,	\
	NODE(1, RELATION('_', 1)),\
	NODE(1, RELATION('s', 2)),\
	NODE(1, RELATION('t', 3)),\
	NODE(1, RELATION('r', 4)),\
	NODE(1, RELATION('l', 5)),\
	NODE(1, RELATION('e', 6)),\
	NODE(1, RELATION('n', 7)),\
	NODE()

#define FST_STRCOPY 9,	\
	NODE(1, RELATION('_', 1)),\
	NODE(1, RELATION('s', 2)),\
	NODE(1, RELATION('t', 3)),\
	NODE(1, RELATION('r', 4)),\
	NODE(1, RELATION('c', 5)),\
	NODE(1, RELATION('o', 6)),\
	NODE(1, RELATION('p', 7)),\
	NODE(1, RELATION('y', 8)),\
	NODE()

#define FST_MATHLIB 13,	\
	NODE(1, RELATION('#', 1)),\
	NODE(1, RELATION('u', 2)),\
	NODE(1, RELATION('s', 3)),\
	NODE(1, RELATION('e', 4)),\
	NODE(1, RELATION('l', 5)),\
	NODE(1, RELATION('i', 6)),\
	NODE(1, RELATION('b', 7)),\
	NODE(1, RELATION('_', 8)),\
	NODE(1, RELATION('m', 9)),\
	NODE(1, RELATION('a', 10)),\
	NODE(1, RELATION('t', 11)),\
	NODE(1, RELATION('h', 12)),\
	NODE()

#define FST_RANDOM 8,	\
	NODE(1, RELATION('_', 1)),\
	NODE(1, RELATION('r', 2)),\
	NODE(1, RELATION('a', 3)),\
	NODE(1, RELATION('n', 4)),\
	NODE(1, RELATION('d', 5)),\
	NODE(1, RELATION('o', 6)),\
	NODE(1, RELATION('m', 7)),\
	NODE()

#define FST_EXP 5,	\
	NODE(1, RELATION('_', 1)),\
	NODE(1, RELATION('e', 2)),\
	NODE(1, RELATION('x', 3)),\
	NODE(1, RELATION('p', 4)),\
	NODE()