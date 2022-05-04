#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid = fork();
    if (pid == 0)
    {
        std::cout << "\x1b[30m\x1b[42m[ Программа 2 ]\x1b[0m Идентификатор текущего процесса -> " << getpid() << std::endl;
        std::cout << "\x1b[30m\x1b[42m[ Программа 2 ]\x1b[0m Идентификатор родительского процесса -> " << getppid() << std::endl;
        execl("main_1", argv[0], argv[1], argv[2], NULL);
    }
    else if (pid > 0)
    {
        while (waitpid(pid, &status, WNOHANG) == 0)
        {
            std::cout << "\x1b[30m\x1b[42m[ Программа 2 ]\x1b[0m Ждемс..." << std::endl;
            usleep(500000); // In microseconds
        }

        std::cout << "\x1b[30m\x1b[42m[ Программа 2 ]\x1b[0m Код статуса завершения -> " << WEXITSTATUS(status) << std::endl;
    }
    else
    {
        perror("fork");
    }

    return 0;
}
