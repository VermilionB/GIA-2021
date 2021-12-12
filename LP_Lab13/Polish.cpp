#include "LexAnalyze.h"
#include "Polish.h"
#include <stack>
#include <queue>


	bool PolishNotation(int i, Lex::LEX& lex) {
		std::stack<LT::Entry> stack;	
		std::queue<LT::Entry> queue;	

		LT::Entry func;					
		func.idxTI = LT_TI_NULLIDX;		
		func.lexema = '@';
		func.sn = lex.lextable.table[i].sn;

		LT::Entry forbidden;			// Запрещенная лексема
		forbidden.idxTI = LT_TI_NULLIDX;
		forbidden.lexema = ' ';
		forbidden.sn = lex.lextable.table[i].sn;

		LT::Entry countFuncParm;		
		countFuncParm.idxTI = LT_TI_NULLIDX;
		countFuncParm.lexema = '0';
		countFuncParm.sn = lex.lextable.table[i].sn;

		int countLexem = 0;				
		int posLexem = i;				
		int countfuncparm_int = 0;		

		bool findFunction = false;			


		for (i; lex.lextable.table[i].lexema != LEX_SEMICOLON; i++, countLexem++) {
			switch (lex.lextable.table[i].lexema) {

			case LEX_ID:
			case LEX_LITERAL:
				queue.push(lex.lextable.table[i]);
				continue;

			case LEX_LEFTHESIS:
				// Если скобка вначале или скобка в скобке. 
				if (lex.lextable.table[i - 1].lexema == LEX_EQUAL || lex.lextable.table[i - 1].lexema == LEX_LEFTHESIS) {
					stack.push(lex.lextable.table[i]);
					continue;
				}
			case LEX_LEFTSQ:
				if (lex.idtable.table[lex.lextable.table[i - 1].idxTI].idtype == IT::F) {
					// Считаем количество параметров в функции
					for (int j = i + 1; lex.lextable.table[j].lexema != LEX_RIGHTSQ; j++)
						if (lex.lextable.table[j].lexema != LEX_COMMA)
							countfuncparm_int++;
					findFunction = true;
					func.sn = lex.lextable.table[i - 1].sn;
					func.idxTI = lex.lextable.table[i - 1].idxTI;
					queue.pop(); // Убрать название функции из таблицы лексем
				}

				stack.push(lex.lextable.table[i]);
				continue;

			case LEX_RIGHTHESIS:
				while (stack.top().lexema != LEX_LEFTHESIS) {
					queue.push(stack.top());
					stack.pop();
					if (stack.empty())
						return false;
				}
				continue;
			case LEX_RIGHTSQ:
				if (findFunction) {
					queue.push(func);
					countFuncParm.lexema += countfuncparm_int;
					queue.push(countFuncParm);
					countFuncParm.lexema -= countfuncparm_int;
					countfuncparm_int = 0;
					findFunction = false;
				}
				stack.pop();
				continue;

			case LEX_OPERATOR:
				while (!stack.empty() && lex.lextable.table[i].priority <= stack.top().priority) {
					queue.push(stack.top());
					stack.pop();
				}
				stack.push(lex.lextable.table[i]);
				continue;
			}
		}

		while (!stack.empty()) {
			if (stack.top().lexema == LEX_LEFTHESIS || stack.top().lexema == LEX_RIGHTHESIS)
				return false;
			queue.push(stack.top());
			stack.pop();
		}
		while (countLexem != 0) {
			if (!queue.empty()) {
				lex.lextable.table[posLexem++] = queue.front();
				queue.pop();
			}
			else {
				lex.lextable.table[posLexem++] = forbidden;
			}
			countLexem--;
		}

		for (int i = 0; i < posLexem; i++) {
			if (lex.lextable.table[i].lexema == LEX_OPERATOR || lex.lextable.table[i].lexema == LEX_LITERAL)
				lex.idtable.table[lex.lextable.table[i].idxTI].idxFirstLE = i;
		}
		return true;
	}

	void PolishStart(Lex::LEX& lex) {
		for (int i = 0; i < lex.lextable.size; i++) {
			if (lex.lextable.table[i].lexema == '=')
				PolishNotation(i + 1, lex);
		}
	}
