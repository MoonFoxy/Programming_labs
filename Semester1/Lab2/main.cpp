/*
  Задача: С клавиатуры вводится последовательность целых чисел признак окончания ввода - "0".
  Необходимо вывести на экран:
    Минимальное из чисел,
    Среднее арифметическое чисел,
    Количество положительных чисел.
  Ввод: Число X.
  Завершение: Ввод числа X = 0.
  Вывод:
    Минимальное число,
    Среднее арифметическое чисел,
    Количество положительных чисел.
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
    int iX = 0, iMinNumber = 0, iNumberAmount = 0, iNumberSum = 0, iPositiveAmount = 0;

    std::cout << "Enter numbers: ";

    std::cin >> iX;
    iMinNumber = iX;

    while (true)
    {
        if (iX == 0) break;

        if (iX <= iMinNumber)
        {
            iMinNumber = iX;
        }

        if (iX > 0)
        {
            iPositiveAmount++;
        }

        iNumberSum += iX;
        iNumberAmount++;

        std::cin >> iX;
    }

    int iAverageNumber = float(iNumberSum) / ((iNumberAmount == 0) ? 1 : iNumberAmount);

    std::cout << "Minimum number: " << iMinNumber << "\n";
    std::cout << "Average: " << iAverageNumber << "\n";
    std::cout << "Positive numbers: " << iPositiveAmount << "\n";

    wait();
    return 0;
}
