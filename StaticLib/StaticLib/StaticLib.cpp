#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#pragma warning(disable: 4996)

extern "C" {
	void BREAKL() {
		std::cout << std::endl;
	}

	void IntOut(int a) {
		std::cout << a;
	}

	void IntOutLn(int a) {
		std::cout << a << std::endl;
	}

	void StrOut(char* ptr) {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		if (ptr == nullptr) {
			std::cout << std::endl;
			return;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
			std::cout << ptr[i];
	}

	void StrOutLn(char* ptr) {
		StrOut(ptr);
		std::cout << std::endl;
	}

	int StrLen(char* ptr) {
		return strlen(ptr);
	}

	char* StrCopy(char* s1, char* s2) {
		if (!s1 || !s2) {
			std::cout << "ERROR: null string" << std::endl;
			ExitProcess(0);
		}
		return s2;
	}

	int Exp(short num, short exp) {
		return pow(num, exp);
	}
	
	int Random(short min, short max) {
		return rand() % (max - min) + min;
	}
}