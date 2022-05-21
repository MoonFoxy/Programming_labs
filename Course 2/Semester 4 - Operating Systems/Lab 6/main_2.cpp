#include <climits>
#include <csignal>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <semaphore.h>
#include <sys/mman.h>
#include <unistd.h>

int flag = 0;
sem_t *semwrite;
sem_t *semready;
char *divide;
char buf[256];
int shm;
void sig_handler(__attribute__((unused)) int signo)
{
    sem_close(semready);
    sem_unlink("/ready");
    sem_close(semwrite);
    sem_unlink("/write");
    munmap(divide, 256);
    close(shm);
    shm_unlink("/user");
    exit(0);
}

int main()
{
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    signal(SIGINT, sig_handler);
    shm = shm_open("/user", O_CREAT | O_RDWR, 0644);
    ftruncate(shm, 256);
    divide = (char *)mmap(nullptr, PATH_MAX, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);
    semwrite = sem_open("/write", O_CREAT, 0644, 0);
    semready = sem_open("/ready", O_CREAT, 0644, 0);
    while (flag == 0)
    {
        sem_wait(semwrite);
        memcpy(buf, divide, 256);
        std::cout << buf << std::flush;
        std::cout << std::endl;
        sem_post(semready);
        if (getchar() == '\n')
        {
            break;
        }
    }
    flag = 1;
    sem_close(semready);
    sem_unlink("/ready");
    sem_close(semwrite);
    sem_unlink("/write");
    munmap(divide, 256);
    close(shm);
    shm_unlink("/user");
}
