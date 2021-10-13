#include <iostream>
#include <limits>

#define CLEAR "\x1B[2J\x1B[H"

void wait()
{
    std::cout << std::endl
              << "Press enter to continue" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar();
}

int *enterXnY(bool bFlag = false, int iX = 0, int iY = 0)
{
    int *aiXnY = new int [2];
    bool bError = false;
    do
    {
        std::cout << std::endl;
        if (bFlag)
            std::cout << "[ " << iX << 'x' << iY << " ]" << std::endl;
        std::cout << (bError ? "Wrong input! " : "") << "X ( Row ): ";
        std::cin >> aiXnY[0];
    } while (bError = (aiXnY[0] <= 0) || (bFlag && aiXnY[0] > iX));

    bError = false;
    do
    {
        std::cout << std::endl;
        if (bFlag)
            std::cout << "[ " << iX << 'x' << iY << " ]" << std::endl;
        std::cout << (bError ? "Wrong input! " : "") << "Y ( Seat ): ";
        std::cin >> aiXnY[1];
    } while (bError = (aiXnY[1] <= 0) || (bFlag && aiXnY[1] > iY));

    if (bFlag)
    {
        aiXnY[0]--;
        aiXnY[1]--;
    }

    return aiXnY;
}

void printMatrix(int **aiMatrix, int iX, int iY)
{
    for (int iI = 0; iI < iX; iI++)
    {
        std::cout << '\t';
        for (int iJ = 0; iJ < iY; iJ++)
            std::cout << ' ' << aiMatrix[iI][iJ];

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << CLEAR
              << "Enter the size of the cinema!";

    int *aiXnY = enterXnY();
    int iX = aiXnY[0], iY = aiXnY[1];
    int **aiMatrix = new int *[iX];
    for (int iI = 0; iI < iX; iI++)
    {
        aiMatrix[iI] = new int[iY];
        for (int iJ = 0; iJ < iY; iJ++)
            aiMatrix[iI][iJ] = 0;
    }

    int iAnswer = 0;
    do
    {
        std::cout << CLEAR
                  << "Choose an action!" << std::endl
                  << "Size of the cinema " << iX << "x" << iY << std::endl
                  << std::endl
                  << "[ 1 ] - Fix the seat reservation" << std::endl
                  << "[ 2 ] - Cancel seat reservation" << std::endl
                  << "[ 3 ] - Display seats" << std::endl
                  << std::endl
                  << "[ 4 ] - ( Task A ) Calculate the total number of reserved seats" << std::endl
                  << "[ 5 ] - ( Task B ) Display a list like: \"Row number - Number of spectators\"" << std::endl
                  << "[ 6 ] - ( Task C ) Display a list of fully occupied hall rows" << std::endl
                  << "[ 7 ] - ( Task D ) Display the row number with the maximum number of reserved seats" << std::endl
                  << std::endl
                  << "[ 0 ] - Exit" << std::endl
                  << std::endl
                  << "Enter answer: ";
        std::cin >> iAnswer;

        switch (iAnswer)
        {
            default:
                continue;

            case 0:
                break;

            case 1:
            {
                std::cout << CLEAR
                        << "Enter input!";
                int *aiInput = enterXnY(true, iX, iY);
                int iInputX = aiInput[0], iInputY = aiInput[1];
                if (aiMatrix[iInputX][iInputY] == 0)
                {
                    aiMatrix[iInputX][iInputY] = 1;
                    std::cout << std::endl
                              << "Success";
                }
                else
                    std::cout << std::endl
                              << "Seat already fixed!";

                wait();
                continue;
            }

            case 2:
            {
                std::cout << CLEAR
                          << "Enter input!";
                int *aiInput = enterXnY(true, iX, iY);
                int iInputX = aiInput[0], iInputY = aiInput[1];
                if (aiMatrix[iInputX][iInputY] == 1)
                {
                    aiMatrix[iInputX][iInputY] = 0;
                    std::cout << std::endl
                              << "Success";
                }
                else
                    std::cout << std::endl
                              << "Seat already canceled!";

                wait();
                continue;
            }

            case 3:
            {
                std::cout << CLEAR;
                printMatrix(aiMatrix, iX, iY);
                wait();
                continue;
            }

            case 4:
            {
                int iCount = 0;
                for (int iI = 0; iI < iX; iI++)
                    for (int iJ = 0; iJ < iY; iJ++)
                        if (aiMatrix[iI][iJ] == 1)
                            iCount++;

                std::cout << CLEAR
                          << "In the cinema hall " << iX << 'x' << iY << ", " << iCount << " seats are reserved" << std::endl;
                wait();
                continue;
            }

            case 5:
            {
                std::cout << CLEAR;
                for (int iI = 0; iI < iX; iI++)
                {
                    int iCountSpectators = 0;
                    for (int iJ = 0; iJ < iY; iJ++)
                        if (aiMatrix[iI][iJ] == 1)
                            iCountSpectators++;

                    std::cout << "Row " << (iI + 1) << " - " << iCountSpectators << " spectators" << std::endl;
                }

                wait();
                continue;
            }

            case 6:
            {
                std::cout << CLEAR
                          << "Fully occupied rows: ";

                bool bFlag = true;
                for (int iI = 0; iI < iX; iI++)
                {
                    int iCountSpectators = 0;
                    for (int iJ = 0; iJ < iY; iJ++)
                        if (aiMatrix[iI][iJ] == 1)
                            iCountSpectators++;

                    if (iCountSpectators == iY)
                        std::cout << (iI + 1) << " ;";
                    else
                        bFlag = false;
                }

                if (!bFlag)
                    std::cout << "They are not!";

                std::cout << std::endl;
                wait();
                continue;
            }

            case 7:
            {
                int iMaxRow = 0;
                int iMaxSpectatorsRow = 0;
                for (int iI = 0; iI < iX; iI++)
                {
                    int iCountSpectators = 0;
                    for (int iJ = 0; iJ < iY; iJ++)
                        if (aiMatrix[iI][iJ] == 1)
                            iCountSpectators++;

                    if (iMaxSpectatorsRow < iCountSpectators)
                    {
                        iMaxSpectatorsRow = iCountSpectators;
                        iMaxRow = iI + 1;
                    }
                }

                if (iMaxRow > 0)
                    std::cout << CLEAR << "The " << iMaxRow << "th row has the most reserved seats " << iMaxSpectatorsRow << std::endl;
                else
                    std::cout << CLEAR << "The rows are empty" << std::endl;

                wait();
                continue;
            }
        }
    } while (iAnswer != 0);

    for (int iI = 0; iI < iX; iI++)
        delete[] aiMatrix[iI];

    delete[] aiMatrix;

    wait();
    return 0;
}
