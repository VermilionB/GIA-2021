#include "Generation.h"

using namespace std;

namespace Gen {
	Generator::Generator(LT::LexTable plexT, IT::IdTable pidT, wchar_t pout[], std::stack<std::string> libraries)
	{
		lexT = plexT;
		idT = pidT;
		out = ofstream(pout, ios_base::out);

		Head(libraries);
		Const();
		Data();
		Code();
	}

	void Generator::Head(std::stack<std::string> libs) {
		out << ".586\n";
		out << ".model flat, stdcall\n";

		out << "includelib libucrt.lib\n";
		out << "includelib kernel32.lib\n";
		out << "includelib "../Debug/StaticLib.lib"\n";
		out << "ExitProcess PROTO :DWORD\n\n";

		while (!libs.empty()) {
			if (libs.top() == "math") {
				out << "EXTRN _random: proc\n";
				out << "EXTRN _exp: proc\n";
			}
			else if (libs.top() == "str") {
				out << "EXTRN _strlen: proc\n";
				out << "EXTRN _strcopy: proc\n";
			}
			libs.pop();
		}

		out << "EXTRN BREAKL: proc\n";
		out << "EXTRN IntOut: proc\n";
		out << "EXTRN IntOutLn: proc\n";
		out << "EXTRN StrOut: proc\n";
		out << "EXTRN StrOutLn: proc\n";

		out << "\n.stack 4096\n\n";
	}

	void Generator::Const() {
		out << ".const\n";
		for (int i = 0; i < idT.size; i++) {
			if (idT.table[i].idtype == IT::L) {
				out << "\t" << idT.table[i].id;
				if (idT.table[i].iddatatype == IT::STR)
					out << " BYTE \"" << idT.table[i].value.vstr.str << "\", 0";
				if (idT.table[i].iddatatype == IT::UBYTE || idT.table[i].iddatatype == IT::BOOL)
					out << " DD " << idT.table[i].value.vint;
				out << "\n";
			}
		}
	}

	void Generator::Data() {
		out << "\n.data\n";
		out << "\tbuffer BYTE 256 dup(0)\n";
		for (int i = 0; i < lexT.size; i++) {
			if (lexT.table[i].lexema == LEX_DESCRIBE) {
				if (idT.table[lexT.table[i + 2].idxTI].idtype == IT::V) {
					out << "\t" << idT.table[lexT.table[i + 2].idxTI].id;
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::STR)
						out << " DWORD ?\n";
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::UBYTE || idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::BOOL)
						out << " DD 0\n";
				}
			}
		}
	}

	void Generator::Code() {
		stack<char*> stk;
		int num_of_points = 0,
			num_of_ret = 0,
			num_of_ends = 0,
			num_of_cycles = 0,
			countParm = 0;
		string strret = string(),
			circuit_body = string(),
			func_name = string();
		bool flag_function = false,
			flag_give = false,
			flag_body = false,
			flag_provided = false,
			flag_callfunction = false,
			flag_else = false,
			flag_condition = false,
			flag_then = false,
			flag_circuit = false;

		int result_position;

		out << "\n.code\n\n";
		for (int i = 0; i < lexT.size; i++) {
			switch (lexT.table[i].lexema) {
			case LEX_FUNCTION:
				while (lexT.table[i].lexema != LEX_RIGHTSQ) {
					if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].idtype == IT::F) {
						out << (func_name = string((char*)idT.table[lexT.table[i].idxTI].id)) << " PROC ";
					}
					if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].idtype == IT::P) {
						out << idT.table[lexT.table[i].idxTI].id << " : ";
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::UBYTE || idT.table[lexT.table[i].idxTI].iddatatype == IT::BOOL)
							out << "DWORD";
						else
							out << "DWORD";
					}

					if (lexT.table[i].lexema == LEX_COMMA)
						out << ", ";

					i++;
				}
				flag_function = true;
				out << "\n";
				break;

			case LEX_MAIN:
				flag_body = true;
				out << "main PROC\n";
				break;

			case LEX_EQUAL:
				result_position = i - 1;
				while (lexT.table[i].lexema != LEX_SEMICOLON) {
					switch (lexT.table[i].lexema) {
					case LEX_ID:
					case LEX_LITERAL:
						if (idT.table[lexT.table[i].idxTI].idtype == IT::F) {
							flag_callfunction = true;
						}
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::UBYTE || idT.table[lexT.table[i].idxTI].iddatatype == IT::BOOL) {
							out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
							stk.push(idT.table[lexT.table[i].idxTI].id);
							break;
						}
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::STR) {
							char* s;
							if (idT.table[lexT.table[i].idxTI].idtype == IT::L) {
								out << "\tpush offset " << idT.table[lexT.table[i].idxTI].id << "\n";
								s = new char[8]{ "offset " };
							}
							else {
								out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
								s = new char[1]{ "" };
							}

							size_t len1 = strlen((char*)s);
							size_t len2 = strlen((char*)idT.table[lexT.table[i].idxTI].id);
							char* result = (char*)malloc(len1 + len2 + 1);
							memcpy(result, s, len1);
							memcpy(result + len1, (char*)idT.table[lexT.table[i].idxTI].id, len2 + 1);
							stk.push(result);
							break;
						}

					case LEX_OPERATOR: 
						switch (lexT.table[i].ops) {
						case LT::OMUL:
							out << "\tpop eax\n\tpop ebx\n";
							out << "\tmul ebx\n\tpush eax\n";
							break;
						case LT::OPLUS:
							out << "\tpop eax\n\tpop ebx\n";
							out << "\tadd eax, ebx\n\tpush eax\n";
							break;
						case LT::OMINUS:
							out << "\tpop ebx\n\tpop eax\n";
							out << "\tsub eax, ebx\n\tpush eax\n";
							break;
						case LT::ODIV:
							out << "\tpop ebx\n\tpop eax\n";
							out << "\tcdq\n\tidiv ebx\n\tpush eax\n";
							break;
						case LT::OSHIFTL:
							out << " \tpop eax \n ";
							out << " \tpop eax \n ";
							out << " \tshl eax,  " << idT.table[lexT.table[i - 1].idxTI].value.vint << "\n";
							out << " \tpush eax \n ";
							break;
						case LT::OSHIFTR:
							out << " \tpop eax \n ";
							out << " \tpop eax \n ";
							out << " \tshr eax,  " << idT.table[lexT.table[i - 1].idxTI].value.vint << "\n";
							out << " \tpush eax \n ";
							break;
						}
						break;

					case '@':
						countParm = (char)lexT.table[i + 1].lexema - '0';

						for (int j = 1; j <= countParm; j++)
							out << "\tpop edx\n";

						for (int j = 1; j <= countParm; j++) {
							out << "\tpush " << stk.top() << "\n";
							stk.pop();
						}
						out << "\tcall " << idT.table[lexT.table[i].idxTI].id << "\n\tpush eax\n";
						flag_callfunction = false;
						break;
					}

					i++;
				}

				out << "\tpop " << idT.table[lexT.table[result_position].idxTI].id << "\n";
				break;

			case '@':
				countParm = (char)lexT.table[i + 1].lexema - '0';
				for (int j = 1; j <= countParm; j++) {
					if (idT.table[lexT.table[i - j].idxTI].iddatatype == IT::UBYTE || idT.table[lexT.table[i - j].idxTI].iddatatype == IT::BOOL)
						out << "\tpush " << idT.table[lexT.table[i - j].idxTI].id << "\n";
					else {
						if (idT.table[lexT.table[i - j].idxTI].idtype == IT::L)
							out << "\tpush offset " << idT.table[lexT.table[i - j].idxTI].id << "\n";
						else
							out << "\tpush " << idT.table[lexT.table[i - j].idxTI].id << "\n";
					}
				}

				out << "\tcall " << idT.table[lexT.table[i - countParm - 1].idxTI].id << "\n";
				break;

			case LEX_GIVE:
				out << "\tpush ";
				if (idT.table[lexT.table[i + 1].idxTI].idtype == IT::L)
					out << idT.table[lexT.table[i + 1].idxTI].value.vint << "\n";
				else
					out << idT.table[lexT.table[i + 1].idxTI].id << "\n";
				if (flag_function) {
					out << "\tjmp local" << num_of_ret << "\n";
					flag_give = true;
				}
				if (flag_body) {
					out << "\t\tjmp theend\n";
					flag_give = true;
				}
				break;

			case LEX_BRACELET:
				if (flag_body && !flag_then && !flag_else && !flag_function && !flag_circuit) {
					if (flag_give) {
						out << "theend:\n";
						flag_give = false;
					}
					out << "\tcall ExitProcess\nmain ENDP\nend main";
				}
				if (flag_function && !flag_then && !flag_else && !flag_circuit) {
					if (flag_give) {
						out << "local" << num_of_ret++ << ":\n";
						out << "\tpop eax\n\tret\n";
						flag_give = false;
					}
					out << func_name << " ENDP\n\n";
					flag_function = false;
				}
				if (flag_then) {
					flag_then = false;
					if (flag_else) {
						out << "\tjmp e" << num_of_ends << "\n";
						flag_else = false;
					}
					out << "m" << num_of_points++ << ":\n";
				}
				if (flag_else) {
					flag_else = false;
					out << "e" << num_of_ends++ << ":\n";
				}
				break;

			case LEX_CIRCUIT:
				flag_circuit = true;
				flag_condition = true;
				out << "push " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
				out << "pop ebx\n";
				out << circuit_body << "cyclenext" << num_of_cycles << ":\n";
				break;

			case LEX_END:
				if (flag_circuit) {
					out << circuit_body << "\tsub ebx, 1\n\tcmp ebx, 0\n\tjz endcycle" << num_of_cycles << "\n\tloop cyclenext" << num_of_cycles << "\n\tendcycle" << num_of_cycles << ":\n";
					circuit_body.clear();
					num_of_cycles++;
					flag_circuit = false;
				}
				break;

			case LEX_LEFTHESIS:
				if (flag_provided) {
					if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::BOOL && lexT.table[i + 2].lexema == LEX_RIGHTHESIS) {
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "\tcmp eax, 1\n";
						out << "\tjz m" << num_of_points << "\n";
						out << "\tjnz m" << num_of_points + 1 << "\n";
					}
					else {
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "\tcmp eax, " << idT.table[lexT.table[i + 3].idxTI].id << "\n";

						if (lexT.table[i + 2].ops == LT::OMORE) {
							out << "\tjg m" << num_of_points << "\n";
							out << "\tjl m" << num_of_points + 1 << "\n";
						}
						else if (lexT.table[i + 2].ops == LT::OLESS) {
							out << "\tjl m" << num_of_points << "\n";
							out << "\tjg m" << num_of_points + 1 << "\n";
						}
						else if (lexT.table[i + 2].ops == LT::OEQU) {
							out << "\tjz m" << num_of_points << "\n";
							out << "\tjnz m" << num_of_points + 1 << "\n";
						}
						else if (lexT.table[i + 2].ops == LT::ONEQU) {
							out << "\tjnz m" << num_of_points << "\n";
							out << "\tjz m" << num_of_points + 1 << "\n";
						}
					}
					out << "\tje m" << num_of_points + 1 << "\n";
					int j = i;
					while (lexT.table[j++].lexema != LEX_BRACELET) {
						if (lexT.table[j + 1].lexema == LEX_ELSE) {
							flag_else = true;
							break;
						}
					}
				}

			case LEX_PROVIDED:
				flag_provided = true;
				break;

			case LEX_ELSE:
				flag_else = true;
				break;
			case LEX_RIGHTHESIS:
				if (lexT.table[i + 1].lexema == LEX_LEFTBRACE && flag_provided) {
					flag_then = true;
					out << "m" << num_of_points++ << ":\n";
					flag_provided = false;
				}
				break;

			case LEX_SPEAK:
				if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::UBYTE || idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::BOOL)
					out << "\tpush " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tcall IntOut\n";
				else {
					if (idT.table[lexT.table[i + 1].idxTI].idtype == IT::L)
						out << "\tpush offset ";
					else
						out << "\tpush ";
					out << idT.table[lexT.table[i + 1].idxTI].id << "\n\tcall StrOut\n";
				}
				break;

			case LEX_SPEAKFN:
				if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::UBYTE || idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::BOOL)
					out << "\tpush " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tcall IntOutLn\n";
				else {
					if (idT.table[lexT.table[i + 1].idxTI].idtype == IT::L)
						out << "\tpush offset ";
					else
						out << "\tpush ";
					out << idT.table[lexT.table[i + 1].idxTI].id << "\n\tcall StrOutLn\n";
				}
				break;
			}
		}
	}
}
