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

int main() {
    int X;
    int minNumber;
    int numberAmount;
    int numberSum = 0;
    int positiveAmount = 0;

    cout << "Enter numbers:\n";

    while(true) {
        cin >> X;

        if (X == 0) break;

        if (!minNumber || X <= minNumber) {
            minNumber = X;
        }

        if (X > 0) {
            positiveAmount++;
        }

        numberSum += X;
        numberAmount++;
    }

    int averageNumber = 1.0 * numberSum / (numberAmount || 1);

    cout << "Minimum number: " << minNumber << endl;
    cout << "Average: " << averageNumber << endl;
    cout << "Positive numbers: " << positiveAmount << endl;
}
