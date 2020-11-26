#include <iostream>

/*
  Задача: Вывести на экран все простые числа не превышающие число N.
  Ввод: Целое положительное число N.
  Завершение: Автоматически после ввода числа N.
  Вывод: Список простых чисел не превышающие число N.
*/

int main()
{
    int N;
    std::cout << "Enter number N: ";
    std::cin >> N;

    int dozens = 10;

    if (N >= 2) std::cout << "2 ";

    for (int i = 3; i <= N; i += 2)
    {
        bool prime = false;
        for (int j = 3; j * j <= i; j += 2)
        {
            if ((i % j) == 0)
            {
                prime = true;
                break;
            }
        }

        if (prime)
        {
            if (i > dozens)
            {
                std::cout << "\n";
            }

            std::cout << i << " ";
            dozens = ((i / 10 + 1) * 10);
        }
    }

    system("pause");
    return 0;
}
