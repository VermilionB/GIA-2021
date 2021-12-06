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
#define FST_ID 1,	\
	NODE(26,	\
	RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0), RELATION('e', 0), RELATION('f', 0),\
	RELATION('g', 0), RELATION('h', 0), RELATION('i', 0), RELATION('j', 0), RELATION('k', 0), RELATION('l', 0),\
	RELATION('m', 0), RELATION('n', 0), RELATION('o', 0), RELATION('p', 0), RELATION('q', 0), RELATION('r', 0),\
	RELATION('s', 0), RELATION('t', 0), RELATION('u', 0), RELATION('v', 0), RELATION('w', 0), RELATION('x', 0),\
	RELATION('y', 0), RELATION('z', 0))

#define FST_INTLIT 1,	\
	NODE(10,	\
	RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0), RELATION('5', 0),\
    RELATION('6', 0), RELATION('7', 0), RELATION('8', 0), RELATION('9', 0), RELATION('0', 0))
	
#define FST_STRLIT 4,	\
	NODE(2, RELATION('\'', 1), RELATION('\'', 2)),\
	NODE(158,	\
	RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1), RELATION('f', 1),\
	RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),\
	RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1), RELATION('r', 1),\
	RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),\
	RELATION('y', 1), RELATION('z', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1),\
	RELATION('5', 1), RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),\
	\
	RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),\
	RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),\
	RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),\
	RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),\
	RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),\
	RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION(' ', 1), RELATION('.', 1), RELATION(',', 1),\
	RELATION('?', 1), RELATION('!', 1), RELATION(';', 1), RELATION(':', 1), RELATION('-', 1), RELATION(')', 1),\
	RELATION('(', 1), \
	\
	RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2), RELATION('e', 2), RELATION('f', 2),\
	RELATION('g', 2), RELATION('h', 2), RELATION('i', 2), RELATION('j', 2), RELATION('k', 2), RELATION('l', 2),\
	RELATION('m', 2), RELATION('n', 2), RELATION('o', 2), RELATION('p', 2), RELATION('q', 2), RELATION('r', 2),\
	RELATION('s', 2), RELATION('t', 2), RELATION('u', 2), RELATION('v', 2), RELATION('w', 2), RELATION('x', 2),\
	RELATION('y', 2), RELATION('z', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2),\
	RELATION('5', 2), RELATION('6', 2), RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2),\
	\
	RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),\
	RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),\
	RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),\
	RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),\
	RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),\
	RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION(' ', 2), RELATION('.', 2), RELATION(',', 2),\
	RELATION('?', 2), RELATION('!', 2), RELATION(';', 2), RELATION(':', 2), RELATION('-', 2), RELATION(')', 2),\
	RELATION('(', 2)),\
	\
	NODE(1, RELATION('\'', 3)),\
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

#define FST_LEFTHESIS 2,	\
	NODE(1, RELATION('(', 1)),\
	NODE()

#define FST_RIGHTHESIS 2,	\
	NODE(1, RELATION(')', 1)),\
	NODE()

#define FST_EQUAL 2,	\
	NODE(1, RELATION('=', 1)),\
	NODE()