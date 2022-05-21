#include <csignal>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <mqueue.h>
#include <unistd.h>

int flag = 0;
mqd_t qd;
char queue_name[] = { "/test_queue" };

void sig_handler(__attribute__((unused)) int signo)
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

    qd = mq_open(queue_name, O_CREAT | O_RDONLY | O_NONBLOCK, 0644, &attr);
    if (qd == -1)
    {
        perror("mq_open");
    }
    char buf[256];
    while (flag != 1)
    {
        memset(buf, 0, 256);
        long send_status = mq_receive(qd, buf, 256, nullptr);
        if (send_status > 0)
        {
            std::cout << buf << std::flush;
            std::cout << std::endl;
        }
        else if (send_status == -1)
        {
            perror("mq_receive");
            sleep(1);
            continue;
        }
        if (getchar() == '\n')
        {
            break;
        }
    }
    flag = 1;
    mq_close(qd);
    mq_unlink(queue_name);
    return 0;
}
