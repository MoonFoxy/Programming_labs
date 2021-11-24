// Аппаратное прерывание от таймера, генерация сигнала SOS звука в 700 Гц.
#include <dos.h>
#include <stdio.h>
#include <conio.h>
// #include <bios.h>

unsigned long far *count =  (unsigned long far*) MK_FP(0x0040, 0x006c); // Тут храниться время (Кол-во выполненных прерываний)

void interrupt mybeep(...) // Прерывание
{
	static char a = 0;
	if (*count % 18L == 0)
	{
		switch(a)
		{
			case 0:
			case 1:
			case 2:
			case 6:
			case 7:
			case 8:
			{
				sound(700);
				delay(80);
				nosound();
				delay(10);
				a++;
				if (a == 9)
					a = 0;
				break;
			}
			case 3:
			case 4:
			case 5:
			{
				sound(700);
				delay(160);
				nosound();
				delay(10);
				a++;
				break;
			}
			default:
				break;
		}
	}
	return;
}


int main(void)
{
    clrscr();
    void interrupt (*oldvect)(...);		// Переменная
    oldvect = getvect(0x1c);	// Получаем значение вектора прерываний
    setvect(0x1c, mybeep);		// Создаем свое прерывание
	printf("To exit, press any key...\n");
	getch();
    setvect(0x1c, oldvect);		// Восстанавливаем значения
    return 0;
}
