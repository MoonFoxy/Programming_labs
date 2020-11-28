#include <iostream>

#define MATRIX_SIZE 3

/*
  Ввод:
  С клавиатуры вводится двумерный массив целых чисел размерностью 3х3. Затем вводится натуральная n.
  Вывод:
  Необходимо возвести матрицу в степень n
*/

int main()
{
    unsigned long long array[MATRIX_SIZE][MATRIX_SIZE], temp[MATRIX_SIZE][MATRIX_SIZE];

    std::cout << "Enter numbers: ";

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            std::cin >> array[i][j];
            temp[i][j] = array[i][j];
        }
    }

    int power;

    std::cout << "Enter power: ";
    std::cin >> power;

    unsigned long long result[MATRIX_SIZE][MATRIX_SIZE] = { 0 };

    for (int p = 1; p < power; p++)
    {
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            for (int j = 0; j < MATRIX_SIZE; j++)
            {
                for (int k = 0; k < MATRIX_SIZE; k++)
                {
                    result[i][j] += array[k][j] * temp[i][k];
                }
            }
        }
    }

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            std::cout << result[i][j] << " ";
        }

        std::cout << "\n";
    }

    system("pause");
    return 0;
}
