#include <iostream>
#include <string.h>
#include <limits>

struct PhoneCall
{
    char acIncomingNumber[12];
    char acOutgoingNumber[12];
    int iTalkTime;
    PhoneCall *next;
};

/**
 * Функция ожидания действия
 */
void wait()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar();
}

int main()
{
    PhoneCall *tempCall, *bufferCall, *plusCall, *buffer2Call;
    int iTalkTimeLimit = 0, send_nudes = 0;
    char acDeleteNumber[12] = " ";
    tempCall = new PhoneCall;
    bufferCall = tempCall;
    while (true)
    {
        std::cout << "Enter the incoming number: " << std::endl;
        std::cin >> bufferCall->acIncomingNumber;
        if (bufferCall->acIncomingNumber[0] == '0' && bufferCall->acIncomingNumber[1] == '\0')
        {
            bufferCall->next = nullptr;
            break;
        }
        else
        {
            std::cout << "Enter outgoing number: " << std::endl;
            std::cin >> bufferCall->acOutgoingNumber;
            std::cout << "Enter a talk time: " << std::endl;
            std::cin >> bufferCall->iTalkTime;
            if (bufferCall->iTalkTime > iTalkTimeLimit)
                iTalkTimeLimit = bufferCall->iTalkTime;
        }
        bufferCall->next = new PhoneCall;
        bufferCall = bufferCall->next;
    }
    std::cout << "Talk time limit: " << iTalkTimeLimit << std::endl;
    bufferCall = tempCall;

    // Удаление по номеру источника
    std::cout << "Enter the INCOMING number you want to delete:" << std::endl;
    std::cin >> acDeleteNumber;

    while (strcmp(tempCall->acIncomingNumber, acDeleteNumber) == 0) // Функция удаления, если ячейка находится на 1 месте
    {
        plusCall = tempCall;
        tempCall = tempCall->next;
        delete plusCall;
    }

    bufferCall = tempCall;
    while (bufferCall->next != nullptr)
    {
        while (strcmp(bufferCall->next->acIncomingNumber, acDeleteNumber) == 0) // Функция удаления, если ячейка находится на любом месте
        {
            buffer2Call = bufferCall->next;
            bufferCall->next = bufferCall->next->next;
            delete buffer2Call;
        }
        bufferCall = bufferCall->next;
    }

    bufferCall = tempCall;
    plusCall = tempCall;
    int iTime = 0;
    while (bufferCall != nullptr)
    {
        if (bufferCall->iTalkTime > 5)
        {
            iTime = (bufferCall->iTalkTime) - 5;
            buffer2Call = bufferCall->next;          // Присваиваем к промежуточной ячейке следующий узел
            if ((bufferCall->iTalkTime) % 5 == 0) // Проверка на остаток
                send_nudes = ((bufferCall->iTalkTime) / 5) - 1;
            else
                (send_nudes = ((bufferCall->iTalkTime) / 5));

            plusCall->iTalkTime = 5;
            for (int iI = 0; iI < send_nudes; iI++) // Цикл который копирует информацию в новосозданную ячейку
            {
                plusCall->next = new PhoneCall;
                strcpy(plusCall->next->acIncomingNumber, plusCall->acIncomingNumber);
                strcpy(plusCall->next->acOutgoingNumber, plusCall->acOutgoingNumber);
                if (iTime > 5) // Запись времени в новую ячейку
                {
                    plusCall->next->iTalkTime = 5;
                    iTime = iTime - 5;
                }
                else
                {
                    plusCall->next->iTalkTime = iTime % 5;
                }

                if (iI == send_nudes - 1) // Создание новых ячеек
                {
                    plusCall = plusCall->next;
                    plusCall->next = buffer2Call;
                    plusCall = buffer2Call;
                }
                else
                    plusCall = plusCall->next;
            }
        }
        else
            bufferCall = bufferCall->next;
    }

    bufferCall = tempCall;  // Вывод (проверка программы)
    while (bufferCall->next != nullptr)
    {
        std::cout << bufferCall->acIncomingNumber << '\t' << bufferCall->acOutgoingNumber << '\t' << bufferCall->iTalkTime << std::endl;
        bufferCall = bufferCall->next;
    }

    wait();

    do  // Очистка памяти
    {
        tempCall = bufferCall;
        bufferCall = bufferCall->next;
        delete tempCall;
    } while (bufferCall != nullptr);
    return 0;
}
