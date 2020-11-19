#include <iostream>

using namespace std;

/*
  С клавиатуры вводится целочисленный массив из девяти элементов.
  Необходимо:
    1) Определить номер тройки элементов, имеющей максимальную сумму элементов среди всех трёх троек;
    2) Вывести в обратном порядке следования МАКСИМУМЫ каждой из троек;
    3) Определить: имеется ли внутри массива последовательность какой-либо длины, состоящая из непрерывно возрастающих степеней 2 (1, 2, 4, 8, 16...Если таких последовательностей много, то достаточно вывести первую слева)
    4) Вывести на экран элементы массива в порядке возрастания.
  Примечание: ВСПОМОГАТЕЛЬНЫЕ МАССИВЫ ИСПОЛЬЗОВАТЬ НЕЛЬЗЯ! Метод сортировки произвольный, но без использования вспомогательных функций.
  Комментарий: Обработка троек должна проводиться в циклах!
*/

int main()
{
    int input[9];
    for(int i = 0; i < 9; i++)
    {
        cin >> input[i];
    }

    int maxKey = 1;
    int maxSum;
    int maxInThree[3];
    for (int i = 0; i < 3; i++)
    {
        int sum = 0;
        int key = i * 3;
        maxInThree[i] = input[key];
        for (int j = 0; j < 3; j++, key++)
        {
            sum += input[key];
            if (maxInThree[i] < input[key])
            {
                maxInThree[i] = input[key];
            }
        }

        if (i == 0 || maxSum < sum)
        {
            maxKey = i + 1;
            maxSum = sum;
        }
    }

    cout << "(1): " << maxKey << endl;

    cout << "(2):";
    for (int i = 2; i >= 0; i--)
    {
        cout << " " << maxInThree[i];
    }
    // delete[] maxInThree;
    cout << endl;

    bool flag = false;
    int nextNum;
    cout << "(3):";
    for (int i = 0; i < 9; i++)
    {
        if ((input[i] & (input[i] - 1) != 0) && (input[i] != 0))
        {
            if (flag) break;
            continue;
        }

        if (flag && (input[i] != nextNum)) break;

        cout << " " << input[i];

        if (!flag)
        {
            flag = true;
            nextNum = input[i] * 2;
        }
    }
    cout << endl;

    // Шейкер сортировка
    int left = 1;
    int right = 9;
    bool sorted = false;
    do {
        sorted = false;
        for (int i = left; i <= right; i++) {
            if (input[i - 1] > input[i]) {
                swap (input[i - 1], input[i]);
                sorted = true;
            }
        }
        right--;
        for (int i = right; i >= left; i--) {
            if (input[i - 1] > input[i]) {
                swap (input[i - 1], input[i]);
                sorted = true;
            }
        }
        left++;
    } while (sorted);

    cout << "(4):";
    for (int i = 0; i < 9; i++)
    {
        cout << " " << input[i];
    }
    cout << endl;

    // delete[] input;
    return 0;
}
