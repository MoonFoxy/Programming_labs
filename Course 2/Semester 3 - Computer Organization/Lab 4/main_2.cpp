#include <stdio.h>
#include <conio.h>
// #include <bios.h>	// bioskey
#include <dos.h>

#define X 80	// Выверенно точными науками
#define Y 25

#define FORWARD 62	// F4
#define BACKWARD 61 // F3

// const int X0 = X * 0.2, X1 = X * 0.8, Y0 = Y * 0.2, Y1 = Y * 0.8;
const int X0 = 20, X1 = 60, Y0 = 10, Y1 = 20;

/**
 * ESC - 27
 * UP - 72
 * LEFT <- - 75
 * RIGHT -> - 77
 * DOWN - 80
 * F3 - 61
 * F4 - 62
 */

char keyCheck(int option) {
	union REGS regs;

	switch (option)
	{
		case 0:
			regs.h.ah = 0x07;
			/**
			 * AH=07h - ввод с консоли с ожиданием без "эха" на экран
			 * ASCII-код прочитанного символа возвращается в AL.
			 */
			break;

		case 1:
			regs.h.ah = 0x0B;
			/**
			 * AH=0Bh проверка состояния стандартного ввода.
			 * Возвращает в регистре AL значение FFh,
			 * если буфер клавиатуры не пуст, и 0 в противном случае.
			 */
			break;

		default:
			return 0;
	}

	int86(0x21, &regs, &regs);
	/**
	 * int int86(int intnum, union REGS *regsin, union REGS *regsout)
	 * int int86(номер прерывания, откуда , куда)
	 * является указателем на структуру, в которую записываются
	 * возвращаемые значения регистров
	 * int86 выполняeт  программное  прерывание
	 */
	return regs.h.al;	// Возвращается ASCII код считонного символа
}

int main()
{
	textbackground(0);
	clrscr();
	window(X0, Y0, X1, Y1);
	textbackground(4);
	clrscr();

	int winWidth = X1 - X0 + 1;
	int winHeight = Y1 - Y0 + 1;

	int curX = 1, curY = 1;
	gotoxy(curX, curY);
	printf("@");
	gotoxy(curX, curY);

	char keyChar = 0;
	while (keyChar != 27)	// Проверка на клавишу ESC
	{
		if (keyCheck(1) != 0)		// [ bioskey(1) | 0x16 ] 0x0B Проверка на нажатие клавиши
			keyChar = keyCheck(0);	// [ bioskey(0) | 0x16 ] 0x07 Выполняет ввод с клавиатуры без "эхо" вывода на экран

		switch (keyChar)
		{
			case 77:	// ->
			case FORWARD:
			{
				gotoxy(curX, curY);
				printf(" ");

				++curX;
				if (curX == winWidth + 1)
				{
					curX = 1;
					++curY;
				}

				if (curY == winHeight + 1)
					curY = 1;

				gotoxy(curX, curY);
				printf("@");
				gotoxy(curX, curY);

				delay(70);
			}
			break;

			case 75:	// <-
			case BACKWARD:
			{
				gotoxy(curX, curY);
				printf(" ");

				--curX;
				if (curX == 0)
				{
					curX = winWidth;
					--curY;
				}

				if (curY == 0)
					curY = winHeight;

				gotoxy(curX, curY);
				printf("@");
				gotoxy(curX, curY);

				delay(70);
			}
			break;

			default:
				break;
		}
	}
	return 0;
}
