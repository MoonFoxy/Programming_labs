#include <iostream>

/*
  Ввод:
  С клавиатуры вводится двумерный массив целых чисел размерностью 3х3. Затем вводится натуральная n.
  Вывод:
  Необходимо возвести матрицу в степень n
*/

int main()
{
    const int size = 3;
    unsigned long long array[size][size], temp[size][size];

    std::cout << "Enter numbers: ";

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cin >> array[i][j];
            temp[i][j] = array[i][j];
        }
    }

    int power;

    std::cout << "Enter power: ";
    std::cin >> power;

    unsigned long long result[size][size] = { 0 };

    for (int p = 1; p < power; p++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    result[i][j] += array[k][j] * temp[i][k];
                }
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << result[i][j] << " ";
        }

        std::cout << "\n";
    }

    system("pause");
    return 0;
}
