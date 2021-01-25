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
    int aiMatrix[10][10] = { 0 };
    for (int iI = 0; iI < 10; iI++)
        for (int iJ = 0; iJ <= (iI - 1); iJ++)
        {
            std::cout << CLEAR;
            while (true)
            {
                std::cout << "\tEnter the distance between cities!" << std::endl
                          << "City " << (iI + 1) << " to city " << (iJ + 1) << ": ";
                std::cin >> aiMatrix[iI][iJ];
                aiMatrix[iJ][iI] = aiMatrix[iI][iJ];
                if (aiMatrix[iI][iJ] < -1)
                    std::cout << CLEAR
                              << "\t\tWrong number!" << std::endl;
                else
                    break;
            }
        }

    int iAnswer = 0;
    do
    {
        std::cout << CLEAR
                  << "\tChoose an action!" << std::endl
                  << std::endl
                  << "[ 1 ] - Derivation of a matrix with distances between cities" << std::endl
                  << std::endl
                  << "[ 2 ] - ( Task A ) Display the number of the city farthest (by the average sum of distances) from other cities" << std::endl
                  << "[ 3 ] - ( Task B ) Display the numbers of cities that can be reached only from one neighboring city" << std::endl
                  << "[ 4 ] - ( Task C ) Display all pairs of city numbers, the length of the direct path between which does not exceed the value specified from the keyboard" << std::endl
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
                          << "\tMatrix with distances between cities" << std::endl;
                for (int iI = 0; iI < 10; iI++)
                {
                    std::cout << '\t';
                    for (int iJ = 0; iJ < 10; iJ++)
                        std::cout << '\t' << aiMatrix[iI][iJ];

                    std::cout << std::endl;
                }
                std::cout << std::endl;
                wait();
                continue;
            }

            case 2:
            {
                int iRemoteCity = 0;
                int iMaxAmountNullPaths = 0;
                int iMaxAverageDistance = 0;
                for (int iI = 0; iI < 10; iI++)
                {
                    int iAmountNullPaths = 0;
                    int iAverageDistance = 0;
                    for (int iJ = 0; iJ < 10; iJ++)
                        if (iI == iJ)
                            continue;
                        else if (aiMatrix[iI][iJ] < 0)
                            iAmountNullPaths++;
                        else
                            iAverageDistance += aiMatrix[iI][iJ];

                    if (iMaxAmountNullPaths < iAmountNullPaths)
                    {
                        iRemoteCity = iI + 1;
                        iMaxAmountNullPaths = iAmountNullPaths;
                        iMaxAverageDistance = iAverageDistance / 9;
                        continue;
                    }

                    iAverageDistance /= 9;
                    if ((iMaxAmountNullPaths == iAmountNullPaths) && (iAverageDistance > iMaxAverageDistance))
                    {
                        iRemoteCity = iI + 1;
                        iMaxAverageDistance = iAverageDistance;
                    }
                }

                std::cout << CLEAR
                          << "\tThe most remote city" << std::endl
                          << "City number: " << iRemoteCity << std::endl
                          << "Paths that do not exist: " << iMaxAmountNullPaths << std::endl
                          << "Average Distance: " << iMaxAverageDistance << std::endl;
                wait();
                continue;
            }

            case 3:
            {
                std::cout << CLEAR
                          << "\tCities that can only be accessed from one neighboring city" << std::endl
                          << "List of cities: ";
                for (int iI = 0; iI < 10; iI++)
                {
                    int iAmountNullPaths = 0;
                    for (int iJ = 0; iJ < 10; iJ++)
                        if (aiMatrix[iI][iJ] < 0)
                            iAmountNullPaths++;

                    if (iAmountNullPaths == 8)
                        std::cout << (iI + 1) << "; ";
                }

                std::cout << std::endl;
                wait();
                continue;
            }

            case 4:
            {
                int iInputDistance = 0;
                std::cout << CLEAR;
                while (true)
                {
                    std::cout << "\tPairs of cities, the length of the direct path between which does not exceed the value specified from the keyboard" << std::endl
                              << "Enter the distance that should not exceed the city: ";
                    std::cin >> iInputDistance;
                    if (iInputDistance <= 0)
                        std::cout << CLEAR
                                  << "\t\tWrong input!";
                    else
                        break;
                }

                std::cout << CLEAR
                          << "City pair sheet:" << std::endl;
                for (int iI = 0; iI < 10; iI++)
                    for (int iJ = 0; iJ <= (iI - 1); iJ++)
                        if (aiMatrix[iI][iJ] <= iInputDistance)
                            std::cout << '\t' << iI << " - " << iJ << std::endl;

                wait();
                continue;
            }
        }
    } while (iAnswer != 0);

    return 0;
}
