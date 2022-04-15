#include <conio.h>
#include <dos.h>
// #include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define XSTART 0.5 // Промежуток
#define XEND 7
#define GRAPHTEXT "f(x) = sin^2(x) - cos^2(x) on [ Pi/2; 7Pi ]"
#define DRIVERPATH "..//BORLANDC//BGI" // Расположение графического драйвера
#define X 639						   // Выверенно точными науками
#define Y 479

// Настройка "UI"
const int X0 = X * 0.05, X1 = X * 0.95, X2 = (X0 + X1) / 2, Y0 = Y * 0.25, Y1 = Y * 0.95, Y2 = (Y0 + Y1) / 2, N = X1 - X0 - 25;

/**
 * Вот эта ебанутая функция
 */
float graphFunction(double x)
{
	return (float)(pow(sin(x), 2) - pow(cos(x), 2));
}

/**
 * Создает точки функции и адаптирует под график на экране
 */
int *considerFunction(float *Fmax, float *Fmin)
{
	int i, *f = new int[N];
	double x = XSTART * M_PI, dx = (XEND - XSTART) * M_PI / N;
	float *fRaw = new float[N];

	*Fmin = (*Fmax = graphFunction(x));
	for (i = 0; i < N; i++, x += dx)
	{
		fRaw[i] = graphFunction(x);
		if (*Fmax < fRaw[i])
			*Fmax = fRaw[i];
		else if (*Fmin > fRaw[i])
			*Fmin = fRaw[i];
	}

	// Подстраиваем график под экран ("UI")
	for (i = 0; i < N; i++)
		f[i] = Y1 - 25 + (Y0 - Y1 + 50) * (fRaw[i] - *Fmin) / (*Fmax - *Fmin);
	/*
		relative_value = (value - low) / (high - low);
		scaled_value = low_2 + (high_2 - low_2) * relative_value;
	*/

	return f;
}

/**
 * Рисуем график
 */
void draw(int *F)
{
	setlinestyle(0, 1, 1);
	for (int i = 0; i + 1 < N; i++)
	{
		// putpixel(i + X0, F[i], 2);
		setcolor(i % 16);
		line(X0 + i, F[i], X0 + i + 1, F[i + 1]);
		delay(10);
	}
	setcolor(15);
}

int main()
{
	int i, driver, mode;
	char text[15];

	clrscr(); // Очистка экрана
	gotoxy(15, 10);
	cprintf("< < < Press any key to switch to graphics mode > > >");
	getch();

	detectgraph(&driver, &mode); // Открыли графичесий режим
	initgraph(&driver, &mode, DRIVERPATH);
	int errorCode = graphresult();
	if (errorCode < 0)
	{
		gotoxy(15, 15);
		cprintf("[ ERROR %d! CAN'T OPEN GRAPHIC MODE ]", errorCode);
		getch();
		return errorCode;
	}

	int textLength = (X / 2) - (textwidth(GRAPHTEXT) / 2);
	outtextxy(textLength, 20, GRAPHTEXT); // Текст условия

	float Fmax, Fmin;
	int *F = considerFunction(&Fmax, &Fmin); // Вычислили значения функции

	/**
	 * Рисуем координатные оси
	 */
	int zeroLine;
	if (Fmax < 0)
		zeroLine = Y0 + 15;
	else if (Fmin > 0)
		zeroLine = Y1 - 15;
	else
		zeroLine = Y1 - 25 + (Y0 - Y1 + 50) * (0 - Fmin) / (Fmax - Fmin);

	setlinestyle(0, 1, 1);
	line(X0, Y0, X0, Y1);			  // Y
	line(X0, zeroLine, X1, zeroLine); // X

	/**
	 * Помечаем оси
	 */
	outtextxy(X2 - 10, Y0 - 10, "f(x)");
	outtextxy(X1 + 5, zeroLine - 5, "X");
	outtextxy(X0 - 5, Y0 - 10, "Y");
	outtextxy(X0 - 10, zeroLine - 5, "0");
	sprintf(text, "%.2f", Fmax);
	outtextxy(X0 + 10, Y0 - 10, text);
	sprintf(text, "%.2f", Fmin);
	outtextxy(X0 + 10, Y1 + 5, text);

	/**
	 * Рисуем метки и подписи на оси Х
	 */
	int count = (XEND - XSTART) * 2 + 0.5;
	// Метки
	for (i = 1; i <= count; i++)
	{
		int Xline = X0 + N / count * i;
		line(Xline, zeroLine - 3, Xline, zeroLine + 3); // Метки
	}

	i = 1;
	int num = XSTART + 0.5;
	if ((XSTART - (int)XSTART) == 0)
	{
		i = 2;
		num = XSTART;
		sprintf(text, "%.1fpi", (float)XEND);
		outtextxy(X1 - (N / count) - textwidth(text) / 2, zeroLine + 15, text); // Подписи
	}

	// Подписи
	for (; i <= count; i += 2, num += 1)
	{
		int Xline = X0 + N / count * i;
		sprintf(text, "%ipi", num);
		outtextxy(Xline - textwidth(text) / 2, zeroLine + 15, text); // Подписи
	}

	draw(F); // Рисуем график

	/**
	 * Вывод Максимума и Минимума
	 */
	sprintf(text, "Max: ~%.2f", Fmax);
	outtextxy(textLength, 35, text);
	sprintf(text, "Min: ~%.2f", Fmin);
	outtextxy(textLength, 50, text);

	getch();	  // Ожидаем нажатия клавиши...
	closegraph(); // Закрываем графичесий режим
	return 0;
}
