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
#include <fstream>  // Для Файлового ввода/вывода
#include <cstring>  // Для функции memcmp
#include <limits>   // Для очищении потока консоли

// Количество создаваемых матриц
#define MATRIX_COUNT 3

// Файл для записи и чтения данных ( Полный путь до файла )
#define TEXT_FILE "./Course/file.txt"

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
 * Функция ожидания действия
 */
void wait()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar();
}

/**
 * Полностью удаляет матрицу
 *
 * @param aiMatrix Матрица
 * @param iSize Размер матрицы
 */
void deleteMatrix(int **aiMatrix, int iSize)
{
    for (int iI = 0; iI < iSize; iI++)
    {
        if (!(memcmp(aiMatrix[iI], "exit", 4) == 0))
            break;

        delete[] aiMatrix[iI];
    }

    delete[] aiMatrix;
}

/**
 * Полностью удаляет трёхмерную матрицу
 *
 * @param aiMatrix Трёхмернаая матрица
 * @param aiSizeMatrix Массив с размерами вложенных матриц
 */
void deleteAllMatrix(int ***aiMatrix, int *aiSizeMatrix)
{
    for (int iI = 0; iI < MATRIX_COUNT; iI++)
    {
        if (!(memcmp(aiMatrix, "exit", 4) == 0))
            break;

        int iSize = aiSizeMatrix[iI];
        for (int iJ = 0; iJ < iSize; iJ++)
        {
            if (!(memcmp(aiMatrix[iI], "exit", 4) == 0))
                break;

            delete[] aiMatrix[iI][iJ];
        }

        delete[] aiMatrix[iI];
    }

    delete[] aiMatrix;
}

/**
 * Выводит матрицу в консоль
 *
 * @param aiMatrix Выводимая матрица
 * @param iSize Размер матрицы
 */
void printMatrix(int **aiMatrix, int iSize)
{
    for (int iI = 0; iI < iSize; iI++)
    {
        std::cout << TITLE_CL << '\t';
        for (int iJ = 0; iJ < iSize; iJ++)
            std::cout << ' ' << aiMatrix[iI][iJ];

        std::cout << RESET_CL << std::endl;
    }

    std::cout << std::endl;
}

/**
 * Перводит буквы алфавита в номер их порядка
 *
 * @param iLetter Число ASCII буквы
 * @return Номер порядка буквы в алфавите
 */
int ABCToInt(int iLetter)
{
    if (iLetter > 122)
        return -1;

    if (iLetter >= 97 && iLetter <= 122)
        iLetter -= 32;

    if (iLetter >= 65 && iLetter <= 90)
        iLetter -= 64;

    if (iLetter <= 57)
        iLetter -= 48;

    if (iLetter < 0)
        return -1;

    return iLetter;
}

/**
 * Создает матрицу Size на Size все эллементы которой равны 0
 *
 * @param iSize Размер матрицы
 * @return Готовая матрица все элементы которой равны 0
 */
int **createMatrix(int iSize)
{
    int **aiMatrix = new int *[iSize];
    for (int iI = 0; iI < iSize; iI++)
        aiMatrix[iI] = new int[iSize];

    return aiMatrix;
}

/**
 * Обновляет значения в матрице через консоль
 *
 * @param aiMatrix Изменяемая матрица
 * @param iSize Размер матрицы
 */
void updateMatrixValues(int **aiMatrix, int iSize)
{
    std::cout << CLEAR;
    while (true)
    {
        std::cout << LOG_CL << "\t\t\tThe matrix: " << RESET_CL << std::endl;

        printMatrix(aiMatrix, iSize);

        std::cout << std::endl
                  << LOG_CL << "\t[ X, Y, Value ]" << RESET_CL << " - Enter X, Y, Value parameters separated by a space" << std::endl
                  << "\t\tto change a specific value in the matrix" << std::endl
                  << std::endl
                  << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Enter 0 in X and Y to go back" << std::endl
                  << std::endl
                  << LOG_CL << "\t\t[ X,  Y,  Value ]" << RESET_CL << std::endl
                  << "Enter answer: " << TITLE_CL;

        int iX = -1, iY = -1, iValue = 0;
        std::cin >> iX >> iY >> iValue;

        std::cout << RESET_CL;

        if (iX == 0 && iY == 0)
            return;

        if (iX > iSize || iY > iSize || iX < 0 || iY < 0)
            std::cout << CLEAR
                      << std::endl
                      << WARN_CL << "!!! Wrong input !!!" << RESET_CL << std::endl;
        else
        {
            aiMatrix[iY - 1][iX - 1] = iValue;
            std::cout << CLEAR;
        }
    }
}

/**
 * Заполняет матрицу рандомными числами ( 0 - 10 )
 *
 * @param aiMatrix Изменяемая матрица
 * @param iSize Размер матрицы
 */
void fillRandomMatrix(int **aiMatrix, int iSize)
{
    for (int iI = 0; iI < iSize; iI++)
        for (int iJ = 0; iJ < iSize; iJ++)
            aiMatrix[iI][iJ] = rand() % 10;
}

/**
 * Заполняет матрицу нулями ( 0 )
 *
 * @param aiMatrix Изменяемая матрица
 * @param iSize Размер матрицы
 */
void fillZeroMatrix(int **aiMatrix, int iSize)
{
    for (int iI = 0; iI < iSize; iI++)
        for (int iJ = 0; iJ < iSize; iJ++)
            aiMatrix[iI][iJ] = 0;
}

/**
 * Изменяет размер матрицы и заполняет нулями пустые эллементы матрицы
 *
 * @param aiMatrix Изменяемая матрица [ Переменная изменяется ]
 * @param iSize Размер матрицы [ Переменная изменяется ]
 * @param iNewSize Новый размер матрицы
 */
void resizeMatrix(int **&aiMatrix, int &iSize, int iNewSize)
{
    int iBias = iNewSize - iSize;
    if (iBias == 0)
        return;

    int **aiTemp = createMatrix(iNewSize);

    int iSelected = ((iBias > 0) ? iSize : iNewSize);
    for (int iI = 0; iI < iSize; iI++)
    {
        for (int iJ = 0; iI < iSelected && iJ < iSelected; iJ++)
            aiTemp[iI][iJ] = aiMatrix[iI][iJ];

        delete aiMatrix[iI];
        aiMatrix[iI] = aiTemp[iI];
    }

    delete aiMatrix;
    aiMatrix = aiTemp;
    if (iBias > 0)
        for (int iI = 0; iI < iNewSize; iI++)
        {
            int iJ = ((iI < iSize) ? iSize : 0);
            for (; iJ < iNewSize; iJ++)
                aiMatrix[iI][iJ] = 0;
        }

    iSize = iNewSize;
}

/**
 * Перезаписывает файл .TXT матрицами программы
 *
 * @param aiMatrix Трёхмернаая матрица
 * @param aiSizeMatrix Массив с размерами вложенных матриц
 * @return Показатель успешного завершения
 */
bool printMatrixInTXT(int ***aiMatrix, int *aiSizeMatrix)
{
    std::ofstream matrix;
    matrix.open(TEXT_FILE);

    if (!matrix.is_open())
        return false;

    for (int iI = 0; iI < MATRIX_COUNT; iI++)
    {
        if (matrix.fail())
            return false;

        int iSize = aiSizeMatrix[iI];
        matrix << (iI + 1) << ' ' << iSize << std::endl;
        for (int iJ = 0; iJ < iSize; iJ++)
        {
            for (int iK = 0; iK < iSize; iK++)
                matrix << ' ' << aiMatrix[iI][iJ][iK];

            matrix << std::endl;
        }

        matrix << std::endl
               << std::endl;
    }

    matrix.close();
    return true;
}

/**
 * Создает матрицы из заполненного заранее файла .TXT
 *
 * @param aiMatrix Заполняемая трехмерная матрица
 * @param aiSizeMatrix Массив с размерами матриц
 * @return Показатель успешного завершения
 */
bool createMatrixFromTXT(int ***&aiMatrix, int *aiSizeMatrix)
{
    std::ifstream matrix;
    matrix.open(TEXT_FILE);
    if (!matrix.is_open() || matrix.eof())
        return false;

    while (!matrix.eof())
    {
        if (!matrix.good())
            break;

        if (matrix.fail())
        {
            deleteAllMatrix(aiMatrix, aiSizeMatrix);
            for (int iI = 0; iI < MATRIX_COUNT; iI++)
            return false;
        }

        int iIndex = -1;
        int iSize = 0;
        matrix >> iIndex >> iSize;
        if (iIndex > MATRIX_COUNT || iIndex < 0)
            continue;

        iIndex--;
        if (matrix.eof())
            break;

        aiSizeMatrix[iIndex] = iSize;
        aiMatrix[iIndex] = createMatrix(iSize);
        bool bFlag = true;
        for (int iJ = 0; bFlag && iJ < iSize; iJ++)
            for (int iK = 0; iK < iSize; iK++)
            {
                if (matrix.eof())
                {
                    bFlag = false;
                    break;
                }

                matrix >> aiMatrix[iIndex][iJ][iK];
            }

        if (!bFlag)
        {
            deleteMatrix(aiMatrix[iIndex], aiSizeMatrix[iIndex]);
            aiSizeMatrix[iIndex] = 0;
            break;
        }
    }

    matrix.close();
    return true;
}

/**
 * Обновляет значение матриц из заполненного заранее файла .TXT
 *
 * @param aiMatrix Трёхмерная матрица
 * @param aiSizeMatrix Массив с размерами вложенных матриц
 * @return Показатель успешного завершения
 */
bool updateMatrixFromTXT(int ***&aiMatrix, int *aiSizeMatrix)
{
    int ***aiTemp = new int **[MATRIX_COUNT];
    int aiSizeTemp[MATRIX_COUNT] = { 0 };

    bool bSuccess = createMatrixFromTXT(aiTemp, aiSizeTemp);

    for (int iI = 0; iI < MATRIX_COUNT; iI++)
    {
        if (aiSizeTemp[iI] == 0)
            continue;

        deleteMatrix(aiMatrix[iI], aiSizeMatrix[iI]);
        int iSize = (aiSizeMatrix[iI] = aiSizeTemp[iI]);
        aiMatrix[iI] = createMatrix(iSize);
        for (int iJ = 0; iJ < iSize; iJ++)
            for (int iK = 0; iK < iSize; iK++)
                aiMatrix[iI][iJ][iK] = aiTemp[iI][iJ][iK];

        deleteMatrix(aiTemp[iI], aiSizeTemp[iI]);
    }

    delete[] aiTemp, aiSizeTemp;
    return bSuccess;
}

/**
 * [ Персональное задание номер 4 ]:
 * Скопировать в матрицу С те элементы матрицы А, которые более одного раза встречаются в матрице В
 *
 * @param aiMatrix Трёхмерная матрица
 * @param aiSizeMatrix Массив размеров матриц
 * @param aiIndex Массив с индексами
 */
void task4(int ***&aiMatrix, int *aiSizeMatrix, int *aiIndex) // TODO: Дополнительное задание 4 в курсовой работе
{
    int iSizeA = aiSizeMatrix[aiIndex[0]];
    int iSizeB = aiSizeMatrix[aiIndex[1]];
    int iSizeC = aiSizeMatrix[aiIndex[2]];
    int iSelected = 0;
    if ((iSizeA - iSizeB) > 0)
        if ((iSizeB - iSizeC) > 0)
            iSelected = iSizeC;
        else
            iSelected = iSizeB;
    else
        if ((iSizeA - iSizeC) > 0)
            iSelected = iSizeC;
        else
            iSelected = iSizeA;

    int iSizeSquare = iSelected * iSelected;
    int aiMatches[iSizeSquare];
    for (int iI = 0; iI < iSizeSquare; iI++)
        aiMatches[iI] = 0;

    int iMatchesIndex = 0;
    int iX = 0;
    int iY = 0;
    for (int iI = 0; iI < iSizeSquare; iI++)
    {
        bool bFlag1 = true;
        int iElement = aiMatrix[aiIndex[1]][iY][iX];
        for (int iJ = 0; iJ < iMatchesIndex; iJ++)
            if (iElement == aiMatches[iJ])
            {
                bFlag1 = false;
                break;
            }

        if (bFlag1)
        {
            bool bFlag2 = true;
            for (int iJ = iY; bFlag2 && iJ < iSelected; iJ++)
                for (int iK = iX; iK < iSelected; iK++)
                    if (iElement == aiMatrix[aiIndex[1]][iJ][iK])
                    {
                        aiMatches[++iMatchesIndex] = iElement;
                        bFlag2 = false;
                        break;
                    }
        }

        if (iX == iSizeB - 1)
        {
            iX = 0;
            iY++;
        }
        else
            iX++;
    }

    for (int iI = 0; iI < iMatchesIndex + 1; iI++)
        for (int iJ = 0; iJ < iSelected; iJ++)
            for (int iK = 0; iK < iSelected; iK++)
                if (aiMatches[iI] == aiMatrix[aiIndex[1]][iJ][iK])
                    aiMatrix[aiIndex[2]][iJ][iK] = aiMatrix[aiIndex[0]][iJ][iK];
}

/**
 * [ Персональное задание номер 14 ]:
 * Вывести на экран те элементы матрицы С, которые равны сумме соответствующих элементов матриц А и В
 *
 * @param aiMatrix Трёхмерная матрица
 * @param aiSizeMatrix Массив размеров матриц
 * @param aiIndex Массив с индексами
 */
void task14(int ***aiMatrix, int *aiSizeMatrix, int *aiIndex) // TODO: Дополнительное задание 14 в курсовой работе
{

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
            std::cout << CLEAR << WARN_CL << "!!! Matrix size must be greater than zero !!!" << RESET_CL << std::endl;
        else
            return iAnswer;
    }
}

/**
 * Выбор матрицы из предложенных в консоли
 *
 * @param bStart Показывает что программа находится в { Стадия заполнения матриц } [ Не обязательно ]
 * @param aiSizeMatrix Проверяемые на заполнение матрицы [ Не обязательно ]
 * @return Индекс выбранной матрицы
 */
int selectMatrix(bool bStart = false, int *aiSizeMatrix = {})
{
    std::cout << CLEAR;
    while (true)
    {
        std::cout << LOG_CL << "Select a matrix from the following:" << RESET_CL << std::endl;
        for (int iI = 0; iI < MATRIX_COUNT; iI++)
        {
            std::cout << LOG_CL << "\t[ " << (iI + 1) << " ]" << RESET_CL << " - " << char(iI + 65) << '\t';
            if (bStart && aiSizeMatrix[iI] > 0)
                std::cout << SUCCESS_CL << " - Filled ✓ - " << RESET_CL;

            std::cout << std::endl;
        }

        std::cout << std::endl
                  << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Back" << std::endl
                  << std::endl
                  << "Enter answer: " << TITLE_CL;

        char iAnswer = -1;
        std::cin >> iAnswer;
        iAnswer = ABCToInt(iAnswer);
        std::cout << RESET_CL;
        if (iAnswer == -1 || iAnswer > MATRIX_COUNT)
        {
            std::cout << CLEAR
                      << std::endl
                      << WARN_CL << "!!! Wrong input !!!" << RESET_CL << std::endl;

            continue;
        }
        else if (iAnswer == 0)
            return -1;
        else
            return (iAnswer - 1);
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
bool start(int ***aiMatrix, int *aiSizeMatrix)
{
    while (true)
    {
        bool bFlag = true;
        for (int iI = 0; iI < MATRIX_COUNT; iI++)
            if (aiSizeMatrix[iI] == 0)
            {
                bFlag = false;
                break;
            }

        std::cout << CLEAR
                  << LOG_CL << "Matrix input:" << RESET_CL << std::endl
                  << LOG_CL << "\t[ 1 ]" << RESET_CL << " - Creating a matrices filled with zeros ( 0 )" << std::endl
                  << LOG_CL << "\t[ 2 ]" << RESET_CL << " - Creating matrices filled with random numbers ( 0 - 10 )" << std::endl
                  << LOG_CL << "\t[ 3 ]" << RESET_CL << " - Filling matrices from a pre-entered .TXT file" << std::endl;

        if (bFlag)
            std::cout << SUCCESS_CL << "\t[ 4 ]" << RESET_CL << " - Continue" << std::endl;

        std::cout << std::endl
                  << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Exiting the program" << std::endl
                  << std::endl
                  << "Enter answer: " << TITLE_CL;
        char iAnswer = -1;
        std::cin >> iAnswer;
        iAnswer = ABCToInt(iAnswer);
        std::cout << RESET_CL;
        switch (iAnswer)
        {
            case 0: // Выход из программы
            {
                return false;
            }

            case 1: // Заполнение матрицы нулями
            {
                int aiSelectedMatrix = selectMatrix(true, aiSizeMatrix);
                if (aiSelectedMatrix == -1)
                    continue;

                int iSize = (aiSizeMatrix[aiSelectedMatrix] = inputMatrixSize(aiSelectedMatrix + 65)); // 65 = A ( int в ASCII )
                aiMatrix[aiSelectedMatrix] = createMatrix(iSize);
                fillZeroMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                wait();
                continue;
            }

            case 2: // Заполнение матрицы рандомом
            {
                int aiSelectedMatrix = selectMatrix(true, aiSizeMatrix);
                if (aiSelectedMatrix == -1)
                    continue;

                int iSize = (aiSizeMatrix[aiSelectedMatrix] = inputMatrixSize(aiSelectedMatrix + 65)); // 65 = A ( int в ASCII )
                aiMatrix[aiSelectedMatrix] = createMatrix(iSize);
                fillRandomMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                wait();
                continue;
            }

            case 3: // Заполнение матриц программы из .TXT файла
            {
                bool bSuccess = createMatrixFromTXT(aiMatrix, aiSizeMatrix);
                if (bSuccess)
                    std::cout << SUCCESS_CL << "Reading matrices from the " << TEXT_FILE << " file was successful!" << RESET_CL << std::endl;
                else
                    std::cout << WARN_CL << "Reading matrices from the file " << TEXT_FILE << " failed!" << RESET_CL << std::endl;

                wait();
                continue;
            }

            case 4: // Переход в { Основная стадия }
            {
                if (!bFlag)
                    continue;

                return true;
            }

            default: // Заного печатать меню
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
void menu(int ***aiMatrix, int *aiSizeMatrix)
{
    while (true)
    {
        std::cout << CLEAR
                  << LOG_CL << "Menu:" << RESET_CL << std::endl
                  << LOG_CL << "\t[ 1 ]" << RESET_CL << " - Change matrices via the console ( manual input )" << std::endl
                  << LOG_CL << "\t[ 2 ]" << RESET_CL << " - Updates matrices with a pre-entered .TXT file" << std::endl
                  << LOG_CL << "\t[ 3 ]" << RESET_CL << " - Fills matrices with zeros ( 0 )" << std::endl
                  << LOG_CL << "\t[ 4 ]" << RESET_CL << " - Fills existing matrices with random numbers ( 0 - 10 )" << std::endl
                  << LOG_CL << "\t[ 5 ]" << RESET_CL << " - Resizes matrices" << std::endl
                  << LOG_CL << "\t[ 6 ]" << RESET_CL << " - Outputting matrices to the console" << std::endl
                  << LOG_CL << "\t[ 7 ]" << RESET_CL << " - Outputting matrices to a previously created .TXT file" << std::endl
                  << std::endl
                  << WARN_CL << "\t[ 8 ]" << RESET_CL << " - (Task 4) " << std::endl
                  << WARN_CL << "\t[ 9 ]" << RESET_CL << " - (Task 14) " << std::endl
                  << std::endl
                  << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Exiting the program" << std::endl
                  << std::endl
                  << "Enter answer: " << TITLE_CL;

        char iAnswer = -1;
        std::cin >> iAnswer;
        iAnswer = ABCToInt(iAnswer);
        std::cout << RESET_CL;
        switch (iAnswer)
        {
            case 0: // Выход из программы
            {
                return;
            }

            case 1: // Ручной ввод с консоли в матрицу
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1)
                    continue;

                updateMatrixValues(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                continue;
            }

            case 2: // Обновление матриц программы из .TXT файла
            {
                bool bSuccess = updateMatrixFromTXT(aiMatrix, aiSizeMatrix);
                if (bSuccess)
                    std::cout << SUCCESS_CL << "Updating matrices from the " << TEXT_FILE << " file was successful!" << RESET_CL << std::endl;
                else
                    std::cout << WARN_CL << "Updating matrices from the file " << TEXT_FILE << " failed!" << RESET_CL << std::endl;

                wait();
                continue;
            }

            case 3: // Заполнение матрицы нулями
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1)
                    continue;

                std::cout << LOG_CL << "Output of the original matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                wait();
                fillZeroMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                wait();
                continue;
            }

            case 4: // Заполнение матрицы рандомом
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1)
                    continue;

                std::cout << LOG_CL << "Output of the original matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                wait();
                fillRandomMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                wait();
                continue;
            }

            case 5: // Изменение размера матрицы
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1)
                    continue;

                std::cout << LOG_CL << "Output of the original matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                wait();
                int iNewSize = inputMatrixSize(aiSelectedMatrix + 65); // 65 = A ( int в ASCII )
                resizeMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix], iNewSize);
                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                wait();
                continue;
            }

            case 6: // Вывод матрицы в консоль
            {
                int aiSelectedMatrix = selectMatrix(false);
                if (aiSelectedMatrix == -1)
                    continue;

                std::cout << LOG_CL << "Output of the matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiSelectedMatrix], aiSizeMatrix[aiSelectedMatrix]);
                wait();
                continue;
            }

            case 7: // Заполнение .TXT файла матрицами из программы
            {
                bool bSuccess = printMatrixInTXT(aiMatrix, aiSizeMatrix);
                if (bSuccess)
                    std::cout << SUCCESS_CL << "Writing matrices to the " << TEXT_FILE << " file was successful!" << RESET_CL << std::endl;
                else
                    std::cout << WARN_CL << "Writing matrices from the file " << TEXT_FILE << " failed!" << RESET_CL << std::endl;

                wait();
                continue;
            }

            case 8: // TODO: Персональное задание 4 в курсовой работе
            {
                /**
                 * [ Персональное задание номер 14 ]:
                 * Скопировать в матрицу С те элементы матрицы А, которые более одного раза встречаются в матрице В
                 */
                int aiIndex[3] = { 0 };
                bool bFlag = true;
                for (int iI = 0; iI < 3; iI++)
                {
                    aiIndex[iI] = selectMatrix(false);
                    if (aiIndex[iI] == -1)
                    {
                        bFlag = false;
                        break;
                    }
                }

                if (bFlag == false)
                    continue;

                std::cout << LOG_CL << "Output of the original matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiIndex[2]], aiSizeMatrix[aiIndex[2]]);
                wait();
                task4(aiMatrix, aiSizeMatrix, aiIndex);
                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiIndex[2]], aiSizeMatrix[aiIndex[2]]);
                wait();
                continue;
            }

            case 9: // TODO: Персональное задание 14 в курсовой работе
            {
                /**
                 * [ Персональное задание номер 14 ]:
                 * Вывести на экран те элементы матрицы С, которые равны сумме соответствующих элементов матриц А и В
                 */
                int aiIndex[3] = { 0 };
                bool bFlag = true;
                for (int iI = 0; iI < 3; iI++)
                {
                    aiIndex[iI] = selectMatrix(false);
                    if (aiIndex[iI] == -1)
                    {
                        bFlag = false;
                        break;
                    }
                }

                if (bFlag == false)
                    continue;

                std::cout << LOG_CL << "Output of the original matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiIndex[2]], aiSizeMatrix[aiIndex[2]]);
                wait();
                // task14(aiMatrix, aiSizeMatrix, aiIndex);
                std::cout << LOG_CL << "Output of the modified matrix" << RESET_CL << std::endl;
                printMatrix(aiMatrix[aiIndex[2]], aiSizeMatrix[aiIndex[2]]);
                wait();
                continue;
            }

            default: // Заного напечатать меню
            {
                continue;
            }
        }
    }
}

/**
 * Заголовок программы
 */
void title()
{
    std::cout << CLEAR
              << SUCCESS_CL << "\t\t\"Coursework on PROGRAMMING\" No. 1" << TITLE_CL << std::endl
              << "\tAuthor: Ilya Balakirev aka. MoonFoxy                    " << std::endl
              << "\tGitHub: https://github.com/MoonFoxy/                    " << std::endl
              << "\tFirst course                                            " << std::endl
              << "\tFaculty of Computer Technology and Informatics          " << std::endl
              << "\tManagement in technical systems                         " << std::endl
              << "\tGroup: 0391                                             " << std::endl
              << RESET_CL << std::endl;

    wait();
}

/**
 * Основная функция
 *
 * @return Код завершения программы
 */
int main()
{
    int ***aiMatrix = new int **[MATRIX_COUNT];
    int aiSizeMatrix[MATRIX_COUNT] = { 0 };
    title();
    bool bFlag = start(aiMatrix, aiSizeMatrix);
    if (bFlag)
        menu(aiMatrix, aiSizeMatrix);

    std::cout << std::endl
              << EXIT_CL << "\t\tExit the programm" << RESET_CL << std::endl;
    deleteAllMatrix(aiMatrix, aiSizeMatrix);
    return 0;
}
