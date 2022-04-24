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

using namespace std;

// Файл для записи и чтения данных ( Полный путь до файла ) < Стандартное значение >
#define TEXT_FILE "./file.txt"

// Очистка консоли ( Коряво работает )
#define CLEAR "\x1B[2J\x1B[H"

ofstream fileOut;
ifstream fileIn;

struct Student	// Список студентов
{
	char acName[100];       // Имя Студента
	char acGroup[5] = " ";  // Номер группы студента
	int iGrant;            // Степендия студента
	int aiGrades[5];        // Оценки студента
	int iSumOfGrades = 0;	// Сумма баллов студента
	double dScore;          // Значение показателя «средний балл» / «объем стипендии» TODO:

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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getchar();
}

/**
 * Заголовок программы
 */
void title()
{
	cout << CLEAR
			  << "\t\t\"Coursework on PROGRAMMING\" No. 2" << endl
			  << "\tAuthor: Ilya Balakirev aka. MoonFoxy" << endl
			  << "\tGitHub: https://github.com/MoonFoxy/ ( Plz don't )" << endl
			  << "\tSecond course" << endl
			  << "\tFaculty of Computer Technology and Informatics" << endl
			  << "\tManagement in technical systems" << endl
			  << "\tGroup: 0391" << endl
			  << endl;

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
			cout << "Name:" << buffer->lastStudent->acName << endl
					  << "Group number:" << buffer->lastStudent->acGroup << endl
					  << "Evaluations:";

			for (int iI = 0; iI < 5; iI++)
				cout << buffer->lastStudent->aiGrades[iI] << "  "
						  << endl
						  << "Grants size:" << buffer->lastStudent->iGrant << endl;

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
	string name = TEXT_FILE;

	fileIn.open(name);
	fileIn >> acGroup;
	{
		while (!strcmp(acGroup, "0\0"))
		{
			int iKey = 0;
			if (head == nullptr)
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
					if (buffer->nextGroup == nullptr)
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
			if (back->firstStudent == nullptr)
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
			if (head->nextGroup != nullptr && iKey != 0)
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
	string name = TEXT_FILE;
	Group *buffer{ nullptr };
	buffer = head;
	cout << "Enter the file name to save: " << endl;
	cin >> name;
	fileOut.open(name);
	{
		while (buffer)
		{
			buffer->lastStudent = buffer->firstStudent;
			while (buffer->lastStudent)
			{
				fileOut << buffer->lastStudent->acName << endl;
				fileOut << buffer->lastStudent->acGroup << endl;
				for (int iI = 0; iI < 5; iI++)
					fileOut << buffer->lastStudent->aiGrades[iI] << "  ";
				fileOut << endl
					<< buffer->lastStudent->iGrant << endl;
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

	cout << "Enter the group" << endl;
	cin >> acBufferGroup;
	while (bufferGroup)
	{
		if (strcmp(bufferGroup->acGroup, acBufferGroup))
			break;
		else
		{
			if (bufferGroup->nextGroup == nullptr)
			{
				cout << "You entered a group that is not listed." << endl;
				return;
			}
		}
		bufferGroup = bufferGroup->nextGroup;
	}
	cout << "Enter a name to delete." << endl;
	cin.getline(acBufferStudentName, 100);
	cin.getline(acBufferStudentName, 100);
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
				if (bufferStudent->nextStudent->nextStudent == nullptr)
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
	cout << "Enter a name to edit:" << endl;
	cin.getline(acBufferStudentName, 100);
	cin.getline(acBufferStudentName, 100);
	while (bufferGroup)
	{
		bufferStudent = bufferGroup->firstStudent;
		while (bufferStudent)
		{
			if (strcmp(acBufferStudentName, bufferStudent->acName) == 0)
			{
				cout << "What do you want to change?" << endl
						  << "[ 1 ] - Student name" << endl
						  << "[ 2 ] - Student grades" << endl
						  << "[ 3 ] - Student grant" << endl;
				int iChoice = 0;
				cin >> iChoice;
				switch (iChoice)
				{
					case 1:
					{
						cout << "Enter the new student name:" << endl;
						cin.getline(bufferStudent->acName, 100);
						cin.getline(bufferStudent->acName, 100);
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
						cout << "New student grades:" << endl;
						bufferStudent->dScore = 0;
						for (int iI = 0; iI < 5; iI++)
						{
							cin >> bufferStudent->aiGrades[iI];
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
						cout << "Enter the new student grant:" << endl;
						cin >> bufferStudent->iGrant;
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
		cout << "Enter the group number or '0' to exit the menu:" << endl;
		cin >> acGroup;
		int key = 0;

		if (!strcmp(acGroup, "0\0"))
		{
			cout << endl
					  << "Data entry is complete." << endl;
			break;
		}
		if (head == nullptr)
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

				if (bufferGroup->nextGroup == nullptr)
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
		if (back->firstStudent == nullptr)
		{
			back->firstStudent = new Student; // Создаём узел для нового студентав в новой группе
			back->lastStudent = back->firstStudent;

			back->topStudent = back->firstStudent; // Добавляем нового студента в качестве лучшего студента

			back->lastStudent->nextStudent = nullptr;
			key++;
		}
		else
		{
			back->lastStudent->nextStudent = new Student; // Создаём узел для нового студента в уже имеющейся группе
			back->lastStudent = back->lastStudent->nextStudent;
			back->lastStudent->nextStudent = nullptr;
		}
		cout << endl
				  << "Enter student's full name: ";
		cin.getline(back->lastStudent->acName, 100);
		cin.getline(back->lastStudent->acName, 100);

		strcpy(back->lastStudent->acGroup, back->acGroup);

		cout << endl
				  << "Enter student grades: ";
		for (int iI = 0; iI < 5; iI++)
		{
			cin >> back->lastStudent->aiGrades[iI];
			back->lastStudent->iSumOfGrades += (int)(*&back->lastStudent->aiGrades[iI]);
		}
		cout << endl
				  << "Enter the size of the student's grant: ";
		cin >> back->lastStudent->iGrant;
		back->lastStudent->dScore = (double)back->lastStudent->iSumOfGrades / back->lastStudent->iGrant;
		if (head->nextGroup && key != 0)
			sort_top(backSorted, back, headSorted, key);
		else if (back->topStudent->dScore < back->lastStudent->dScore)
		{
			back->topStudent = back->lastStudent;
			sort_top(backSorted, back, headSorted, key);
		}
		cout << "Student entered" << endl;
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

/**
 * [ 4 ] Вывести в порядке возрастания номера групп, в которых соотношение «суммарный объем стипендии» / «общее количество баллов» превышает заданное значение
 */
void task4(Group *(&groupSorted))
{
	Group *bufferGroup = groupSorted;
	Student *bufferStudent = { nullptr };
	cout << "Enter value: ";
	int iValue = 0;
	cin >> iValue;
	cout << "Conclusion in ascending order of the number of groups in which the ratio of \"total grants\" / \"total number of points\" exceeds " << iValue << endl;

	for (int iI = 0; bufferGroup != nullptr; iI++)
	{
		int iJ = 1;
		int iGrantTotal = 0;
		float iGradesTotal = 0;
		bufferStudent = bufferGroup->firstStudent;
		for (; bufferStudent != nullptr; iJ++)
		{
			iGradesTotal += (bufferStudent->iSumOfGrades / float(5));
			iGrantTotal += bufferStudent->iGrant;
			bufferStudent = bufferStudent->nextStudent;
		}
		iGradesTotal /= float(iJ);

		if (iGrantTotal / float(iGradesTotal) > float(0))
		{
			cout << "[ " << iI << " ] Group " << bufferGroup->acGroup << ": " << iGrantTotal / float(iGradesTotal) << endl;
		}
		bufferGroup = bufferGroup->nextGroupSorted;
	}
}

/**
 * [ 19 ] Вывести в алфавитном порядке список той группы, в которой средний балл является максимальным по потоку
 */
void task19(Group *(&groupSorted))
{
	Group *bufferGroup = groupSorted, *maxBufferGroup = groupSorted->nextGroupSorted;
	Student *bufferStudent = { nullptr }, *maxBufferStudent = { nullptr };

	float fMaxGradesAverage = 0;
	int iCount = 1;
	maxBufferGroup->firstStudent;
	for (; maxBufferStudent != nullptr; iCount++)
	{
		fMaxGradesAverage += (maxBufferStudent->iSumOfGrades / float(5));
		maxBufferStudent = maxBufferStudent->nextStudent;
	}
	fMaxGradesAverage /= iCount;

	while (bufferGroup)
	{
		float fGradesAverage = 0;
		iCount = 1;
		bufferStudent = bufferGroup->firstStudent;
		for (; bufferStudent != nullptr; iCount++)
		{
			fMaxGradesAverage += (bufferStudent->iSumOfGrades / float(5));
			bufferStudent = bufferStudent->nextStudent;
		}
		fGradesAverage /= iCount;

		if (fGradesAverage > fMaxGradesAverage)
		{
			maxBufferGroup = bufferGroup;
			fMaxGradesAverage = fGradesAverage;
		}

		bufferGroup = bufferGroup->nextGroupSorted;
	}

	maxBufferStudent = maxBufferGroup->firstStudent;
	cout << "Display in alphabetical order a list of the group with the maximum average score for the stream" << endl;

	if (maxBufferGroup != nullptr)
		cout << "Group " << maxBufferGroup->acGroup << "\tAverage score: " << fMaxGradesAverage << endl << endl;

	for (int iI = 1; maxBufferStudent != nullptr; iI++)
	{
		cout << "[ " << iI << " ] - " << maxBufferStudent->acName << endl
			 << "\tGrades: ";
		for (int iJ = 0; iJ < 5; iJ++)
			cout << maxBufferStudent->aiGrades[iJ] << ' ';
		cout << endl << endl;
		maxBufferStudent = maxBufferStudent->nextStudent;
	}
}

void menu()
{
	cout << CLEAR
			  << "Menu:" << endl
			  << "\t[ 1 ] - Console / file input" << endl
			  << "\t[ 2 ] - Console / file output" << endl
			  << "\t[ 3 ] - Editing data about students and groups of the stream" << endl
			  << "\t[ 4 ] - Adding new students" << endl
			  << endl
			  << "\t[ 6 ] - ( Task 4 )" << endl
			  << "\t[ 7 ] - ( Task 14 )" << endl
			  << endl
			  << "\t[ 0 ] - Exiting the program" << endl
			  << endl
			  << "Enter answer: ";
}

int main()
{
	Group *headGroup{ nullptr }, *backGroup{ nullptr }, *headGroupSorted{ nullptr }, *backGroupSorted{ nullptr };

	while (true)
	{
		menu();
		int iChoice;
		cin >> iChoice;
		switch (iChoice)
		{
			case 0:
				return 0;

			case 1:
			{
				cout << CLEAR
						  << "[ 1 ] - Console input" << endl
						  << "[ 2 ] - File input" << endl
						  << "[ 0 ] - Exit" << endl;
				iChoice = 0;
				cin >> iChoice;
				switch (iChoice)
				{
					case 1:
					{
						if (headGroup != nullptr)
						{
							cout << endl
									  << "There is already a list of groups and students, do you want to rewrite it?" << endl
									  << "[ 1 ] - Yes" << endl
									  << "[ 0 ] - No" << endl;
							iChoice = 0;
							cin >> iChoice;
							if (iChoice == 0)
								break;
							else
							{
								clear(headGroup, backGroup);
								cout << "Everything deleted";
							}
						}
						groupAdd(headGroup, backGroup, headGroupSorted, backGroupSorted);
						break;
					}

					case 2:
					{
						if (headGroup != nullptr)
						{
							cout << endl
									  << "There is already a list of groups and students, do you want to rewrite it?" << endl
									  << "[ 1 ] - Yes" << endl
									  << "[ 0 ] - No" << endl;
							iChoice = 0;
							cin >> iChoice;
							if (iChoice == 0)
								break;
							else
							{
								clear(headGroup, backGroup);
								cout << "Everything deleted";
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
				if (headGroup == nullptr)
				{
					cout << endl
							  << "No data entered";
					continue;
				}

				cout << CLEAR
						  << "[ 1 ] - Console input" << endl
						  << "[ 2 ] - File input" << endl
						  << "[ 0 ] - Exit" << endl;
				iChoice = 0;
				cin >> iChoice;
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
				if (headGroup == nullptr)
				{
					cout << endl
							  << "No data entered";
					continue;
				}

				formEdit(headGroup, backGroup, headGroupSorted, backGroupSorted);
				continue;
			}
			case 4:
			{
				if (headGroup == nullptr)
				{
					cout << endl
							  << "No data entered";
					continue;
				}

				groupAdd(headGroup, backGroup, headGroupSorted, backGroupSorted);
				continue;
			}

			case 6:
			{
				if (headGroup == nullptr)
				{
					cout << endl
							  << "No data entered";
					continue;
				}

				task4(headGroupSorted);
				continue;
			}

			case 7:
			{
				if (headGroup == nullptr)
				{
					cout << endl
							  << "No data entered";
					continue;
				}

				task19(headGroupSorted);
				continue;
			}

			default:
				continue;
		};
	};
	return 0;
}
