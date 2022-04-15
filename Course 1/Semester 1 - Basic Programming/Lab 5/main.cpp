/*
  Ввод:
  С клавиатуры вводится двумерный массив целых чисел размерностью 3х3. Затем вводится натуральная n.
  Вывод:
  Необходимо возвести матрицу в степень n
*/

#include <iostream>
#include <limits>

#define MATRIX_SIZE 3

void wait()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar();
}

int main()
{
    unsigned long long aullArray[MATRIX_SIZE][MATRIX_SIZE], aullResult[MATRIX_SIZE][MATRIX_SIZE];

    std::cout << "Enter numbers: ";

    for (int iI = 0; iI < MATRIX_SIZE; iI++)
    {
        for (int iJ = 0; iJ < MATRIX_SIZE; iJ++)
        {
            std::cin >> aullArray[iI][iJ];
            aullResult[iI][iJ] = aullArray[iI][iJ];
        }
    }

    int iPower;

    std::cout << "Enter power: ";
    std::cin >> iPower;

    unsigned long long aullTemp[MATRIX_SIZE][MATRIX_SIZE] = { 0 };

    for (; iPower > 1; --iPower)
    {
        for (int iI = 0; iI < MATRIX_SIZE; iI++)
            for (int iJ = 0; iJ < MATRIX_SIZE; iJ++)
                for (int iK = 0; iK < MATRIX_SIZE; iK++)
                    aullTemp[iI][iJ] += aullArray[iI][iK] * aullResult[iK][iJ];

        for (int iI = 0; iI < MATRIX_SIZE; iI++)
            for (int iJ = 0; iJ < MATRIX_SIZE; iJ++)
            {
                aullResult[iI][iJ] = aullTemp[iI][iJ];
                aullTemp[iI][iJ] = 0;
            }
    }

    for (int iI = 0; iI < MATRIX_SIZE; iI++)
    {
        for (int iJ = 0; iJ < MATRIX_SIZE; iJ++)
            std::cout << aullResult[iI][iJ] << " ";

        std::cout << "\n";
    }

    wait();
    return 0;
}
