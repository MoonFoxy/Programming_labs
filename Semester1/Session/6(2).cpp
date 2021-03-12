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

int main()
{
    int aiMatrix[2][5][5] = { 0 };
    for (int iI = 0; iI < 2; iI++)
    {
        std::cout << CLEAR
                  << "\tMatrix size 5x5" << std::endl
                  << "Enter the value for matrix " << (iI + 1) << ": ";
        for (int iJ = 0; iJ < 5; iJ++)
            for (int iK = 0; iK < 5; iK++)
                std::cin >> aiMatrix[iI][iJ][iK];
    }

    int iAnswer = 0;
    do
    {
        std::cout << CLEAR
                  << "\tChoose an action!" << std::endl
                  << std::endl
                  << "[ 1 ] - Display 2 matrices" << std::endl
                  << std::endl
                  << "[ 2 ] - ( Task A ) " << std::endl
                  << "[ 3 ] - ( Task B ) " << std::endl
                  << "[ 4 ] - ( Task C ) " << std::endl
                  << "[ 5 ] - ( Task D ) " << std::endl
                  << "[ 6 ] - ( Task E ) " << std::endl
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
                for (int iI = 0; iI < 2; iI++) {
                    std::cout << CLEAR
                              << "\tMatrix №" << (iI + 1) << std::endl;
                    for (int iJ = 0; iJ < 5; iJ++)
                    {
                        std::cout << '\t';
                        for (int iK = 0; iK < 5; iK++)
                            std::cout << '\t' << aiMatrix[iI][iJ][iK];

                        std::cout << std::endl;
                    }
                    std::cout << std::endl;
                    wait();
                }
                continue;
            }

            case 2:
            {
                int iCount = 0;
                for (int iI = 0; iI < 5; iI++)
                    for (int iJ = 0; iJ < 5; iJ++)
                    {
                        int iTempCount = 0;
                        for (int iK = 0; iK < 5 && (iTempCount += int(aiMatrix[0][iI][iK] == aiMatrix[1][iK][iJ])); iK++);

                        if (iTempCount == 5)
                        {
                            iCount++;
                            break;
                        }
                    }

                std::cout << CLEAR
                          << "\t( Task A )" << std::endl
                          << "Number of coincidences: " << iCount << std::endl;
                wait();
                continue;
            }

            case 3:
            {
                std::cout << CLEAR
                          << "\t( Task B )" << std::endl;
                int iCount = 0;
                for (int iI = 0; iI < 5; iI++)
                {
                    int iJ = 0;
                    int iTempCount = 0;
                    for (iJ = 0; iJ < 5 && (iTempCount += int(aiMatrix[0][iI][iJ] == aiMatrix[1][iI][iJ])); iJ++);

                    if (iTempCount == 5)
                    {
                        std::cout << '\t';
                        for (iJ = 0; iJ < 5; iJ++)
                            std::cout << '\t' << aiMatrix[1][iI][iJ];

                        std::cout << std::endl;
                    }
                }
                std::cout << "Number of coincidences: " << iCount << std::endl;
                wait();
                continue;
            }

            case 4:
            {
                int aiMatches[25] = { 0 };
                int iMatchesIndex = 0;
                int iX = 0;
                int iY = 0;
                for (int iI = 0; iI < 25; iI++)
                {
                    bool bFlag = true;
                    int iElement = aiMatrix[0][iY][iX];
                    for (int iJ = 0; iJ < iMatchesIndex; iJ++)
                        if (iElement == aiMatches[iJ])
                        {
                            bFlag = false;
                            break;
                        }

                    if (bFlag)
                    {
                        bFlag = true;
                        for (int iJ = iY; bFlag && iJ < 5; iJ++)
                            for (int iK = iX; iK < 5; iK++)
                                if (iElement == aiMatrix[1][iJ][iK])
                                {
                                    aiMatches[++iMatchesIndex] = iElement;
                                    bFlag = false;
                                    break;
                                }
                    }

                    if (iX == 4)
                    {
                        iX = 0;
                        iY++;
                    }
                    else
                        iX++;
                }

                std::cout << CLEAR
                          << "Found elements: " << std::endl;

                for (int iI = 0; iI < iMatchesIndex; iI++)
                    std::cout << CLEAR
                              << aiMatches[iI] << "; ";

                std::cout << std::endl;
                wait();
                continue;
            }

            case 5:
            {
                int iTotalCountZeros = 0;
                for (int iI = 0; iI < 5; iI++)
                {
                    int iSum[2] = { 0 };
                    int iCountZeros = 0;
                    for (int iJ = 0; iJ < 5; iJ++)
                    {
                        iSum[0] += aiMatrix[0][iJ][iI];
                        iSum[1] += aiMatrix[1][iJ][iI];
                        iCountZeros += int(aiMatrix[0][iJ][iI] == 0);
                    }

                    if (iSum[0] > iSum[1])
                        iTotalCountZeros += iCountZeros;
                }

                std::cout << CLEAR
                          << "Total number of zeros: " << iTotalCountZeros << std::endl;
                wait();
                continue;
            }

            case 6:
            {
                wait();
                continue;
            }
        }
    } while (iAnswer != 0);
}
