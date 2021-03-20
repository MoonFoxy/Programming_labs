/*
  Задача: Треугольник с координатам (2; 6), (6; 6), (6; 2). Проверить входит ли точка в треугольник.
  Ввод: Целое положительные числа X и Y.
  Завершение: После ввода координат X == 0 и Y == 0.
  Вывод: Сообщение входит ли координата в треугольник или нет.
*/

#include <iostream>
#include <limits>

void wait()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar();
}

int main()
{
    float fX = 0, fY = 0;
    while (true)
    {
        std::cout << "Enter coordinates:" << std::endl;
        std::cin >> fX >> fY;

        if ((fX == 0) && (fY == 0)) break;

        if ((fX >= 2) && (fX <= 6) && (fY <= fX))
        {
            std::cout << "Enters +\n";
        }
        else
        {
            std::cout << "Excluded -\n";
        }
    }

    std::cout << "Stopped!\n";

    wait();
    return 0;
}
