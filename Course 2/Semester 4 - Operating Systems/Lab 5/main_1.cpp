#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

sem_t *sem;

void *proc(void *arg)
{
	std::cout << "Поток 1 начал работу." << std::endl;
	int *flag = (int *)arg;
	std::ofstream file;
	int count;

	file.open("file.txt", std::ofstream::app);
	if (!file.is_open())
	{
		std::cout << "Не удалось открыть файл" << std::endl;
		return 0;
	}

	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

	while (*flag == 0)
	{
		count = sem_wait(sem);
		if (count == -1)
		{
			perror("sem_wait");
		}

		for (int i = 0; i < 5; ++i)
		{
			file << 1 << std::flush;
			std::cout << 1 << std::flush;
			sleep(1);
		}

		count = sem_post(sem);
		if (count == -1)
		{
			perror("sem_post");
		}
		sleep(1);
	}

	file.close();

	std::cout << "Поток 1 закончил работу." << std::endl;

	int *state = new int;
	*state = 0;
	pthread_exit(state);
}

int main()
{
	std::cout << "Программа начала работу." << std::endl;

	pthread_t id;

	int flag = 0;
	int count;

	int *exitCode;

	sem = sem_open("/OS", O_CREAT, 0777, 1);
	if (sem == SEM_FAILED)
	{
		perror("sem_open");
		return 1;
	}

	pthread_create(&id, NULL, proc, &flag);

	std::cout << "Программа ждёт нажатия клавиши." << std::endl;
	std::getchar(); // Wait for Enter key press

	std::cout << "[ Клавиша нажата ]" << std::endl;
	flag = 1;

	pthread_join(id, (void **)&exitCode);

	count = sem_close(sem);
	if (count == -1)
	{
		perror("sem_close");
		return 1;
	}

	count = sem_unlink("/OS");
	if (count == -1)
	{
		perror("sem_unlink");
		return 1;
	}

	std::cout << "Поток 1 завершился с кодом " << *exitCode << std::endl;

	std::cout << std::endl
			  << "Программа завершила работу." << std::endl;
	return 0;
}
