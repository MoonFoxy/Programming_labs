#include <iostream>

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
    for (int i = 0; i < 9; i++) std::cin >> input[i];

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

    std::cout << "(1): " << maxKey << "\n";

    std::cout << "(2):";
    for (int i = 2; i >= 0; i--)
    {
        std::cout << " " << maxInThree[i];
    }

    std::cout << "\n";

    bool flag = false;
    int nextNum;
    std::cout << "(3):";
    for (int i = 0; i < 9; i++)
    {
        if ((input[i] & (input[i] - 1) != 0) && (input[i] != 0))
        {
            if (flag) break;
            continue;
        }

        if (flag && (input[i] != nextNum)) break;

        std::cout << " " << input[i];

        if (!flag)
        {
            flag = true;
            nextNum = input[i] * 2;
        }
    }

    std::cout << "\n";

    // Шейкер сортировка
    int left = 1;
    int right = 9;
    bool sorted = false;
    do {
        sorted = false;
        for (int i = left; i <= right; i++) {
            if (input[i - 1] > input[i]) {
                std::swap(input[i - 1], input[i]);
                sorted = true;
            }
        }
        right--;
        for (int i = right; i >= left; i--) {
            if (input[i - 1] > input[i]) {
                std::swap(input[i - 1], input[i]);
                sorted = true;
            }
        }
        left++;
    } while (sorted);

    std::cout << "(4):";
    for (int i = 0; i < 9; i++)
    {
        std::cout << " " << input[i];
    }
    std::cout << "\n";

    system("pause");
    return 0;
}
