#include <iostream>
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
    int iTalkTimeLimit = 0;
    PhoneCall *tempCall, *bufferCall;
    tempCall = new PhoneCall;
    bufferCall = tempCall;
    while (true)
    {
        std::cout << "Enter the incoming number: " << std::endl;
        std::cin >> bufferCall->acIncomingNumber;
        if (bufferCall->acIncomingNumber[0] = '0' && bufferCall->acIncomingNumber[1] == '\0')
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

    while (true)
    {
        if (bufferCall == nullptr)
            break;

        std::cout << bufferCall->acIncomingNumber << "\t" << bufferCall->acOutgoingNumber << "\t" << bufferCall->iTalkTime << std::endl;
        bufferCall = bufferCall->next;
    }

    wait();
    // do
    // {
    //     tempCall = bufferCall;
    //     bufferCall = bufferCall->next;
    //     delete tempCall;
    // } while (bufferCall != nullptr);
    return 0;
}
