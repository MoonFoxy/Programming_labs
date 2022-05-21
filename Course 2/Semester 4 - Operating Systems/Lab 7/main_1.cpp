#include <arpa/inet.h>
#include <csignal>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <mqueue.h>
#include <netdb.h>
#include <sys/sysinfo.h>
#include <unistd.h>

int flag = 0;
mqd_t qd;
char queue_name[] = { "/test_queue" };

void sig_handler (__attribute__((unused)) int signo)
{
    mq_close(qd);
    mq_unlink(queue_name);
    exit(0);
}

int main()
{
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    signal(SIGINT, sig_handler);

    struct mq_attr attr{};
    attr.mq_flags = 0;
    attr.mq_maxmsg = 20;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;

    qd = mq_open(queue_name, O_CREAT | O_WRONLY | O_NONBLOCK, 0644, &attr);
    if (qd == -1)
    {
        perror("mq_open");
    }

    char buf[256];
    while (flag != 1)
    {
        struct sysinfo info;
        int rv = sysinfo(&info);
        sprintf(buf, "%ld", (long int)info.uptime);
        std::cout << buf << std::flush;
        std::cout << std::endl;
        int send_status = mq_send(qd, buf, strlen(buf) + 1, 0);
        if (send_status  == -1)
        {
            perror("mq_send");
        }
        else
        {
            std::cout << "Okay" << std::endl;
        }
        sleep(1);
        if  (getchar()== '\n')
        {
           break;
        }
    }
    flag = 1;
    mq_close(qd);
    mq_unlink(queue_name);
    return 0;
}
