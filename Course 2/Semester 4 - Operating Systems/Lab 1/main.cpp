#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *proc1(void *arg)
{
    std::cout << "Поток 1 начал работу." << std::endl;
    int *flag = (int *)arg;

    while (*flag == 0)
    {
        std::cout << "Поток 1 выполняет работу...\n";
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
        std::cout << "Поток 2 выполняет работу...\n";
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

    pthread_attr_t tattr;
    size_t stksize;

    int flag1 = 0;
    int flag2 = 0;

    int *exitCode1;
    int *exitCode2;

    pthread_attr_init(&tattr);
    if (pthread_attr_getstacksize(&tattr, &stksize) == 0)
    {
        std::cout << "Размер стека потока Поток 1 [ до ] -> " << stksize << std::endl;
    }

    if (pthread_attr_setstacksize(&tattr, stksize * 2) != 0)
    {
        std::cout << "Не удалось увеличить размер стека потока Поток 1" << std::endl;
    }

    if (pthread_attr_getstacksize(&tattr, &stksize) == 0)
    {
        std::cout << "Размер стека потока Поток 1 [ после ] -> " << stksize << std::endl;
    }
    pthread_create(&id1, &tattr, proc1, &flag1);
    pthread_create(&id2, NULL, proc2, &flag2);

    //------------------------------------------------------------------------------
    pthread_attr_t attrib;
    int rv = pthread_getattr_np(id1, &attrib);
    if (rv != 0)
    {
        printf("pthread_getattr_np: %s\n", strerror(rv));
    }

    pthread_attr_getstacksize(&attrib, &stksize);
    printf("Thread id1 stksize = %ld\n", stksize);
    //------------------------------------------------------------------------------

    std::cout << "Программа ждёт нажатия клавиши." << std::endl;
    std::getchar(); // Wait for Enter key press

    std::cout << std::endl
              << "[ Клавиша нажата ]" << std::endl;
    flag1 = 1;
    flag2 = 1;

    pthread_join(id1, (void **)&exitCode1);
    pthread_join(id2, (void **)&exitCode2);

    std::cout << "Поток 1 завершился с кодом " << *exitCode1 << std::endl;
    std::cout << "Поток 2 завершился с кодом " << *exitCode2 << std::endl;

    delete exitCode1;
    delete exitCode2;

    std::cout << std::endl
              << "Программа завершила работу." << std::endl;
    return 0;
}
