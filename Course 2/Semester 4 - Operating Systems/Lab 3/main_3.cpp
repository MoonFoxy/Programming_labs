#include <fcntl.h>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>

int pipefd[2];

#if 0
extern int sysinfo (struct sysinfo *info);
#endif

void *proc1(void *arg)
{
	std::cout << "Поток 1 начал работу." << std::endl;
	int *flag = (int *)arg;
	char buf[256];

	while (*flag == 0)
	{
		struct sysinfo info;
		int rv = sysinfo(&info);
		if (rv == 0)
		{
			sprintf(buf, "%ld", (long int)info.uptime);
		}
		write(pipefd[1], &buf, sizeof(buf));
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
	char buf[256];

	while (*flag == 0)
	{
		int rv = read(pipefd[0], &buf, sizeof(buf));
		if (rv == -1)
		{
			perror("pipe");
			sleep(1);
		}
		else if (rv == 0)
		{
			std::cout << "Это - Конец файла!" << std::endl;
			sleep(1);
		}
		else if (rv < 0)
		{
			perror("read");
			sleep(1);
		}
		else
		{
			std::cout << buf << std::endl;
			sleep(1);
		}
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

	pipe(pipefd);
	fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
	fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

	pthread_create(&id1, NULL, proc1, &flag1);
	pthread_create(&id2, NULL, proc2, &flag2);

	std::cout << "Программа ждёт нажатия клавиши." << std::endl;
	std::getchar(); // Wait for Enter key press

	std::cout << "[ Клавиша нажата ]" << std::endl;
	flag1 = 1;
	flag2 = 1;

	pthread_join(id1, (void **)&exitCode1);
	pthread_join(id2, (void **)&exitCode2);

	std::cout << "Поток 1 завершился с кодом " << *exitCode1 << std::endl;
	std::cout << "Поток 2 завершился с кодом " << *exitCode2 << std::endl;

	close(pipefd[0]);
	close(pipefd[1]);

	std::cout << std::endl
			  << "Программа завершила работу." << std::endl;
	return 0;
}
