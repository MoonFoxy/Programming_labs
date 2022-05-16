#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[])
{
	std::cout << "\x1b[30m\x1b[43m[ Программа 1 ]\x1b[0m Идентификатор текущего процесса -> " << getpid() << std::endl;
	std::cout << "\x1b[30m\x1b[43m[ Программа 1 ]\x1b[0m Идентификатор родительского процесса -> " << getppid() << std::endl;
	std::cout << "\x1b[30m\x1b[43m[ Программа 1 ]\x1b[0m Список аргументов -> " << std::endl;
	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
		sleep(1);
	}
	std::cout << "\x1b[30m\x1b[43m[ Программа 1 ]\x1b[0m Код выхода -> " << 55 << std::endl;
	exit(55);
}
