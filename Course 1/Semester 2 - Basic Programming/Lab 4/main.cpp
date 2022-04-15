#include <iostream>
#include <string.h>
#include <limits>

// Очистка консоли
#define CLEAR "\x1B[2J\x1B[H"

// Расцветка консоли
#define LOG_CL "\x1b[37m\x1b[44m"
#define TITLE_CL "\x1b[30m\x1b[47m"
#define EXIT_CL "\x1b[30m\x1b[41m"
#define RESET_CL "\x1b[0m"

struct PhoneCall
{
    char acIncomingNumber[12];
    char acOutgoingNumber[12];
    int iTalkTime;
    PhoneCall *next;
    PhoneCall *sorted;
};

/**
 * Функция ожидания действия
 */
void wait()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar();
}

void sortCalls(PhoneCall *(&back), PhoneCall *(&back1), PhoneCall *(&ptr1))
{
    PhoneCall *buf1, *buf2;
    if (strcmp(back->next->acIncomingNumber, back1->acIncomingNumber) >= 0)
    {
        back1->sorted = back->next;
        back1->sorted->sorted = nullptr;
        back1 = back1->next;
    }
    else if (strcmp(back->next->acIncomingNumber, ptr1->acIncomingNumber) < 0)
    {
        back->next->sorted = ptr1;
        ptr1 = back->next;
    }
    else
    {
        buf1 = ptr1;
        while (buf1 != back1)
        {
            if (strcmp(back->next->acIncomingNumber, buf1->sorted->acIncomingNumber) <= 0)
            {
                buf2 = buf1->sorted;
                buf1->sorted = back->next;
                back->next->sorted = buf2;
                break;
            }
            buf1 = buf1->sorted;
        }
    }
}

void output(PhoneCall *(&a), PhoneCall *(&b))
{
    a = b; // Вывод
    while (a != nullptr)
    {
        std::cout << a->acIncomingNumber << "\t" << a->acOutgoingNumber << "\t" << a->iTalkTime << std::endl;
        a = a->next;
    }
};

void output2(PhoneCall *(&a), PhoneCall *(&b))
{
    a = b; // Вывод
    while (a != nullptr)
    {
        std::cout << a->acIncomingNumber << "\t" << a->acOutgoingNumber << "\t" << a->iTalkTime << std::endl;
        a = a->sorted;
    }
};

void menu()
{
    std::cout << CLEAR
              << LOG_CL << "Menu:" << RESET_CL << std::endl
              << LOG_CL << "\t[ 1 ]" << RESET_CL << " - Display data on screen" << std::endl
              << LOG_CL << "\t[ 2 ]" << RESET_CL << " - Display data in ascending order of source number" << std::endl
              << LOG_CL << "\t[ 3 ]" << RESET_CL << " - Add node" << std::endl
              << std::endl
              << EXIT_CL << "\t[ 0 ]" << RESET_CL << " - Exiting the program" << std::endl;
};

int main()
{
    PhoneCall *bufferCall, *plusCall, *bufferNewCall, *bufferEndCall, *bufferNewEndCall;
    bufferEndCall = nullptr;
    bufferCall = nullptr;
    int iTalkTimeLimit = 0;
    char number[12] = " ";

    for (int i = 0;; i++)
    {
        std::cout << "Enter the incoming number: " << std::endl;
        std::cin >> number;
        if (!strcmp(number, "0\0") && bufferEndCall != nullptr)
        {
            bufferEndCall->next = nullptr;
            break;
        }
        else
        {
            if (i == 0)
            {
                bufferCall = new PhoneCall;
                strcpy(bufferCall->acIncomingNumber, number);
                bufferNewCall = bufferCall;
                bufferEndCall = bufferCall;
                bufferNewCall->sorted = nullptr;
                bufferNewEndCall = bufferCall;
            }
            else
            {

                bufferEndCall->next = new PhoneCall;
                strcpy(bufferEndCall->next->acIncomingNumber, number);
                sortCalls(bufferEndCall, bufferNewEndCall, bufferNewCall);
                bufferEndCall = bufferEndCall->next;
            };
            std::cout << "Enter outgoing number: " << std::endl;
            std::cin >> bufferEndCall->acOutgoingNumber;
            std::cout << "Enter a talk time: " << std::endl;
            std::cin >> bufferEndCall->iTalkTime;
        }
    }

    int choice = 0;

    do
    {
        menu();
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            output(bufferEndCall, bufferCall);
            wait();
            break;
        case 2:
            output2(bufferNewEndCall, bufferNewCall);
            wait();
            break;
        case 3:
            bufferEndCall->next = new PhoneCall;
            std::cout << "Enter the incoming number: " << std::endl;
            std::cin >> bufferEndCall->next->acIncomingNumber;
            std::cout << "Enter outgoing number: " << std::endl;
            std::cin >> bufferEndCall->next->acOutgoingNumber;
            std::cout << "Enter a talk time: " << std::endl;
            std::cin >> bufferEndCall->next->iTalkTime;
            sortCalls(bufferEndCall, bufferNewEndCall, bufferNewCall);
            bufferEndCall = bufferEndCall->next;
            bufferEndCall->next = nullptr;
            break;
        }

    } while (choice > 0);
    return 0;
}
