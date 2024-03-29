#pragma once
#include "GRBH.h"
#define GRB_ERROR_SERIES 600
#define NS(n) GRBH::Rule::Chain::N(n)
#define TS(n) GRBH::Rule::Chain::T(n)
#define ISNS(n) GRBH::Rule::Chain::isN(n)

namespace GRBH {
	Greibach greibach(
		NS('S'), TS('$'),
		10,
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,
			4,
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('g'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('['), NS('F'), TS(']'), TS('{'), NS('N'), TS('g'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('['), NS('F'), TS(']'), TS('{'), NS('N'), TS('g'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('g'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 1,
			16,
			Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'),TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('s'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('s'), NS('E'), TS(';')),
			Rule::Chain(4, TS('n'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('n'), NS('E'), TS(';')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(9, TS('c'), TS('['), NS('W'), TS(']'), TS('{'), NS('C'), TS('}'), TS('e'), TS(';')),
		    Rule::Chain(10, TS('c'), TS('['), NS('W'), TS(']'), TS('{'), NS('C'), TS('}'), TS('e'), TS(';'), NS('N')),
			Rule::Chain(9, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS(';')),
			Rule::Chain(9, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS(';'), NS('N')),
			Rule::Chain(13, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS('o'), TS('{'), NS('U'), TS('}'), TS(';'), NS('N')),
			Rule::Chain(12, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS('o'), TS('{'), NS('U'), TS('}'), TS(';'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 2,
			8,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('['), NS('W'), TS(']')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('['), NS('W'), TS(']'), NS('M'))
		),
		
		Rule(
			NS('F'), GRB_ERROR_SERIES + 3,
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 4,
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 5,
			2,
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		),
		Rule(
			NS('K'), GRB_ERROR_SERIES + 6,   
			2,
			Rule::Chain(3, TS('['), NS('W'), TS(']')),
			Rule::Chain(2, TS('['), TS(']'))
		),
		Rule(
			NS('C'), GRB_ERROR_SERIES + 7,
			16,
			Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('C')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('C')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('C')),
			Rule::Chain(4, TS('s'), NS('E'), TS(';'), NS('C')),
			Rule::Chain(3, TS('s'), NS('E'), TS(';')),
			Rule::Chain(4, TS('n'), NS('E'), TS(';'), NS('C')),
			Rule::Chain(3, TS('n'), NS('E'), TS(';')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(9, TS('c'), TS('['), NS('W'), TS(']'), TS('{'), NS('C'), TS('}'), TS('e'), TS(';')),
			Rule::Chain(10, TS('c'), TS('['), NS('W'), TS(']'), TS('{'), NS('C'), TS('}'), TS('e'), TS(';'), NS('C')),
			Rule::Chain(9, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS(';')),
			Rule::Chain(9, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS(';'), NS('C')),
			Rule::Chain(12, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS('o'), TS('{'), NS('U'), TS('}'), TS(';')),
			Rule::Chain(13, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS('o'), TS('{'), NS('U'), TS('}'), TS(';'), NS('C'))
		),
		Rule(

			NS('U'), GRB_ERROR_SERIES + 8,
			16,
			Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('U')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('U')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('U')),
			Rule::Chain(4, TS('s'), NS('E'), TS(';'), NS('U')),
			Rule::Chain(3, TS('s'), NS('E'), TS(';')),
			Rule::Chain(4, TS('n'), NS('E'), TS(';'), NS('U')),
			Rule::Chain(3, TS('n'), NS('E'), TS(';')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(9, TS('c'), TS('['), NS('W'), TS(']'), TS('{'), NS('U'), TS('}'), TS('e'), TS(';')),
			Rule::Chain(10, TS('c'), TS('['), NS('W'), TS(']'), TS('{'), NS('U'), TS('}'), TS('e'), TS(';'), NS('U')),
			Rule::Chain(9, TS('w'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS(';')),
			Rule::Chain(9, TS('w'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS(';'), NS('U')),
			Rule::Chain(12, TS('w'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS('o'), TS('{'), NS('U'), TS('}'), TS(';')),
			Rule::Chain(13, TS('w'), TS('('), NS('R'), TS(')'), TS('{'), NS('U'), TS('}'), TS('o'), TS('{'), NS('U'), TS('}'), TS(';'), NS('U'))
		),
		Rule(
			NS('R'), GRB_ERROR_SERIES + 9,
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('i'), TS('v'), TS('i')),
			Rule::Chain(3, TS('i'), TS('v'), TS('l')),
			Rule::Chain(3, TS('l'), TS('v'), TS('i'))
		)
	);
}