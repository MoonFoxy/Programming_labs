#include <iostream>
#include <limits>

// Очистка консоли
#define CLEAR "\x1B[2J\x1B[H"

// Расцветка консоли
#define LOG_CL "\x1b[37m\x1b[44m"
#define TITLE_CL "\x1b[30m\x1b[47m"
#define EXIT_CL "\x1b[30m\x1b[41m"
#define RESET_CL "\x1b[0m"

struct BSTree
{
    int iValue;
    BSTree *right;
    BSTree *left;
};

/**
 * Функция ожидания действия
 */
void wait()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar();
}

/**
 * Создание новой ветки дерева
 */
void newNode(int iElement, BSTree *(&node))
{
    if (node == nullptr)
    {
        node = new BSTree;
        node->iValue = iElement;
        node->left = node->right = nullptr;
        return;
    }

    if (iElement > node->iValue)
        newNode(iElement, node->right);
    else if (iElement < node->iValue)
        newNode(iElement, node->left);
}

int hight(BSTree *node)
{
    int iLeftHight = 0, iRightHight = 0;
    if (node == nullptr)
        return 0;

    if (node->left)
        iLeftHight = hight(node->left);

    if (node->right)
        iRightHight = hight(node->right);

    if (iLeftHight > iRightHight)
        return iLeftHight + 1;
    else
        return iRightHight + 1;
}

void task1(BSTree *node)
{
    if (node == nullptr)
        return;

    std::cout << node->iValue << " ";
    task1(node->left);
    task1(node->right);
}

void task2(BSTree *node)
{
    if (node == nullptr)
        return;

    task2(node->left);
    std::cout << node->iValue << " ";
    task2(node->right);
}

void task3(BSTree *node)
{
    if (node == nullptr)
        return;

    task3(node->left);
    task3(node->right);
    std::cout << node->iValue << " ";
}

void menu(BSTree *node)
{
    while(true)
    {
        std::cout << CLEAR
                  << LOG_CL << "Menu:" << RESET_CL << std::endl
                  << LOG_CL << "\t[ 1 ]" << RESET_CL << " - Output in prefix order" << std::endl  // Префиксный
                  << LOG_CL << "\t[ 2 ]" << RESET_CL << " - Output in index order" << std::endl   // Инфексный
                  << LOG_CL << "\t[ 3 ]" << RESET_CL << " - Output in postfix order" << std::endl // Постфиксный
                  << std::endl
                  << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Exiting the program" << std::endl
                  << std::endl
                  << "Enter answer: " << TITLE_CL;

        int iAnswer = -1;
        std::cin >> iAnswer;
        std::cout << RESET_CL;
        switch (iAnswer)
        {
            case 0:
            {
                return;
            }

            case 1:
            {
                std::cout << CLEAR
                          << "\tTask 1" << std::endl;

                task1(node);
                wait();
                continue;
            }

            case 2:
            {
                std::cout << CLEAR
                          << "\tTask 2" << std::endl;

                task2(node);
                wait();
                continue;
            }

            case 3:
            {
                std::cout << CLEAR
                          << "\tTask 3" << std::endl;

                task3(node);
                wait();
                continue;
            }

            default:
            {
                continue;
            }
        }
    }
}

int main()
{
    int iAnswer = 0;
    BSTree *node;
    node = nullptr;
    std::cout << "Enter tree elements: " << std::endl;
    std::cin >> iAnswer;

    while (iAnswer != 0)
    {
        newNode(iAnswer, node);
        std::cin >> iAnswer;
    }

    menu(node);
    return 0;
}
