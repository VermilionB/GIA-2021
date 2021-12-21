#include <iostream>
#include <ctime>
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

	int _strlen(char* ptr) {
		return strlen(ptr) < 255 ? strlen(ptr) : 255;
	}

	char* _strcopy(char* s1, char* s2) {
		if (!s1 || !s2) {
			std::cout << "ERROR: null string" << std::endl;
			ExitProcess(0);
		}
		return s2;
	}

	int _exp(short num, short exp) {
		return pow(num, exp) < 255 ? pow(num, exp) : 255;
	}
	
	int _random(short min, short max) {
		srand(time(NULL));
		return rand() % (max - min) + min;
	}
}