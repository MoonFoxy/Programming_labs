#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int sd, flagg = 0;
struct sockaddr_un servAddr;
struct sockaddr_un clAddr;

void sig_handler(int fd)
{
    printf("Client is crushed or disconnect with server\n");
}

void *snd(void *flag)
{
    int *flag2 = (int *)flag;
    printf("Поток передачи начал работу\n");

    int rqstID = 1;
    while (*flag2 != 1)
    {
        int rv = sendto(sd, &rqstID, sizeof(rqstID), 0, (struct sockaddr *)&servAddr, sizeof(servAddr));
        if (rv != -1)
        {
            printf("Запрос %d передан\n", rqstID);
            rqstID++;
        }
        sleep(1);
    }
    printf("Поток передачи закончил работу\n");
    pthread_exit((void *)22);
}

void *rsv(void *flag)
{
    int *flag1 = (int *)flag;
    printf("Поток приема начал работу\n");

    dev_t devID;
    socklen_t len = sizeof(clAddr);
    ;
    char buffer[256];
    while (*flag1 != 1)
    {
        memset(buffer, 0, 256);
        int rv = recvfrom(sd, buffer, 256, 0, (struct sockaddr *)&clAddr, &len);
        if (rv == -1)
            sleep(1);
        else
            printf("received: buffer = |%s|\n", buffer);
    }
    printf("Поток приема закончил работу\n");
    pthread_exit((void *)11);
}

int main()
{
    signal(SIGPIPE, sig_handler);
    pthread_t th_rsv, th_snd;
    int exitcode1, exitcode2, optval = 1;

    sd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        perror("socket");
        return 0;
    }
    fcntl(sd, F_SETFL, O_NONBLOCK);

    servAddr.sun_family = AF_UNIX;
    strcpy(servAddr.sun_path, "srvsocket");

    clAddr.sun_family = AF_UNIX;
    strcpy(clAddr.sun_path, "clnsocket");

    if (bind(sd, (struct sockaddr *)&clAddr, sizeof(clAddr)) < 0)
    {
        perror("bind");
        close(sd);
        return 0;
    }
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    pthread_create(&th_rsv, NULL, rsv, &flagg);
    usleep(100);
    pthread_create(&th_snd, NULL, snd, &flagg);

    printf("Программа ждет нажатия клавиши\n");
    getchar();
    printf("Клавиша нажата\n");

    flagg = 1;
    pthread_join(th_rsv, (void **)&exitcode1);
    pthread_join(th_snd, (void **)&exitcode2);
    printf("exitcode th_rsv = %d\n", exitcode1);
    printf("exitcode th_snd = %d\n", exitcode2);

    close(sd);
    unlink("srvsocket");
    unlink("clnsocket");
    return 0;
}
