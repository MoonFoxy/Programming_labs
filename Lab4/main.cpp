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

#include <iostream>

int main()
{
    int aiInput[9];

    std::cout << "Enter numbers: ";
    for (int iI = 0; iI < 9; iI++) std::cin >> aiInput[iI];

    int iMaxKey = 1;
    int iMaxSum;
    int aiMaxInThree[3];
    for (int iI = 0; iI < 3; iI++)
    {
        int iSum = 0;
        int iKey = iI * 3;
        aiMaxInThree[iI] = aiInput[iKey];
        for (int iJ = 0; iJ < 3; iJ++, iKey++)
        {
            iSum += aiInput[iKey];
            if (aiMaxInThree[iI] < aiInput[iKey])
            {
                aiMaxInThree[iI] = aiInput[iKey];
            }
        }

        if (iI == 0 || iMaxSum < iSum)
        {
            iMaxKey = iI + 1;
            iMaxSum = iSum;
        }
    }

    std::cout << "(1): " << iMaxKey << "\n";

    std::cout << "(2):";
    for (int iI = 2; iI >= 0; iI--)
    {
        std::cout << " " << aiMaxInThree[iI];
    }

    std::cout << "\n";

    bool bFlag = false;
    int iNextNum;
    std::cout << "(3):";
    for (int iI = 0; iI < 9; iI++)
    {
        if ((aiInput[iI] & (aiInput[iI] - 1) != 0) && (aiInput[iI] != 0))
        {
            if (bFlag) break;
            continue;
        }

        if (bFlag && (aiInput[iI] != iNextNum)) break;

        std::cout << " " << aiInput[iI];

        if (!bFlag)
        {
            bFlag = true;
            iNextNum = aiInput[iI] * 2;
        }
    }

    std::cout << "\n";

    // Шейкер сортировка
    int iLeft = 1;
    int iRight = 9;
    bool bSorted = false;
    do {
        bSorted = false;
        for (int iI = iLeft; iI <= iRight; iI++) {
            if (aiInput[iI - 1] > aiInput[iI]) {
                std::swap(aiInput[iI - 1], aiInput[iI]);
                bSorted = true;
            }
        }
        iRight--;
        for (int iI = iRight; iI >= iLeft; iI--) {
            if (aiInput[iI - 1] > aiInput[iI]) {
                std::swap(aiInput[iI - 1], aiInput[iI]);
                bSorted = true;
            }
        }
        iLeft++;
    } while (bSorted);

    std::cout << "(4):";
    for (int iI = 0; iI < 9; iI++)
    {
        std::cout << " " << aiInput[iI];
    }
    std::cout << "\n";

    return 0;
}
