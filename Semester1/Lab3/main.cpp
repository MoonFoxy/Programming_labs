/*
  Задача: Вывести на экран все простые числа не превышающие число N.
  Ввод: Целое положительное число N.
  Завершение: Автоматически после ввода числа N.
  Вывод: Список простых чисел не превышающие число N.
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
    int iN = 0, iDozens = 10;
    std::cout << "Enter number N: ";
    std::cin >> iN;

    if (iN >= 2) std::cout << "2 ";

    for (int iI = 3; iI <= iN; iI += 2)
    {
        bool bPrime = false;
        for (int iJ = 3; iJ * iJ <= iI; iJ += 2)
        {
            if ((iI % iJ) == 0)
            {
                bPrime = true;
                break;
            }
        }

        if (bPrime)
        {
            if (iI > iDozens)
            {
                std::cout << "\n";
            }

            std::cout << iI << " ";
            iDozens = ((iI / 10 + 1) * 10);
        }
    }

    wait();
    return 0;
}
