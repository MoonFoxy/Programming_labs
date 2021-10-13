#include <iostream>     // Поток ввода/вывода
#include <stdio.h>      // Функция printf()
#include <stdlib.h>     // ХЗ зачем
#include <conio.h>      // Функция getch() window() textattr()
#include <dos.h>        // Функция delay() REGS int86()
#include <windows.h>    // Функция Sleep()

using namespace std;

union type
{
    unsigned long long ll;
    long double d;
};

void wait()
{
    cout << endl
         << "Press any key to continue...";
    getch();
    cout << endl;
}

void printLongDouble(long double x)
{
    type m;
    m.d = x;
    for (int i = 16 * sizeof(m.ll) - 1; i > -1; i--)
    {
        printf("%d", m.ll >> i & 1);
    }
    cout << endl
         << '\r';
}

void scroll(int direction, int lines, char l_row, char l_col, char r_row, char r_col, char attr)
{
    union REGS regs;
    if (direction)
    {
        regs.h.al = lines;
        regs.h.ah = direction;
    }
    else
    {
        regs.h.al = lines;
        regs.h.ah = 6;
    }
    regs.h.ch = l_row;
    regs.h.cl = l_col;
    regs.h.dh = r_row;
    regs.h.dl = r_col;
    regs.h.bh = attr;
    int86(0x10, &regs, &regs);
}

void getPrintColor(unsigned char colors)
{
    unsigned char bg = colors >> 4;
    unsigned char text = colors & 15;

    switch (bg)
    {
        case 0:
            cout << "1 ";
            break;

        case 1:
            cout << "2 ";
            break;

        case 2:
            cout << "3 ";
            break;

        case 3:
            cout << "4 ";
            break;

        case 4:
            cout << "5 ";
            break;

        case 5:
            cout << "6 ";
            break;

        case 6:
            cout << "7 ";
            break;

        case 7:
            cout << "8 ";
            break;

        case 8:
            cout << "9 ";
            break;

        case 9:
            cout << "10 ";
            break;

        case 10:
            cout << "11 ";
            break;

        case 11:
            cout << "12 ";
            break;

        case 12:
            cout << "13 ";
            break;

        case 13:
            cout << "14 ";
            break;

        case 14:
            cout << "15 ";
            break;

        case 15:
            cout << "16 ";
            break;

        default:
            cout << "? ";
            break;
    }

    switch (text)
    {
        case 0:
            cout << "Черный\r";
            break;

        case 1:
            cout << "Синий\r";
            break;

        case 2:
            cout << "Зеленый\r";
            break;

        case 3:
            cout << "Циановый\r";
            break;

        case 4:
            cout << "Красный\r";
            break;

        case 5:
            cout << "Пурпурный\r";
            break;

        case 6:
            cout << "Коричневый\r";
            break;

        case 7:
            cout << "Светло-серый\r";
            break;

        case 8:
            cout << "Темно-серый\r";
            break;

        case 9:
            cout << "Светло-голубой\r";
            break;

        case 10:
            cout << "Светло-зеленый\r";
            break;

        case 11:
            cout << "Светло-циановый\r";
            break;

        case 12:
            cout << "Светло-красный\r";
            break;

        case 13:
            cout << "Светло-пурный\r";
            break;

        case 14:
            cout << "Желтый\r";
            break;

        case 15:
            cout << "Белый\r";
            break;

        default:
            cout << "??????\r";
            break;
    }
}

int main()
{
    long double inputLongDouble;
    scroll(0, 0, 0, 0, 25, 80, 7);
    window(20, 10, 60, 20);         // Установка окна вывода в консоле
    textattr(112);                  // Устанавливает одновременно как цвета переднего плана, так и фона
    scroll(0, 0, 9, 19, 19, 59, 7); // Скроллинг снизу вверх
    cout << "\n\n\n\n\n\n\n\n\r";

    int answer;
    while (true)
    {
        cout << "Показать магию?" << endl
             << "[ 1 ] - Да" << endl
             << "[ 0 ] - Нет ( Выход )" << endl;

        cin >> answer;

        switch (answer)
        {
            case 0:
                break;

            case 1:
            {
                unsigned char i = 0;
                do
                {
                    textattr(i);
                    inputLongDouble = ((0.956358714) * (rand() % 12501));
                    printLongDouble(inputLongDouble);
                    getPrintColor(i);
                    i++;
                    Sleep(1.5);                     // Задержка в милисекундах
                    scroll(6, 2, 9, 19, 19, 59, i); // Скроллинг
                } while (i < 127);
                wait();
                continue;
            }

            default:
                cout << endl << "Неверный ввод!" << endl;
                wait();
                continue;
        }
    }

    cout << "\n\r ----- ВСЕ, 2-Я ЛАБА ГОТОВА! --------\n\r";
    wait();
    return 0;
}
