/*
ЗАДАНИЕ НА КУРСОВОЙ ПРОЕКТ

  Общая часть задания:
    Программа должна оперировать тремя квадратными матрицами (А, В и С), размерность которых задается (или определяется) на фазе работы программы.

    Необходимо:
      1) реализовать динамические структуры данных и алгоритмы их обработки, позволяющие поддерживать выполнение следующих функций:
        - консольный ввод/вывод данных о матрицах А, В и С;
        - файловый ввод/вывод данных о матрицах А, В и С;
        - интерактивное редактирование элементов матриц;
      2) разработать и реализовать алгоритмы обработки базы данных, предусмотренные персональным заданием.

  Примеры персональных заданий:
    4) Скопировать в матрицу С те элементы матрицы А, которые более одного раза встречаются в матрице В.
    14) Вывести на экран те элементы матрицы С, которые равны сумме соответствующих элементов матриц А и В.

  Общие требования к программам:
    1) Программа должна поддерживать систему меню, пункты которых соответствуют выполнению функций, предусмотренных заданием.
    2) Тексты программ должны содержать комментарии, объясняющие назначение основных функций, типов и объектов данных, функциональных блоков и т.п.
    3) Представляемые тексты программ должны обеспечивать возможность их компиляции и построения в среде MS Visual Studio.
*/

#include <iostream> // Для Консольного ввода/вывода
#include <cstring> // Для функции memcpy()
#include <unistd.h> // Для функции usleep()

// Количество создаваемых матриц
#define MATRIX_COUNT 3

// Очистка консоли
#define CLEAR "\x1B[2J\x1B[H"

// Расцветка консоли
#define TITLE_CL "\x1b[30m\x1b[47m"
#define LOG_CL "\x1b[37m\x1b[44m"
#define SUCCESS_CL "\x1b[37m\x1b[42m"
#define WARN_CL "\x1b[30m\x1b[43m"
#define EXIT_CL "\x1b[30m\x1b[41m"
#define RESET_CL "\x1b[0m"


/**
 * Выводит матрицу в консоль
 *
 * @param aiMatrix Выводимая матрица
 * @param iSize Размер матрицы
 */
void printMatrix(int** aiMatrix, int iSize)
{
    for (int iI = 0; iI < iSize; iI++)
    {
        std::cout << TITLE_CL <<'\t';
        for (int iJ = 0; iJ < iSize; iJ++)
        {
            std::cout << " " << aiMatrix[iI][iJ];
        }
        std::cout << RESET_CL << std::endl;
    }
    std::cout << std::endl;
}

/**
 * Создает матрицу Size на Size все эллементы которой равны 0
 *
 * @param iSize Размер матрицы
 * @return Готовая матрица все элементы которой равны 0
 */
int** createMatrix(int iSize)
{
    int** aiMatrix = new int* [iSize];
    for (int iI = 0; iI < iSize; iI++)
    {
        aiMatrix[iI] = new int [iSize];
    }

    return aiMatrix;
}

/**
 * Обновляет значения в матрице через консоль
 *
 * @param aiMatrix Изменяемая матрица
 * @param iSize Размер матрицы
 */
void updateMatrixValues(int** aiMatrix, int iSize)
{
    std::cout << CLEAR;
    while (true)
    {
        std::cout << LOG_CL << "\t\t\tThe matrix: " << RESET_CL << std::endl;

        printMatrix(aiMatrix, iSize);

        std::cout << std::endl;
        std::cout << LOG_CL << "\t[ X, Y, Value ]" << RESET_CL << " - Enter X, Y, Value parameters separated by a space" << std::endl << "\t\tto change a specific value in the matrix" << std::endl;
        std::cout << std::endl;
        std::cout << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Enter 0 in X and Y to go back" << std::endl;
        std::cout << std::endl;
        std::cout << LOG_CL << "\t\t[ X,  Y,  Value ]" << RESET_CL << std::endl;
        std::cout << "Enter answer: " << TITLE_CL;

        int iX = -1, iY = -1, iValue = 0;
        std::cin >> iX >> iY >> iValue;
        if (iX == 0 && iY == 0) return;

        std::cout << RESET_CL;

        if (iX > iSize || iY > iSize || iX < 0 || iY < 0)
        {
            std::cout << CLEAR;
            std::cout << std::endl << WARN_CL << "!!! Wrong input !!!" << RESET_CL << std::endl;
        }
        else
        {
            aiMatrix[iY - 1][iX - 1] = iValue;
            std::cout << CLEAR;
        }
    }
}

/**
 * Создает матрицы из заполненного заранее файла .TXT
 *
 * @return Созданные матрицы с файла
 */
int*** createMatrixFromTXT()    // TODO: Заполнение матриц с .TXT файла
{

}

/**
 * Обновляет значение матриц из заполненного заранее файла .TXT
 *
 * @param aiMatrix Трёхмернаая матрица
 * @param aiSizeMatrix Массив с размерами вложенных матриц
 */
void updateMatrixFromTXT(int*** aiMatrix, int* aiSizeMatrix)    // TODO: Заполнение матриц с .TXT файла
{

}

/**
 * Заполняет матрицу рандомными числами ( 0 - 10 )
 *
 * @param aiMatrix Изменяемая матрица
 * @param iSize Размер матрицы
 */
void fillRandomMatrix(int** aiMatrix, int iSize)
{
    for (int iI = 0; iI < iSize; iI++)
    {
        for (int iJ = 0; iJ < iSize; iJ++)
        {
            aiMatrix[iI][iJ] = rand() % 10;
        }
    }
}

/**
 * Заполняет матрицу нулями ( 0 )
 *
 * @param aiMatrix Изменяемая матрица
 * @param iSize Размер матрицы
 */
void fillZeroMatrix(int** aiMatrix, int iSize)
{
    for (int iI = 0; iI < iSize; iI++)
    {
        for (int iJ = 0; iJ < iSize; iJ++)
        {
            aiMatrix[iI][iJ] = 0;
        }
    }
}

/**
 * Изменяет размер матрицы и заполняет нулями пустые эллементы матрицы
 *
 * @param aiMatrix Изменяемая матрица [ Переменная изменяется ]
 * @param iSize Размер матрицы [ Переменная изменяется ]
 * @param iNewSize Новый рахмер матрицы
 */
void resizeMatrix(int** &aiMatrix, int &iSize, int iNewSize)
{
    int iBias = iNewSize - iSize;
    if (iBias == 0) return;
    int** aiTemp = createMatrix(iNewSize);

    int iSelected = ((iBias > 0) ? iSize : iNewSize);
    for (int iI = 0; iI < iSize; iI++)
    {
        for (int iJ = 0; iI < iSelected && iJ < iSelected; iJ++)
        {
            aiTemp[iI][iJ] = aiMatrix[iI][iJ];
        }
        delete[] aiMatrix[iI];
        aiMatrix[iI] = aiTemp[iI];
    }
    delete[] aiMatrix;
    aiMatrix = aiTemp;

    if (iBias > 0)
    {
        for (int iI = 0; iI < iNewSize; iI++)
        {
            int iJ = ((iI < iSize) ? iSize : 0);
            for (; iJ < iNewSize; iJ++)
                aiMatrix[iI][iJ] = 0;
        }
    }

    iSize = iNewSize;
}

/**
 * Полностью удаляет трёхмерную матрицу
 *
 * @param aiMatrix Трёхмернаая матрица
 * @param aiSizeMatrix Массив с размерами вложенных матриц
 */
void deleteMatrix(int*** aiMatrix, int* aiSizeMatrix)
{
    for (int iI = 0; iI < MATRIX_COUNT; ++iI)
    {
        int iSize = aiSizeMatrix[iI];
        for (int iJ = 0; iJ < iSize; ++iJ)
        {
            delete[] aiMatrix[iI][iJ];
        }
        delete[] aiMatrix[iI];
    }
    delete[] aiMatrix;
}

/**
 * Перезаписывает файл .TXT матрицами программы
 *
 * @param aiMatrix Трёхмернаая матрица
 * @param aiSizeMatrix Массив с размерами вложенных матриц
 */
void printMatrixInTXT(int*** aiMatrix, int* aiSizeMatrix)     // TODO: Заполнение матриц с .TXT файла
{

}

/**
 * [ Персональное задание номер 4 ]:
 * Скопировать в матрицу С те элементы матрицы А, которые более одного раза встречаются в матрице В
 *
 * // FIXME: Исправить параметры
 * @param Param1 None
 * @param Param2 None
 */
void task4()    // TODO: Дополнительное задание 4 в курсовой работе
{

}

/**
 * [ Персональное задание номер 14 ]:
 * Вывести на экран те элементы матрицы С, которые равны сумме соответствующих элементов матриц А и В
 *
 * // FIXME: Исправить параметры
 * @param Param1 None
 * @param Param2 None
 */
void task14()   // TODO: Дополнительное задание 14 в курсовой работе
{

}

/**
 * Перводит буквы алфавита в номер их порядка
 *
 * @param iLetter Число ASCII буквы
 * @return Номер порядка буквы в алфавите
 */
int ABCToInt(int iLetter)
{
    if (iLetter > 122) return -1;
    if (iLetter >= 97 && iLetter <= 122) iLetter -= 32;
    if (iLetter >= 65 && iLetter <= 90) iLetter -= 64;
    if (iLetter <= 57) iLetter -= 48;
    if (iLetter < 0) return -1;
    return iLetter;
}

/**
 * Ввод размера матрицы с консоли
 *
 * @param cLetter Буква ( Название ) матрицы
 * @return Размер создаваемой матрицы
 */
int inputMatrixSize(char cLetter)
{
    std::cout << CLEAR;
    while (true)
    {
        std::cout << "Enter the size of the matrix " << cLetter << ": ";

        int iAnswer = -1;
        std::cin >> iAnswer;

        std::cout << RESET_CL;
        if (iAnswer <= 0)
        {
            std::cout << CLEAR << WARN_CL << "!!! Matrix size must be greater than zero !!!" << RESET_CL << std::endl;
        }
        else
        {
            return iAnswer;
        }
    }
}

/**
 * Выбор матрицы из предложенных в консоли
 *
 * @param bStart Показывает что программа находится в { Стадия заполнения матриц } [ Не обязательно ]
 * @param aiSizeMatrix Проверяемые на заполнение матрицы [ Не обязательно ]
 * @return Индекс выбранной матрицы
 */
int selectMatrix(bool bStart = false, int* aiSizeMatrix = {})
{
    std::cout << CLEAR;
    while (true)
    {
        std::cout << LOG_CL << "Select a matrix from the following:" << RESET_CL << std::endl;
        for (int iI = 0; iI < MATRIX_COUNT; iI++)
        {
            std::cout << LOG_CL << "\t[ " << (iI + 1) << " ]" << RESET_CL << " - " << char(iI + 65) << '\t';
            if (bStart && aiSizeMatrix[iI] > 0)
            {
                std::cout << SUCCESS_CL << " - Filled ✓ - " << RESET_CL;
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Back" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter answer: " << TITLE_CL;

        char iAnswer = -1;
        std::cin >> iAnswer;
        iAnswer = ABCToInt(iAnswer);

        std::cout << RESET_CL;

        if (iAnswer == -1 || iAnswer > MATRIX_COUNT)
        {
            std::cout << CLEAR;
            std::cout << std::endl << WARN_CL << "!!! Wrong input !!!" << RESET_CL << std::endl;
            continue;
        }
        else if (iAnswer == 0) return -1;
        else return (iAnswer - 1);
    }
}

/**
 * Стартовое меню программы
 * { Стадия заполнения матриц }
 *
 * @param aiMatrix Используемая трёхмерная матрица
 * @param aiSizeMatrix Используемый массив с размером матриц
 * @return Значение завершения программы или Продолжения в { Основная стадия }
 */
bool start(int*** aiMatrix, int* aiSizeMatrix)
{
    while (true)
    {
        bool bFlag = true;
        for (int iI = 0; iI < MATRIX_COUNT; iI++)
        {
            if (aiSizeMatrix[iI] == 0)
            {
                bFlag = false;
                break;
            }
        }

        std::cout << CLEAR;
        std::cout << LOG_CL << "Matrix input:" << RESET_CL << std::endl;
        std::cout << LOG_CL << "\t[ 1 ]" << RESET_CL << " - Creating a matrices filled with zeros ( 0 )" << std::endl;
        std::cout << LOG_CL << "\t[ 2 ]" << RESET_CL << " - Creating matrices filled with random numbers ( 0 - 10 )" << std::endl;
        std::cout << LOG_CL << "\t[ 3 ]" << RESET_CL << " - Filling matrices from a pre-entered .TXT file" << std::endl;

        if (bFlag)
        {
            std::cout << SUCCESS_CL << "\t[ 4 ]" << RESET_CL << " - Continue" << std::endl;
        }

        std::cout << std::endl;
        std::cout << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Exiting the program" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter answer: " << TITLE_CL;

        char iAnswer = -1;
        std::cin >> iAnswer;
        iAnswer = ABCToInt(iAnswer);

        std::cout << RESET_CL;

        switch (iAnswer)
        {
            case 0:     // Выход из программы
            {
                return false;
            }

            case 1:     // Заполнение матрицы нулями
            {
                int aiSelectedMatrix = selectMatrix(true, aiSizeMatrix);
                if (aiSelectedMatrix == -1) continue;

                int iSize = (aiSizeMatrix[aiSelectedMatrix] = inputMatrixSize(aiSelectedMatrix + 65)); // 65 = A ( int в ASCII )
                aiMatrix[aiSelectedMatrix] = createMatrix(iSize);

                fillZeroMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);

                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                usleep(2500000);
                continue;
            }

            case 2:     // Заполнение матрицы рандомом
            {
                int aiSelectedMatrix = selectMatrix(true, aiSizeMatrix);
                if (aiSelectedMatrix == -1) continue;

                int iSize = (aiSizeMatrix[aiSelectedMatrix] = inputMatrixSize(aiSelectedMatrix + 65)); // 65 = A ( int в ASCII )
                aiMatrix[aiSelectedMatrix] = createMatrix(iSize);

                fillRandomMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);

                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                usleep(2500000);
                continue;
            }

            case 3:     // TODO: Заполнение матриц с .TXT файла
            {
                continue;
            }

            case 4:     // Переход в { Основная стадия }
            {
                if (!bFlag) continue;
                return true;
            }

            default:       // Заного печатать меню
            {
                continue;
            }
        }
    }
}

/**
 * Основное меню
 * { Основная стадия }
 *
 * @param aiMatrix Используемая трёхмерная матрица
 * @param aiSizeMatrix Используемый массив с размером матриц
 */
void menu(int*** aiMatrix, int* aiSizeMatrix)
{
    while (true)
    {
        std::cout << CLEAR;
        std::cout << LOG_CL << "Menu:" << RESET_CL << std::endl;
        std::cout << LOG_CL << "\t[ 1 ]" << RESET_CL << " - Change matrices via the console ( manual input )" << std::endl;
        std::cout << LOG_CL << "\t[ 2 ]" << RESET_CL << " - Updates matrices with a pre-entered .TXT file" << std::endl;
        std::cout << LOG_CL << "\t[ 3 ]" << RESET_CL << " - Fills matrices with zeros ( 0 )" << std::endl;
        std::cout << LOG_CL << "\t[ 4 ]" << RESET_CL << " - Fills existing matrices with random numbers ( 0 - 10 )" << std::endl;
        std::cout << LOG_CL << "\t[ 5 ]" << RESET_CL << " - Resizes matrices" << std::endl;
        std::cout << LOG_CL << "\t[ 6 ]" << RESET_CL << " - Outputting matrices to the console" << std::endl;
        std::cout << LOG_CL << "\t[ 7 ]" << RESET_CL << " - Outputting matrices to a previously created .TXT file" << std::endl;
        std::cout << std::endl;
        std::cout << WARN_CL << "\t[ 8 ]" << RESET_CL << " - (Task 4) " << std::endl;
        std::cout << WARN_CL << "\t[ 9 ]" << RESET_CL << " - (Task 14) " << std::endl;
        std::cout << std::endl;
        std::cout << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Exiting the program" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter answer: " << TITLE_CL;

        char iAnswer = -1;
        std::cin >> iAnswer;
        iAnswer = ABCToInt(iAnswer);

        std::cout << RESET_CL;

        switch (iAnswer)
        {
            case 0:     // Выход из программы
            {
                return;
            }

            case 1:     // Ручной ввод с консоли в матрицу
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1) continue;

                updateMatrixValues(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                continue;
            }

            case 2:     // TODO: Заполнение матриц с .TXT файла
            {
                continue;
            }

            case 3:     // Заполнение матрицы нулями
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1) continue;

                std::cout << LOG_CL << "Output of the original matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                usleep(2500000);

                fillZeroMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);

                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                usleep(2500000);
                continue;
            }

            case 4:     // Заполнение матрицы рандомом
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1) continue;

                std::cout << LOG_CL << "Output of the original matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                usleep(2500000);

                fillRandomMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);

                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                usleep(2500000);
                continue;
            }

            case 5:     // Изменение размера матрицы
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1) continue;

                std::cout << LOG_CL << "Output of the original matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                usleep(2500000);

                int iNewSize = inputMatrixSize(aiSelectedMatrix + 65); // 65 = A ( int в ASCII )
                resizeMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix], iNewSize);

                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                usleep(2500000);
                continue;
            }

            case 6:     // Вывод матрицы в консоль
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1) continue;

                std::cout << LOG_CL << "Output of the matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                usleep(4000000);
                continue;
            }

            case 7:     // TODO: Заполнение .TXT файла c матриц
            {
                continue;
            }

            case 8:     // TODO: Дополнительное задание 4 в курсовой работе
            {
                // task4();
                continue;
            }

            case 9:     // TODO: Дополнительное задание 14 в курсовой работе
            {
                // task14();
                continue;
            }

            default:    // Заного напечатать меню
            {
                continue;
            }
        }
    }
}

/**
 * Простая ни на что не влияющая загрузка
 *
 * @param iSeconds Время выполнения загрузки
 */
void loading(int iSeconds)
{
    char cDelete[11] = "\b\b\b\b\b\b\b\b\b\b";

    std::cout << "Loading   " << std::flush;
    for (int iI = 0; iI < iSeconds; iI++) {
        std::cout << cDelete << "Loading   " << std::flush;
        usleep(100000);
        std::cout << cDelete << "LOading   " << std::flush;
        usleep(100000);
        std::cout << cDelete << "LoAding   " << std::flush;
        usleep(100000);
        std::cout << cDelete << "LoaDing   " << std::flush;
        usleep(100000);
        std::cout << cDelete << "LoadIng   " << std::flush;
        usleep(100000);
        std::cout << cDelete << "LoadiNg   " << std::flush;
        usleep(100000);
        std::cout << cDelete << "LoadinG   " << std::flush;
        usleep(100000);
        std::cout << cDelete << "Loading.  " << std::flush;
        usleep(100000);
        std::cout << cDelete << "Loading.. " << std::flush;
        usleep(100000);
        std::cout << cDelete << "Loading..." << std::flush;
        usleep(100000);
    }

    return;
}

/**
 * Заголовок программы
 */
void title()
{
    std::cout << CLEAR;
    std::cout << SUCCESS_CL << "\t\t\"Coursework on PROGRAMMING\" No. 1" << TITLE_CL << std::endl;
    std::cout << "\tAuthor: Ilya Balakirev aka. MoonFoxy                    " << std::endl;
    std::cout << "\tGitHub: https://github.com/MoonFoxy/                    " << std::endl;
    std::cout << "\tFirst course                                            " << std::endl;
    std::cout << "\tFaculty of Computer Technology and Informatics          " << std::endl;
    std::cout << "\tManagement in technical systems                         " << std::endl;
    std::cout << "\tGroup: 0391                                             " << std::endl;
    std::cout << std::endl << "\t\t\t\t";

    loading(5);

    std::cout << RESET_CL << std::endl;
}

/**
 * Основная функция
 *
 * @return Код завершения программы
 */
int main()
{
    int*** aiMatrix = new int** [MATRIX_COUNT];
    int aiSizeMatrix[MATRIX_COUNT] = { 0 };

    title();
    bool bFlag = start(aiMatrix, aiSizeMatrix);
    if (bFlag)
    {
        menu(aiMatrix, aiSizeMatrix);
    }


    std::cout << std::endl << EXIT_CL << "\t\tExit the programm" << RESET_CL << std::endl;
    deleteMatrix(aiMatrix, aiSizeMatrix);
    return 0;
}
