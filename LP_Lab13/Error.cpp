#include"Error.h"
namespace Error
{
	//серии ошибок: 0-99 -- системные ошибки
	//				100-109 -- ошибки параметров
	//				110-119 -- ошибки открытия и чтения файлов

	ERROR errors[ERROR_MAX_ENTRY] = { //таблица ошибок
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111,"Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "UYBTE errrrooor"),
		ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF(120),ERROR_ENTRY_NODEF(130),ERROR_ENTRY_NODEF(140),ERROR_ENTRY_NODEF(150),
		ERROR_ENTRY_NODEF(160),ERROR_ENTRY_NODEF(170),ERROR_ENTRY_NODEF(180),ERROR_ENTRY_NODEF(190),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(200),
		ERROR_ENTRY(208, "[ LEXICAL ] Нераспознанная лексема"),

		ERROR_ENTRY_NODEF(300),ERROR_ENTRY_NODEF(400),ERROR_ENTRY_NODEF(500),
		ERROR_ENTRY(600, "[ SYNTAX ] Неверная структура программы"),
		ERROR_ENTRY(601, "[ SYNTAX ] Ошибка в теле функции"),
		ERROR_ENTRY(602, "[ SYNTAX ] Ошибка в построении выражения"),
		ERROR_ENTRY(603, "[ SYNTAX ] Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "[ SYNTAX ] Ошибка в списке параметров при вызове функции"),
		ERROR_ENTRY(605, "[ SYNTAX ] Ошибка в арифметическом выражении"),
		ERROR_ENTRY(606, "[ SYNTAX ] Ошибка при вызове функции"),
		ERROR_ENTRY(607, "[ SYNTAX ] Ошибочная конструкция в теле цикла"),
		ERROR_ENTRY(608, "[ SYNTAX ] Ошибочная конструкция в теле условия"),
		ERROR_ENTRY(609, "[ SYNTAX ] Ошибка в условном выражении"),

		ERROR_ENTRY(700, "[ SEMANTIC ] Имеется более одной точки входа в main"),
		ERROR_ENTRY(701, "[ SEMANTIC ] Не имеется точки входа в main"),
		ERROR_ENTRY(702, "[ SEMANTIC ] Объявление переменной без ключевого слова describe"),
		ERROR_ENTRY(703, "[ SEMANTIC ] Превышен размер строкового литерала"),
		ERROR_ENTRY(705, "[ SEMANTIC ] Необъявленный идентификатор"),
		ERROR_ENTRY(706, "[ SEMANTIC ] Объвление переменной без указания типа"),
		ERROR_ENTRY(707, "[ SEMANTIC ] Попытка реализовать существующую функцию"),
		ERROR_ENTRY(708, "[ SEMANTIC ] Объявление функции без указания типа"),
		ERROR_ENTRY(709, "[ SEMANTIC ] Несовпадение типов передаваемых параметров функции"),
		ERROR_ENTRY(710, "[ SEMANTIC ] Несоответствие арифметических операторов"),
		ERROR_ENTRY(711, "[ SEMANTIC ] Невозможно деление на ноль"),
		ERROR_ENTRY(712, "[ SEMANTIC ] Несоответсвие типов данных"),
		ERROR_ENTRY(713, "[ SEMANTIC ] Несоответсвие открытых и закрытых скобок в выражении"),
		ERROR_ENTRY(714, "[ SEMANTIC ] Функция возвращает неверный тип данных"),
		ERROR_ENTRY(715, "[ SEMANTIC ] Несоотвествие количества ожидаемых функцией и передаваемых параметров"),
		ERROR_ENTRY(716, "[ SEMANTIC ] Превышено количество параметров в функции"),

		ERROR_ENTRY_NODEF(800),ERROR_ENTRY_NODEF(900),
	};
	ERROR geterror(int id)
	{
		ERROR e;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			e = errors[0];
		else
			e = errors[id];
		return e;

	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			e = errors[0];
		else
		{
			e = errors[id];
			e.inext.line = line;
			e.inext.col = col;
		}
		return e;
	}
	
}