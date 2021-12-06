#include "stdafx.h"
#include "In.h"
#include "Error.h"

using namespace std;

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN in {0, 0, 0, new char[IN_MAX_LEN_TEXT], IN_CODE_TABLE};
		
		int col = 0, i = 0;
		unsigned char l;

		ifstream fin(infile);
		if (fin.fail()) throw ERROR_THROW(110);

		while (in.size < IN_MAX_LEN_TEXT)
		{
			l = fin.get();

			if (fin.eof())
			{
				in.text[in.size] = '\0';
				in.lines++;
				break;
			}
			if (in.code[(int)l] == in.T)
			{
				in.text[in.size] = l;
				in.size++;
				i++;
				col++;
			}
			else if (in.code[(int)l] == in.I)
			{
				in.ignore++;
				col++;
			}
			else if (in.code[(int)l] == in.F)
			{
				throw ERROR_THROW_IN(200, in.lines + 1, col);
			}
			else
			{
				in.text[in.size] = in.code[(int)l];
				in.size++;
				i++;
				col++;
			}
			if (l == IN_CODE_END)
			{
				in.lines++;
				col = 0;
			}
		}
		fin.close();
		in.text[i] = '\0';
		return in;
	}
}