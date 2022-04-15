#include <iostream>
#include <pthread.h>
#include <unistd.h>

void *proc1(void *arg)
{
    std::cout << "Поток 1 начал работу." << std::endl;
    int *flag = (int *)arg;

    while (*flag == 0)
    {
        std::cout << "Поток 1 выполняет работу..." << std::endl;
        sleep(1);
    }

    std::cout << "Поток 1 закончил работу." << std::endl;

    int *state = new int;
    *state = 0;
    pthread_exit(state);
}

void *proc2(void *arg)
{
    std::cout << "Поток 2 начал работу." << std::endl;
    int *flag = (int *)arg;

    while (*flag == 0)
    {
        std::cout << "Поток 2 выполняет работу..." << std::endl;
        sleep(1);
    }

    std::cout << "Поток 2 закончил работу." << std::endl;

    int *state = new int;
    *state = 0;
    pthread_exit(state);
}

int main()
{
    std::cout << "Программа начала работу." << std::endl;

    pthread_t id1;
    pthread_t id2;

    int flag1 = 0;
    int flag2 = 0;

    int *exitCode1;
    int *exitCode2;
    pthread_create(&id1, NULL, proc1, &flag1);
    pthread_create(&id2, NULL, proc2, &flag2);

    std::cout << "Программа ждёт нажатия клавиши." << std::endl;
    std::getchar(); // Wait for Enter key press

    std::cout << "Клавиша нажата." << std::endl;
    flag1 = 1;
    flag2 = 1;

    pthread_join(id1, (void **)&exitCode1);
    pthread_join(id2, (void **)&exitCode2);

    std::cout << "Поток 1 завершился с кодом " << *exitCode1 << std::endl;
    std::cout << "Поток 2 завершился с кодом " << *exitCode2 << std::endl;

    delete exitCode1;
    delete exitCode2;

    std::cout << "Программа завершила работу." << std::endl;
    return 0;
}
