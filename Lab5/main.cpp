#include <iostream>
#include <cmath>

using namespace std;

/*
  Ввод:
  С клавиатуры вводится двумерный массив целых чисел размерностью 3х3. Затем вводится натуральная n.
  Вывод:
  Необходимо возвести матрицу в степень n
*/

int main()
{
    int array[3][3];

    cout << "Enter numbers: ";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> array[i][j];
        }
    }

    int power;

    cout << "Enter power: ";
    cin >> power;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double result = pow(array[i][j], power);
            cout << result << " ";
        }

        cout << endl;
    }
    return 0;
}
