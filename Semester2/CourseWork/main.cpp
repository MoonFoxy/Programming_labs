/*
Общая часть задания:
	Студент потока характеризуется следующими данными:
		- ФИО (до 50 символов);
		- номер группы;
		- набор из пяти оценок за последнюю сессию (без указания предметов);
		- размер стипендии.

	Необходимо:
		1) разработать (и программно реализовать) динамические структуры данных и алгоритмы их обработки, позволяющие поддерживать выполнение следующих функций:
			- консольный ввод/вывод данных о всех студентах потока;
			- файловый ввод/вывод данных о потоке;
			- редактирование данных о студентах и группах потока, включающее операции добавления/удаления групп и студентов;

		2) разработать и программно реализовать алгоритмы обработки базы данных, предусмотренные персональным заданием

Примеры персональных заданий:
	1) Вариант 4:
		Вывести в порядке возрастания номера групп, в которых соотношение «суммарный объем стипендии» / «общее количество баллов» превышает заданное значение

	2) Вариант 14:
		Вывести на экран в порядке возрастания номера групп, в которых процент троечников и двоечников превышает заданное с клавиатуры значение
*/

#include <iostream> // Для Консольного ввода/вывода
#include <fstream>	// Для Файлового ввода/вывода
#include <cstring>	// Для функции memcmp
#include <limits>	// Для очищении потока консоли

// Файл для записи и чтения данных ( Полный путь до файла ) < Стандартное значение >
#define TEXT_FILE "./file.txt"

// Очистка консоли ( Коряво работает )
#define CLEAR "\x1B[2J\x1B[H"

std::ofstream fileOut;
std::ifstream fileIn;

struct Student	// Список студентов
{
	char acName[100];       // Имя Студента
	char acGroup[5] = " ";  // Номер группы студента
	int iGrant;            // Степендия студента
	int aiGrades[5];        // Оценки студента
	int iSumOfGrades = 0;	// Сумма баллов студента
	double dScore;          // Значение показателя «средний балл» / «объем стипендии»

	Student *nextStudent;  // Ссылка на следующего студента в порядке ввода
};

struct Group	// Список групп
{
	char acGroup[5] = " ";				// Номер группы

	Student *firstStudent{ nullptr };	// Указатель на первого студента в порядке ввода
	Student *lastStudent{ nullptr };	// Ссылка на последнего студента в порядке ввода
	Student *topStudent;				// Студент, имеющий максимальное значение показателя «средний балл» / «объем стипендии»

	Group *nextGroup{ nullptr };		// Указатель на следующую группу в порядке ввода
	Group *nextGroupSorted{ nullptr };	// Указатель на следующую группу в алфавитном порядке
};

/**
 * Функция ожидания действия ( Работает только через ENTER )
 */
void wait()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getchar();
}

/**
 * Заголовок программы
 */
void title()
{
	std::cout << CLEAR
			  << "\t\t\"Coursework on PROGRAMMING\" No. 2" << std::endl
			  << "\tAuthor: Ilya Balakirev aka. MoonFoxy" << std::endl
			  << "\tGitHub: https://github.com/MoonFoxy/ ( Plz don't )" << std::endl
			  << "\tSecond course" << std::endl
			  << "\tFaculty of Computer Technology and Informatics" << std::endl
			  << "\tManagement in technical systems" << std::endl
			  << "\tGroup: 0391" << std::endl
			  << std::endl;

	wait();
}

void output(Group *(&head), Group *(&back))
{
	Group *buffer{ nullptr };
	buffer = head;
	while (buffer)
	{
		buffer->lastStudent = buffer->firstStudent;
		while (buffer->lastStudent)
		{
			std::cout << "Name:" << buffer->lastStudent->acName << std::endl
					  << "Group number:" << buffer->lastStudent->acGroup << std::endl
					  << "Evaluations:";

			for (int iI = 0; iI < 5; iI++)
				std::cout << buffer->lastStudent->aiGrades[iI] << "  "
						  << std::endl
						  << "Grants size:" << buffer->lastStudent->iGrant << std::endl;

			buffer->lastStudent = buffer->lastStudent->nextStudent;
		}

		buffer = buffer->nextGroup;
	}
}

void sort_top(Group *(&tailSorted), Group *(&tail), Group *(&head), int iKey)
{

	Group *buffer, *bufferSwap;
	buffer = head;
	if (iKey != 0)
	{
		buffer = tail;
		if (strcmp(tail->topStudent->acName, buffer->topStudent->acName) >= 0)
		{
			buffer->nextGroupSorted = head;
			head = buffer;
		}
		else if (strcmp(tail->topStudent->acName, tailSorted->topStudent->acName) < 0)
		{
			tailSorted->nextGroupSorted = buffer;
			tailSorted = buffer;
			tailSorted->nextGroupSorted = nullptr;
		}
		else
		{
			buffer = head;
			while (buffer != tailSorted)
			{
				if (strcmp(tail->topStudent->acName, tailSorted->topStudent->acName) <= 0)
				{
					bufferSwap = buffer->nextGroupSorted;
					buffer->nextGroupSorted = tail;
					tail->nextGroupSorted = bufferSwap;
					break;
				}
				buffer = buffer->nextGroupSorted;
			}
		}
		buffer = buffer->nextGroupSorted;
	}
	else
	{
		while (buffer->nextGroupSorted)
		{
			if (buffer == tail)
			{

				if (strcmp(tail->topStudent->acName, buffer->topStudent->acName) <= 0)
				{
					buffer->nextGroupSorted = head;
					head = buffer;
					break;
				}
				else if (strcmp(tail->topStudent->acName, tailSorted->topStudent->acName) > 0)
				{
					tailSorted->nextGroupSorted = buffer;
					tailSorted = buffer;
					tailSorted->nextGroupSorted = nullptr;
					break;
				}
				else
				{
					buffer = head;
					while (buffer != tailSorted)
					{
						if (strcmp(tail->topStudent->acName, tailSorted->topStudent->acName) < 0)
						{
							bufferSwap = buffer->nextGroupSorted;
							buffer->nextGroupSorted = tail;
							tail->nextGroupSorted = bufferSwap;
							break;
						}
						buffer = buffer->nextGroupSorted;
					}
					break;
				}
			}
			buffer = buffer->nextGroupSorted;
		}
	}
}

void fileInput(Group *(&head), Group *(&back), Group *(&headSorted), Group *(&backSorted))
{
	Group *buffer;
	char acGroup[5];
	std::string name = TEXT_FILE;

	fileIn.open(name);
	fileIn >> acGroup;
	{
		while (!strcmp(acGroup, "0\0"))
		{
			int iKey = 0;
			if (!head)
			{
				head = new Group;
				back = head;
				headSorted = head;
				backSorted = head;
				strcpy(head->acGroup, acGroup);
				buffer = head;
				back->nextGroup = nullptr;
				backSorted->nextGroupSorted = nullptr;
			}
			else
			{
				buffer = head;
				while (true)
				{
					if (!strcmp(buffer->acGroup, acGroup))
					{
						break;
					}
					if (!buffer->nextGroup)
					{
						back->nextGroup = new Group;
						back = back->nextGroup;
						back->nextGroup = nullptr;
						back->nextGroupSorted = nullptr;

						strcpy(back->acGroup, acGroup);

						break;
					}
					else
						buffer = buffer->nextGroup;
				}
			}
			if (!back->firstStudent)
			{
				back->firstStudent = new Student; // Создаём узел для нового студентав в новой группе
				back->lastStudent = back->firstStudent;

				back->topStudent = back->firstStudent; // Добавляем нового студента в начало сортировочного списка

				back->firstStudent->nextStudent = nullptr;
				iKey++;
			}
			else
			{
				back->lastStudent->nextStudent = new Student; // Создаём узел для нового студента в уже имеющейся группе группе
				back->lastStudent = back->lastStudent->nextStudent;
				back->lastStudent->nextStudent = nullptr;
			}
			fileIn.getline(back->lastStudent->acName, 100);
			strcpy(back->lastStudent->acGroup, back->acGroup);

			for (int iI = 0; iI < 5; iI++)
			{
				fileIn >> back->lastStudent->aiGrades[iI];
				back->lastStudent->iSumOfGrades += back->lastStudent->aiGrades[iI];
			}
			fileIn >> back->lastStudent->iGrant;
			back->lastStudent->dScore = back->lastStudent->iSumOfGrades / back->lastStudent->iGrant;
			if (head->nextGroup && iKey != 0)
			{
				sort_top(backSorted, back, headSorted, iKey);
			}

			else if (back->topStudent->dScore < back->lastStudent->dScore)
			{
				back->topStudent = back->lastStudent;
				sort_top(backSorted, back, headSorted, iKey);
			}
			fileIn >> acGroup;
		}
	}
	fileIn.close();
}

void fileOutput(Group *(&head), Group *(&back))
{
	std::string name = TEXT_FILE;
	Group *buffer{ nullptr };
	buffer = head;
	std::cout << "Enter the file name to save: " << std::endl;
	std::cin >> name;
	fileOut.open(name);
	{
		while (buffer)
		{
			buffer->lastStudent = buffer->firstStudent;
			while (buffer->lastStudent)
			{
				fileOut << buffer->lastStudent->acName << std::endl;
				fileOut << buffer->lastStudent->acGroup << std::endl;
				for (int iI = 0; iI < 5; iI++)
					fileOut << buffer->lastStudent->aiGrades[iI] << "  ";
				fileOut << std::endl
					<< buffer->lastStudent->iGrant << std::endl;
				buffer->lastStudent = buffer->lastStudent->nextStudent;
			}
			buffer = buffer->nextGroup;
		}
	}
	fileOut.close();
}

void topDelete(Group *(&head), Group *(&back), Student *(&temp))
{
	Group *bufferGroup;
	Student *bufferStudent;
	bufferGroup = head;

	if (bufferGroup->topStudent == temp)
	{
		bufferStudent = bufferGroup->firstStudent;
		bufferGroup->topStudent = bufferStudent;
		if (bufferStudent == temp)
			bufferStudent = bufferStudent->nextStudent;
		while (bufferStudent)
		{
			if (temp != bufferStudent && bufferStudent->dScore > bufferGroup->topStudent->dScore)
				bufferGroup->topStudent = bufferStudent;
			bufferStudent = bufferStudent->nextStudent;
		}
		head->topStudent = bufferStudent;
	}
	bufferGroup = bufferGroup->nextGroupSorted;
	while (bufferGroup)
	{
		if (bufferGroup->topStudent == temp)
		{
			if (bufferGroup->nextGroupSorted == back)
				back = bufferGroup;

			bufferGroup->nextGroupSorted = bufferGroup->nextGroupSorted->nextGroupSorted;
		}
		else
			bufferGroup = bufferGroup->nextGroupSorted;
	}
}

void formDelete(Group *(&head), Group *(&back), Group *(&headSorted), Group *(&backSorted))
{
	Group *bufferGroup;
	Student *bufferStudent{ nullptr };
	char acBufferStudentName[100];
	char acBufferGroup[5];
	bufferGroup = head;

	std::cout << "Enter the group" << std::endl;
	std::cin >> acBufferGroup;
	while (bufferGroup)
	{
		if (strcmp(bufferGroup->acGroup, acBufferGroup))
			break;
		else
		{
			if (!bufferGroup->nextGroup)
			{
				std::cout << "You entered a group that is not listed." << std::endl;
				return;
			}
		}
		bufferGroup = bufferGroup->nextGroup;
	}
	std::cout << "Enter a name to delete." << std::endl;
	std::cin.getline(acBufferStudentName, 100);
	bufferStudent = bufferGroup->firstStudent;
	while (bufferStudent)
	{
		while (strcmp(bufferStudent->acName, acBufferStudentName) == 0) // Функция удаления, если ячейка находится на 1 месте
		{
			if (bufferStudent == bufferGroup->topStudent)
			{
				topDelete(headSorted, backSorted, bufferStudent);
			}
			bufferGroup->firstStudent = bufferGroup->firstStudent->nextStudent;
			delete bufferStudent;
			bufferStudent = nullptr;
			return;
		}
		while (bufferStudent->nextStudent)
		{
			while (strcmp(bufferStudent->nextStudent->acName, acBufferStudentName) == 0) // Функция удаления, если ячейка находится на любом месте
			{
				if (!bufferStudent->nextStudent->nextStudent)
				{
					bufferStudent = back->lastStudent;
					topDelete(headSorted, backSorted, bufferStudent);
					back->lastStudent->nextStudent = nullptr;
					delete bufferStudent;
					bufferStudent = nullptr;
					return;
				}
				else
				{
					bufferStudent = bufferStudent->nextStudent;
					bufferStudent->nextStudent = bufferStudent->nextStudent->nextStudent;
					topDelete(headSorted, backSorted, bufferStudent);
					delete bufferStudent;
					bufferStudent = nullptr;
					return;
				}
			}
			bufferStudent = bufferStudent->nextStudent;
		}
	}
}

void formEdit(Group *(&head), Group *(&back), Group *(&headSorted), Group *(&backSorted))
{
	Group *bufferGroup{ nullptr }, *bufferGroupSorted{ nullptr };
	Student *bufferStudent{ nullptr };
	char acBufferStudentName[100];
	char acBufferGroup[5];
	bufferGroup = head;
	std::cout << "Enter a name to edit:" << std::endl;
	std::cin.getline(acBufferStudentName, 100);
	while (bufferGroup)
	{
		bufferStudent = bufferGroup->firstStudent;
		while (bufferStudent)
		{
			if (strcmp(acBufferStudentName, bufferStudent->acName) == 0)
			{
				std::cout << "What do you want to change?" << std::endl
						  << "[ 1 ] - Student name" << std::endl
						  << "[ 2 ] - Student grades" << std::endl
						  << "[ 3 ] - Student grant" << std::endl;
				int iChoice = 0;
				std::cin >> iChoice;
				switch (iChoice)
				{
					case 1:
					{
						std::cout << "Enter the new student name:" << std::endl;
						std::cin.getline(bufferStudent->acName, 100);
						std::cin.getline(bufferStudent->acName, 100);
						if (bufferGroup->topStudent == bufferStudent)
						{
							bufferGroupSorted = headSorted;
							if (bufferGroupSorted->topStudent == headSorted->topStudent)
							{
								headSorted->nextGroupSorted = headSorted->nextGroupSorted->nextGroupSorted;
							}
							else
							{
								while (bufferGroupSorted)
								{

									if (bufferGroupSorted->topStudent == bufferStudent)
									{
										if (bufferGroupSorted->nextGroupSorted == back)
										{
											back = bufferGroupSorted;
										}
										bufferGroupSorted->nextGroupSorted = bufferGroupSorted->nextGroupSorted->nextGroupSorted;
									}
									else
										bufferGroupSorted = bufferGroupSorted->nextGroupSorted;
								}
								sort_top(backSorted, bufferGroup, headSorted, 1);
							}
						}
					};
					break;

					case 2:
					{
						std::cout << "New student grades:" << std::endl;
						bufferStudent->dScore = 0;
						for (int iI = 0; iI < 5; iI++)
						{
							std::cin >> bufferStudent->aiGrades[iI];
							bufferStudent->dScore += bufferStudent->aiGrades[iI];
						}
						if (bufferGroup->topStudent == bufferStudent)
						{
							bufferStudent->dScore = bufferStudent->iSumOfGrades / bufferStudent->iGrant;
							bufferGroupSorted = head;
							while (bufferGroupSorted)
							{
								if (bufferGroupSorted->topStudent->dScore < bufferStudent->dScore)
								{
									bufferGroupSorted->topStudent = bufferStudent;
								}
								bufferGroupSorted = bufferGroupSorted->nextGroup;
							}
							bufferGroupSorted = headSorted;
							if (bufferGroupSorted->topStudent == headSorted->topStudent)
							{
								headSorted->nextGroupSorted = headSorted->nextGroupSorted->nextGroupSorted;
							}
							else
							{
								while (bufferGroupSorted)
								{

									if (bufferGroupSorted->topStudent == bufferStudent)
									{
										if (bufferGroupSorted->nextGroupSorted == back)
										{
											back = bufferGroupSorted;
										}
										bufferGroupSorted->nextGroupSorted = bufferGroupSorted->nextGroupSorted->nextGroupSorted;
									}
									else
										bufferGroupSorted = bufferGroupSorted->nextGroupSorted;
								}
								sort_top(backSorted, bufferGroup, headSorted, 1);
							}
						}
					};
					break;

					case 3:
					{
						std::cout << "Enter the new student grant:" << std::endl;
						std::cin >> bufferStudent->iGrant;
						if (bufferGroup->topStudent == bufferStudent)
						{
							bufferStudent->dScore = bufferStudent->iSumOfGrades / bufferStudent->iGrant;
							bufferGroupSorted = head;
							while (bufferGroupSorted)
							{
								if (bufferGroupSorted->topStudent->dScore < bufferStudent->dScore)
								{
									bufferGroupSorted->topStudent = bufferStudent;
								}
								bufferGroupSorted = bufferGroupSorted->nextGroup;
							}
							bufferGroupSorted = headSorted;
							if (bufferGroupSorted->topStudent == headSorted->topStudent)
							{
								headSorted->nextGroupSorted = headSorted->nextGroupSorted->nextGroupSorted;
							}
							else
							{
								while (bufferGroupSorted)
								{

									if (bufferGroupSorted->topStudent == bufferStudent)
									{
										if (bufferGroupSorted->nextGroupSorted == back)
										{
											back = bufferGroupSorted;
										}
										bufferGroupSorted->nextGroupSorted = bufferGroupSorted->nextGroupSorted->nextGroupSorted;
									}
									else
										bufferGroupSorted = bufferGroupSorted->nextGroupSorted;
								}
								sort_top(backSorted, bufferGroup, headSorted, 1);
							}
						}
					};
					break;
				}
			}
			bufferStudent = bufferStudent->nextStudent;
		}
		bufferGroup = bufferGroup->nextGroup;
	}
}

void groupAdd(Group *(&head), Group *(&back), Group *(&headSorted), Group *(&backSorted))
{
	Group *bufferGroup;
	char acGroup[5];

	while (true)
	{
		std::cout << "Enter the group number or '0' to exit the menu:" << std::endl;
		std::cin >> acGroup;
		int t = 0;

		if (!strcmp(acGroup, "0\0"))
		{
			std::cout << std::endl
					  << "Data entry is complete." << std::endl;
			break;
		}
		if (!head)
		{
			head = new Group;
			back = head;
			headSorted = head;
			backSorted = head;
			strcpy(head->acGroup, acGroup);
			bufferGroup = head;
			back->nextGroup = nullptr;
			backSorted->nextGroupSorted = nullptr;
		}
		else
		{
			bufferGroup = head;
			while (true)
			{
				if (!strcmp(bufferGroup->acGroup, acGroup))
					break;

				if (!bufferGroup->nextGroup)
				{
					back->nextGroup = new Group;
					back = back->nextGroup;
					back->nextGroup = nullptr;
					back->nextGroupSorted = nullptr;

					strcpy(back->acGroup, acGroup);

					break;
				}
				else
					bufferGroup = bufferGroup->nextGroup;
			}
		}
		if (!back->firstStudent)
		{
			back->firstStudent = new Student; // Создаём узел для нового студентав в новой группе
			back->lastStudent = back->firstStudent;

			back->topStudent = back->firstStudent; // Добавляем нового студента в качестве лучшего студента

			back->lastStudent->nextStudent = nullptr;
			t++;
		}
		else
		{
			back->lastStudent->nextStudent = new Student; // Создаём узел для нового студента в уже имеющейся группе
			back->lastStudent = back->lastStudent->nextStudent;
			back->lastStudent->nextStudent = nullptr;
		}
		std::cout << std::endl
				  << "Enter student's full name: ";
		std::cin.getline(back->lastStudent->acName, 100);

		strcpy(back->lastStudent->acGroup, back->acGroup);

		std::cout << std::endl
				  << "Enter student grades: ";
		for (int iI = 0; iI < 5; iI++)
		{
			std::cin >> back->lastStudent->aiGrades[iI];
			back->lastStudent->iSumOfGrades += (int)(*&back->lastStudent->aiGrades[iI]);
		}
		std::cout << std::endl
				  << "Enter the size of the student's grant: ";
		std::cin >> back->lastStudent->iGrant;
		back->lastStudent->dScore = (double)back->lastStudent->iSumOfGrades / back->lastStudent->iGrant;
		if (head->nextGroup && t != 0)
			sort_top(backSorted, back, headSorted, t);
		else if (back->topStudent->dScore < back->lastStudent->dScore)
		{
			back->topStudent = back->lastStudent;
			sort_top(backSorted, back, headSorted, t);
		}
		std::cout << "Student entered" << std::endl;
	}
}

void clear(Group *(&head), Group *(&back))
{
	Group *bufferGroup, *deletedBufferGroup;
	Student *bufferStudent, *deletedBufferStudent;
	bufferGroup = head;
	while (bufferGroup)
	{
		bufferStudent = bufferGroup->firstStudent;
		while (bufferStudent)
		{
			deletedBufferStudent = bufferStudent;
			bufferStudent = bufferStudent->nextStudent;
			delete deletedBufferStudent;
		}
		deletedBufferGroup = bufferGroup;
		bufferGroup->nextGroup;
		delete deletedBufferGroup;
	}
}

void task4() {

}

void task14() {

}

void menu()
{
	std::cout << CLEAR
			  << "Menu:" << std::endl
			  << "\t[ 1 ] - Console / file input" << std::endl
			  << "\t[ 2 ] - Console / file output" << std::endl
			  << "\t[ 3 ] - Editing data about students and groups of the stream" << std::endl
			  << "\t[ 4 ] - Adding new students" << std::endl
			  << std::endl
			  << "\t[ 6 ] - ( Task 4 )" << std::endl
			  << "\t[ 7 ] - ( Task 14 )" << std::endl
			  << std::endl
			  << "\t[ 0 ] - Exiting the program" << std::endl
			  << std::endl
			  << "Enter answer: ";
}

int main()
{
	Group *headGroup{ nullptr }, *backGroup{ nullptr }, *headGroupSorted{ nullptr }, *backGroupSorted{ nullptr };

	while(true)
	{
		menu();
		int iChoice;
		std::cin >> iChoice;
		switch (iChoice)
		{
			case 0:
				return 0;

			case 1:
			{
				std::cout << CLEAR
						  << "[ 1 ] - Console input" << std::endl
						  << "[ 2 ] - File input" << std::endl
						  << "[ 0 ] - Exit" << std::endl;
				iChoice = 0;
				std::cin >> iChoice;
				switch (iChoice)
				{
					case 1:
					{
						if (headGroup)
						{
							std::cout << std::endl
									  << "There is already a list of groups and students, do you want to rewrite it?" << std::endl
									  << "[ 1 ] - Yes" << std::endl
									  << "[ 0 ] - No" << std::endl;
							iChoice = 0;
							std::cin >> iChoice;
							if (iChoice == 0)
								break;
							else
							{
								clear(headGroup, backGroup);
								std::cout << "Everything deleted";
							}
						}
						groupAdd(headGroup, backGroup, headGroupSorted, backGroupSorted);
						break;
					}

					case 2:
					{
						if (headGroup)
						{
							std::cout << std::endl
									  << "There is already a list of groups and students, do you want to rewrite it?" << std::endl
									  << "[ 1 ] - Yes" << std::endl
									  << "[ 0 ] - No" << std::endl;
							iChoice = 0;
							std::cin >> iChoice;
							if (iChoice == 0)
								break;
							else
							{
								clear(headGroup, backGroup);
								std::cout << "Everything deleted";
							}
						}
						fileInput(headGroup, backGroup, headGroupSorted, backGroupSorted);
						break;
					}

					default:
						break;
				}
				continue;
			}

			case 2:
			{
				if (!headGroup)
				{
					std::cout << std::endl
							  << "No data entered";
					continue;
				}

				std::cout << CLEAR
						  << "[ 1 ] - Console input" << std::endl
						  << "[ 2 ] - File input" << std::endl
						  << "[ 0 ] - Exit" << std::endl;
				iChoice = 0;
				std::cin >> iChoice;
				switch (iChoice)
				{
					case 1:
					{
						output(headGroup, backGroup);
						break;
					}

					case 2:
					{
						fileOutput(headGroup, backGroup);
						break;
					}

                    default:
						break;
				}
				continue;
			}

			case 3:
			{
				if (!headGroup)
				{
					std::cout << std::endl
							  << "No data entered";
					continue;
				}

				formEdit(headGroup, backGroup, headGroupSorted, backGroupSorted);
				continue;
			}
			case 4:
			{
				if (!headGroup)
				{
					std::cout << std::endl
							  << "No data entered";
					continue;
				}

				groupAdd(headGroup, backGroup, headGroupSorted, backGroupSorted);
				continue;
			}

			case 6:
			{
				if (!headGroup)
				{
					std::cout << std::endl
							  << "No data entered";
					continue;
				}

				//TODO: task4(headGroup, backGroup);
				continue;
			}

			case 7:
			{
				if (!headGroup)
				{
					std::cout << std::endl
							  << "No data entered";
					continue;
				}

				//TODO: task14(headGroupSorted, backGroupSorted);
				continue;
			}

			default:
				continue;
		};
	};
	return 0;
}
