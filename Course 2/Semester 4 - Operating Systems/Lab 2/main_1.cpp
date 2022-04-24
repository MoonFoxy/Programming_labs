#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex;

void *proc1(void *arg) {
	std::cout << "Поток 1 начал работу." << std::endl;
	int *flag = (int *)arg;

	while (*flag == 0)
	{
		pthread_mutex_lock(&mutex);
		for (int i = 0; i < 10; i++)
		{
			std::cout << "1";
		}
		std::cout << std::flush;
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	std::cout << "Поток 1 закончил работу." << std::endl;

	int *state = new int;
	*state = 0;
	pthread_exit(state);
}

void *proc2(void *arg) {
	std::cout << "Поток 2 начал работу." << std::endl;
	int *flag = (int *)arg;

	while (*flag == 0)
	{
		pthread_mutex_lock(&mutex);
		for (int i = 0; i < 10; i++)
		{
			std::cout << "2";
		}
		std::cout << std::flush;
		pthread_mutex_unlock(&mutex);
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

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&id1, NULL, proc1, &flag1);
	pthread_create(&id2, NULL, proc2, &flag2);

	std::cout << "Программа ждёт нажатия клавиши." << std::endl;
	std::getchar(); // Wait for Enter key press

	std::cout << std::endl
			  << "[ Клавиша нажата ]" << std::endl;
	flag1 = 1;
	flag2 = 1;

	pthread_join(id1, (void **)&exitCode1);
	pthread_join(id2, (void **)&exitCode2);
	pthread_mutex_destroy(&mutex);

	std::cout << "Поток 1 завершился с кодом " << *exitCode1 << std::endl;
	std::cout << "Поток 2 завершился с кодом " << *exitCode2 << std::endl;

	delete exitCode1;
	delete exitCode2;

	std::cout << std::endl
			  << "Программа завершила работу." << std::endl;
	return 0;
}
