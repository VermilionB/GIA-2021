#include"Error.h"
namespace Error
{
	//����� ������: 0-99 -- ��������� ������
	//				100-109 -- ������ ����������
	//				110-119 -- ������ �������� � ������ ������

	ERROR errors[ERROR_MAX_ENTRY] = { //������� ������
		ERROR_ENTRY(0, "������������ ��� ������"),
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"�������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111,"������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112,"������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113, "UYBTE errrrooor"),
		ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF(120),ERROR_ENTRY_NODEF(130),ERROR_ENTRY_NODEF(140),ERROR_ENTRY_NODEF(150),
		ERROR_ENTRY_NODEF(160),ERROR_ENTRY_NODEF(170),ERROR_ENTRY_NODEF(180),ERROR_ENTRY_NODEF(190),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(200),
		ERROR_ENTRY(208, "[ LEXICAL ] �������������� �������"),

		ERROR_ENTRY_NODEF(300),ERROR_ENTRY_NODEF(400),ERROR_ENTRY_NODEF(500),
		ERROR_ENTRY(600, "[ SYNTAX ] �������� ��������� ���������"),
		ERROR_ENTRY(601, "[ SYNTAX ] ������ � ���� �������"),
		ERROR_ENTRY(602, "[ SYNTAX ] ������ � ���������� ���������"),
		ERROR_ENTRY(603, "[ SYNTAX ] ������ � ���������� �������"),
		ERROR_ENTRY(604, "[ SYNTAX ] ������ � ������ ���������� ��� ������ �������"),
		ERROR_ENTRY(605, "[ SYNTAX ] ������ � �������������� ���������"),
		ERROR_ENTRY(606, "[ SYNTAX ] ������ ��� ������ �������"),
		ERROR_ENTRY(607, "[ SYNTAX ] ��������� ����������� � ���� �����"),
		ERROR_ENTRY(608, "[ SYNTAX ] ��������� ����������� � ���� �������"),
		ERROR_ENTRY(609, "[ SYNTAX ] ������ � �������� ���������"),

		ERROR_ENTRY(700, "[ SEMANTIC ] ������� ����� ����� ����� ����� � main"),
		ERROR_ENTRY(701, "[ SEMANTIC ] �� ������� ����� ����� � main"),
		ERROR_ENTRY(702, "[ SEMANTIC ] ���������� ���������� ��� ��������� ����� describe"),
		ERROR_ENTRY(703, "[ SEMANTIC ] �������� ������ ���������� ��������"),
		ERROR_ENTRY(705, "[ SEMANTIC ] ������������� �������������"),
		ERROR_ENTRY(706, "[ SEMANTIC ] ��������� ���������� ��� �������� ����"),
		ERROR_ENTRY(707, "[ SEMANTIC ] ������� ����������� ������������ �������"),
		ERROR_ENTRY(708, "[ SEMANTIC ] ���������� ������� ��� �������� ����"),
		ERROR_ENTRY(709, "[ SEMANTIC ] ������������ ����� ������������ ���������� �������"),
		ERROR_ENTRY(710, "[ SEMANTIC ] �������������� �������������� ����������"),
		ERROR_ENTRY(711, "[ SEMANTIC ] ���������� ������� �� ����"),
		ERROR_ENTRY(712, "[ SEMANTIC ] ������������� ����� ������"),
		ERROR_ENTRY(713, "[ SEMANTIC ] ������������� �������� � �������� ������ � ���������"),
		ERROR_ENTRY(714, "[ SEMANTIC ] ������� ���������� �������� ��� ������"),
		ERROR_ENTRY(715, "[ SEMANTIC ] ������������� ���������� ��������� �������� � ������������ ����������"),
		ERROR_ENTRY(716, "[ SEMANTIC ] ��������� ���������� ���������� � �������"),

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