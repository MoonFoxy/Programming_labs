/*
Программа должна оперировать тремя квадратными матрицами (А, В и С), размерность которых задается (или определяется) на фазе работы программы.

Необходимо:
  1) реализовать динамические структуры данных и алгоритмы их обработки, позволяющие поддерживать выполнение следующих функций:
    - консольный ввод/вывод данных о матрицах А, В и С;
    - файловый ввод/вывод данных о матрицах А, В и С;
    - интерактивное редактирование элементов матриц;
  2) разработать и реализовать алгоритмы обработки базы данных, предусмотренные персональным заданием.
*/

#include <iostream> // Для Консольного вывода/ввода
#include <cstring> // Для функции memcpy()
#include <unistd.h> // Для функции sleep()

#define MATRIX_COUNT 3

// Очистка консоли
#define CLEAR "\x1B[2J\x1B[H"

// Расцветка консоли
#define TITLE_CL "\x1b[30m\x1b[47m"
#define LOG_CL "\x1b[37m\x1b[44m"
#define WARN_CL "\x1b[30m\x1b[43m"
#define EXIT_CL "\x1b[30m\x1b[41m"
#define RESET_CL "\x1b[0m"

void loading()
{
    for (int iI = 0; iI < 2; iI++) {
        switch (iI)
        std::cout << '-' << std::flush;
        sleep(1);
        std::cout << "\b\\" << std::flush;
        sleep(1);
        std::cout << "\b|" << std::flush;
        sleep(1);
        std::cout << "\b/" << std::flush;
        sleep(1);
        std::cout << '\b' << std::flush;
    }

}

int ABCToInt(int iLetter)
{
    if (iLetter > 122) return -1;
    if (iLetter >= 97 && iLetter <= 122) iLetter -= 32;
    if (iLetter >= 65 && iLetter <= 90) iLetter -= 64;
    if (iLetter <= 57) iLetter -= 48;
    if (iLetter < 0 || iLetter > MATRIX_COUNT) return -1;
    return iLetter;
}

int getSingleIndex(int iRow, int iColumn, int iSize)
{
    return (iRow * iSize) + iColumn;
}

/**
 * Создает матрицу Size на Size все эллементы которой равны 0
 *
 * @param iSize Размер матрицы Size на Size
 * @return Готовая матрица все элементы которой равны 0
 */
int* createMatrix(int iSize)
{
    int iSizeSquare = iSize * iSize;
    int* aiMatrix = new int [iSizeSquare];
    for (int iI = 0; iI < iSizeSquare; iI++)
    {
        aiMatrix[iI] = 0;
    }
    return aiMatrix;
}

int* createMatrixFromTXT()
{

}

void resizeMatrix(int* aiMatrix, int iSize, int iNewSize)
{
    int iSizeSquare = iSize * iSize;
    int iNewSizeSquare = iNewSize * iNewSize;
    int iBias = iNewSize - iSize;
    if (iBias == 0) return;
    int* aiTemp = new int [iNewSizeSquare];

    memcpy(aiTemp, aiMatrix, iSizeSquare * sizeof(int));
    iSize = iNewSize;
    delete[] aiMatrix;
    aiMatrix = aiTemp;

    if (iBias > 0) {
        for (int iI = iSizeSquare; iI < iNewSizeSquare; iI++)
        {
            aiMatrix[iI] = 0;
        }
    }
}

void deleteMatrix(int** aiMatrix)
{
    for (int iI = 0; iI < MATRIX_COUNT; ++iI)
    {
        delete[] aiMatrix[iI];
    }
    delete[] aiMatrix;
}

void fillRandomMatrix(int* aiMatrix, int iSize)
{
    int iSizeSquare = iSize * iSize;
    for (int iI = 0; iI < iSizeSquare; iI++)
    {
        aiMatrix[iI] = rand() % 10;
    }
}

void printMatrix(int* aiMatrix, int iSize)
{
    for (int iI = 0; iI < iSize; iI++)
    {
        std::cout << '\t';
        for (int iJ = 0; iJ < iSize; iJ++)
        {
            std::cout << " " << aiMatrix[getSingleIndex(iI, iJ, iSize)];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int inputMatrixSize(char letter)
{
    int iSizeMatrix = 0;
    while (true)
    {
        std::cout << "Enter the size of the matrix " << letter << ": ";
        std::cin >> iSizeMatrix;
        if (iSizeMatrix <= 0)
        {
            std::cout << "!!! Matrix size must be greater than zero !!!" << std::endl << std::endl;
        }
        else break;
    }
    return iSizeMatrix;
}

int selectMatrix(int** aiMatrix)
{
    while (true)
    {
        std::cout << RESET_CL << CLEAR;
        std::cout << LOG_CL << "Select a matrix from the following:" << RESET_CL << std::endl;
        for (int iI = 0; iI < MATRIX_COUNT; iI++)
        {
            std::cout << LOG_CL << "\t[ " << (iI + 1) << " ]" << RESET_CL << " - " << char(iI + 65) << std::endl;
        }
        std::cout << std::endl;
        std::cout << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Exiting the program" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter answer: " << TITLE_CL;

        char iAnswer = -1;
        std::cin >> iAnswer;
        iAnswer = ABCToInt(iAnswer);

        std::cout << RESET_CL;

        if (iAnswer == -1)
        {
            std::cout << std::endl << WARN_CL << "!!! Wrong input !!!" << RESET_CL << std::endl;
            continue;
        }
        else if (iAnswer == 0) return -1;
        else return (iAnswer - 1);
    }
}

bool start(int** aiMatrix, int* iSizeMatrix)
{
    while (true)
    {
        std::cout << CLEAR;
        std::cout << LOG_CL << "Matrix input:" << RESET_CL << std::endl;
        std::cout << LOG_CL << "\t[ 1 ]" << RESET_CL << " - Creating a matrices filled with zeros ( 0 )" << std::endl;
        std::cout << LOG_CL << "\t[ 2 ]" << RESET_CL << " - Creating matrices filled with random numbers ( 0 - 10 )" << std::endl;
        std::cout << LOG_CL << "\t[ 3 ]" << RESET_CL << " - Filling matrices from a pre-entered .txt file" << std::endl;
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
            case 0:
            {
                return false;
            }

            case 1:
            {
                std::cout << CLEAR;
                std::cout << "\t " << std::endl;
                return true;
            }
            default:
            {
                continue;
            }
        }
    }
}

void menu(int** aiMatrix, int* iSizeMatrix)
{
    while (true)
    {
        std::cout << CLEAR;
        std::cout << LOG_CL << "Menu:" << RESET_CL << std::endl;
        std::cout << LOG_CL << "\t[ 1 ]" << RESET_CL << " - Change matrices via the console ( manual input )" << std::endl;
        std::cout << LOG_CL << "\t[ 2 ]" << RESET_CL << " - Fills matrices with zeros ( 0 )" << std::endl;
        std::cout << LOG_CL << "\t[ 3 ]" << RESET_CL << " - Fills existing matrices with random numbers ( 0 - 10 )" << std::endl;
        std::cout << LOG_CL << "\t[ 4 ]" << RESET_CL << " - Updates matrices with a pre-entered .txt file" << std::endl;
        std::cout << LOG_CL << "\t[ 5 ]" << RESET_CL << " - Resizes matrices" << std::endl;
        std::cout << LOG_CL << "\t[ 1 ]" << RESET_CL << " - " << std::endl;
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
            case 0:
            {
                return;
            }
            case 1:
            {
                int aiSelectedMatrix = selectMatrix(aiMatrix);
                if (aiSelectedMatrix == -1) continue;
                fillRandomMatrix(aiMatrix[aiSelectedMatrix], iSizeMatrix[aiSelectedMatrix]);
                printMatrix(aiMatrix[aiSelectedMatrix], iSizeMatrix[aiSelectedMatrix]);
                continue;
            }
            default:
            {
                continue;
            }
        }
    }
}

void title()
{
    std::cout << CLEAR;
    std::cout << LOG_CL << "\t\t\"Coursework on PROGRAMMING\" No. 1" << TITLE_CL << std::endl;
    std::cout << "\tAuthor: Ilya Balakirev aka. MoonFoxy                    " << std::endl;
    std::cout << "\tFirst course                                            " << std::endl;
    std::cout << "\tFaculty of Computer Technology and Informatics          " << std::endl;
    std::cout << "\tManagement in technical systems                         " << std::endl;
    std::cout << "\tGroup: 0391                                             " << RESET_CL << std::endl;

    sleep(5);
}

int main()
{
    int** aiMatrix = new int* [MATRIX_COUNT];
    int iSizeMatrix[MATRIX_COUNT] = { 0 };

    title();
    bool flag = start(aiMatrix, iSizeMatrix);
    if (flag)
    {
        for (int iI = 0; iI < MATRIX_COUNT; iI++)
        {
            int iSize = (iSizeMatrix[iI] = inputMatrixSize(iI + 65)); // 65 = A ( int в ASCII )
            aiMatrix[iI] = createMatrix(iSize);
            printMatrix(aiMatrix[iI], iSize);
        }

        menu(aiMatrix, iSizeMatrix);
    }


    std::cout << std::endl << EXIT_CL << "\t\tExit the programm" << RESET_CL << std::endl;
    deleteMatrix(aiMatrix);
    return 0;
}
