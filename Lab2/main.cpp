#include <iostream>

using namespace std;

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

int main()
{
    int X;
    int minNumber;
    int numberAmount = 0;
    int numberSum = 0;
    int positiveAmount = 0;

    cout << "Enter numbers:\n";

    cin >> X;
    minNumber = X;

    while (true)
    {
        if (X == 0) break;

        if (X <= minNumber)
        {
            minNumber = X;
        }

        if (X > 0)
        {
            positiveAmount++;
        }

        numberSum += X;
        numberAmount++;

        cin >> X;
    }

    int averageNumber = float(numberSum) / (numberAmount == 0) ? 1 : numberAmount;

    cout << "Minimum number: " << minNumber << endl;
    cout << "Average: " << averageNumber << endl;
    cout << "Positive numbers: " << positiveAmount << endl;
    return 0;
}
