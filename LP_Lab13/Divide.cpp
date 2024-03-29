#include "Divide.h"

char** divide(char source[], int size, Log::LOG logfile)
{
	int count = 0;
	char** word = new char* [max_word];
	for (int i = 0; i < max_word; i++) {
		word[i] = new char[size_word] {NULL};
	}

	bool findSeparator, findLit = false;
	int j = 0;
	char separators[] = { " ,;(){}[]=+-*/|\t" };
	for (int i = 0, k = 0; i < size - 1; i++, k++) {
		findSeparator = false;
		if (source[i] == '\'') {
			findLit = !findLit;
			count++;
		}
		for (int t = 0; t < sizeof(separators) - 1; t++) {
			if (source[i] == separators[t] && !findLit) {
			findSeparator = true;
				if (word[j][0] != NULL) {
					word[j++][k] = '\0';
					k = 0;
				}
				if (separators[t] == ' ') {
					k = -1;
					break;
				}
				word[j][k++] = separators[t];
				word[j++][k] = '\0';
				k = -1;
				break;
			}
		}

		if (!findSeparator) word[j][k] = source[i];
	}
	if (count % 2 != 0) {
		Log::WriteError(logfile, Error::geterror(300));
	}
	word[j] = NULL;
	for (int i = 0; i < j; i++) {
		if (!strcmp((char*)word[i], "")) return NULL;
	}

	return word;
}