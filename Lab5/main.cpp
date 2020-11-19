#include <iostream>

using namespace std;

/*
  Ввод:
  С клавиатуры вводится двумерный массив целых чисел размерностью 3х3. Затем вводится натуральная n.
  Вывод:
  Необходимо возвести матрицу в степень n
*/

int main()
{
    const int size = 3;
    unsigned long long result[size][size], array[size][size];

    cout << "Enter numbers: ";

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cin >> array[i][j];
            result[i][j] = array[i][j];
        }
    }

    int power;

    cout << "Enter power: ";
    cin >> power;

    unsigned long long temp[size][size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp[i][j] = 0;
        }
    }

    for (int p = 1; p < power; p++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    temp[i][j] += result[i][k] * array[k][j];
                }
            }
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result[i][j] = temp[i][j];
                temp[i][j] = 0;
            }
        }
    }
    // delete[] temp, array;


    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    // delete[] result;
    return 0;
}
