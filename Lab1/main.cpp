#include <iostream>

using namespace std;

/*
  Задача: Треугольник с координатам (2; 6), (6; 6), (6; 2). Проверить входит ли точка в треугольник.
  Ввод: Целое положительные числа X и Y.
  Завершение: После ввода координат X == 0 и Y == 0.
  Вывод: Сообщение входит ли координата в треугольник или нет.
*/

int main()
{
    float X, Y;
    while(true)
    {
        cout << "Enter coordinates:\n";
        cin >> X >> Y;

        if ((X == 0) && (Y == 0)) break;

        if ((X >= 2) && (X <= 6) && (Y <= X))
        {
            cout << "Enters\n";
        }
        else
        {
            cout << "Excluded\n";
        }
    }

    cout << "Stopped!\n";
}
