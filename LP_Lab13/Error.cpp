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
		ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF(120),ERROR_ENTRY_NODEF(130),ERROR_ENTRY_NODEF(140),ERROR_ENTRY_NODEF(150),
		ERROR_ENTRY_NODEF(160),ERROR_ENTRY_NODEF(170),ERROR_ENTRY_NODEF(180),ERROR_ENTRY_NODEF(190),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(200),ERROR_ENTRY_NODEF(300),ERROR_ENTRY_NODEF(400),ERROR_ENTRY_NODEF(500),
		ERROR_ENTRY_NODEF(600),
		ERROR_ENTRY(700, "[ SEMANTIC ] Имеется более одной точки входа в main"),
		ERROR_ENTRY(701, "[ SEMANTIC ] Не имеется точки входа в main"),
		ERROR_ENTRY(702, "[ SEMANTIC ] Объявление переменной без ключевого слова describe"),
		ERROR_ENTRY(303, "[ SEMANTIC ] Превышен размер строкового литерала"),
		ERROR_ENTRY(305, "[ SEMANTIC ] Необъявленный идентификатор"),
		ERROR_ENTRY(306, "[ SEMANTIC ] Объвление переменной без указания типа"),
		ERROR_ENTRY(307, "[ SEMANTIC ] Попытка реализовать существующую функцию"),
		ERROR_ENTRY(308, "[ SEMANTIC ] Объявление функции без указания типа"),
		ERROR_ENTRY(309, "[ SEMANTIC ] Несовпадение типов передаваемых параметров функции"),
		ERROR_ENTRY(310, "[ SEMANTIC ] Несоответствие арифметических операторов"),
		ERROR_ENTRY(311, "[ SEMANTIC ] Невозможно деление на ноль"),
		ERROR_ENTRY(312, "[ SEMANTIC ] Несоответсвие типов данных"),
		ERROR_ENTRY(313, "[ SEMANTIC ] Несоответсвие открытых и закрытых скобок в выражении"),
		ERROR_ENTRY(314, "[ SEMANTIC ] Функция возвращает неверный тип данных"),
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