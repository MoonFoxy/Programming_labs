#include <iostream>

struct Tree
{
	int aiElement[3];
	int iLength;
	Tree *first;
	Tree *second;
	Tree *third;
	Tree *fourth;
	Tree *parent;
};

struct Level
{
	int iLevel;
	Tree *link;
	Level *nextLevel;
};

void sort(Tree *&buffer)
{
	switch(buffer->iLength)
	{
		case 2:
		{
			if (buffer->aiElement[0] > buffer->aiElement[1])
				std::swap(buffer->aiElement[0], buffer->aiElement[1]);
			return;
		}

		case 3:
		{
			if (buffer->aiElement[0] > buffer->aiElement[1])
				std::swap(buffer->aiElement[0], buffer->aiElement[1]);
			if (buffer->aiElement[0] > buffer->aiElement[2])
				std::swap(buffer->aiElement[0], buffer->aiElement[2]);
			if (buffer->aiElement[1] > buffer->aiElement[2])
				std::swap(buffer->aiElement[1], buffer->aiElement[2]);
			return;
		}

		default:
			return;
	}
}

void addNode(Tree *&buffer, int element)
{
	buffer->aiElement[buffer->iLength] = element;
	buffer->iLength++;
	sort(buffer);
};

Tree *split(Tree *buffer)
{
	if (buffer->iLength < 3)
		return buffer;

	Tree *x = new Tree;
	x->aiElement[0] = buffer->aiElement[0];
	x->first = buffer->first;
	x->second = buffer->second;
	x->third = nullptr;
	x->fourth = nullptr;
	x->parent = buffer->parent;
	x->iLength = 1;

	Tree *y = new Tree;
	y->aiElement[0] = buffer->aiElement[2];
	y->first = buffer->third;
	y->second = buffer->fourth;
	y->third = nullptr;
	y->fourth = nullptr;
	y->parent = buffer->parent;
	y->iLength = 1;

	if (x->first)
		x->first->parent = x;

	if (x->second)
		x->second->parent = x;

	if (y->first)
		y->first->parent = y;

	if (y->second)
		y->second->parent = y;

	if (buffer->parent)
	{
		addNode(buffer->parent, buffer->aiElement[1]);
		if (buffer->parent->first == buffer)
			buffer->parent->first = nullptr;
		else if (buffer->parent->second == buffer)
			buffer->parent->second = nullptr;
		else if (buffer->parent->third == buffer)
			buffer->parent->third = nullptr;

		if (buffer->parent->first == nullptr)
		{
			buffer->parent->first = x;
			buffer->parent->second = y;
			buffer->parent->third = buffer->parent->second;
			buffer->parent->fourth = buffer->parent->third;
		}
		else if (buffer->parent->second == nullptr)
		{
			buffer->parent->second = x;
			buffer->parent->third = y;
			buffer->parent->fourth = buffer->parent->third;
		}
		else
		{
			buffer->parent->third = x;
			buffer->parent->fourth = y;
		}
		Tree *temp = buffer->parent;
		delete buffer;
		return temp;
	}
	else
	{
		x->parent = buffer;
		y->parent = buffer;
		buffer->first = x;
		buffer->second = y;
		buffer->third = nullptr;
		buffer->fourth = nullptr;
		buffer->parent = nullptr;
		buffer->aiElement[0] = buffer->aiElement[1];
		buffer->iLength = 1;
		return buffer;
	}
};

Tree *insert(Tree *&ptr, int element)
{
	if (ptr == nullptr)
	{
		ptr = new Tree;
		ptr->aiElement[0] = element;
		ptr->iLength = 1;
		ptr->first = nullptr;
		ptr->second = nullptr;
		ptr->third = nullptr;
		ptr->fourth = nullptr;
		ptr->parent = nullptr;
	}
	else if ((ptr->first == nullptr) && (ptr->second == nullptr) && (ptr->third == nullptr))
		addNode(ptr, element);
	else if (element <= ptr->aiElement[0])
		insert(ptr->first, element);
	else if ((ptr->iLength == 1) && element >= ptr->aiElement[0] || (ptr->iLength == 2 && element < ptr->aiElement[1]))
		insert(ptr->second, element);
	else
		insert(ptr->third, element);
	return split(ptr);
};

void output(Level *&(buffer))
{
	if (buffer == nullptr)
		return;
	Level *temp, *back;
	temp = (back = buffer);
	temp->nextLevel = nullptr;
	while (temp)
	{
		if (temp->link && temp->link->first)
		{
			back->nextLevel = new Level;
			back->nextLevel->link = temp->link->first;
			back = back->nextLevel;
			back->iLevel = temp->iLevel + 1;
			back->nextLevel = nullptr;
		}
		if (temp->link && temp->link->second)
		{
			back->nextLevel = new Level;
			back = back->nextLevel;
			back->iLevel = temp->iLevel + 1;
			back->link = temp->link->second;
			back->nextLevel = nullptr;
		}
		if (temp->link && temp->link->third)
		{
			back->nextLevel = new Level;
			back = back->nextLevel;
			back->iLevel = temp->iLevel + 1;
			back->link = temp->link->third;
			back->nextLevel = nullptr;
		}
		temp = temp->nextLevel;
	}
	temp = buffer;
	int iLevel = 1;
	std::cout << "Level " << iLevel << ": ";
	while (temp)
	{
		if (temp->iLevel != iLevel)
		{
			iLevel++;
			std::cout << std::endl
				 	  << "Level " << iLevel << ": ";
		}

		if (temp->link)
		{
			for (int iI = 0; iI < temp->link->iLength; iI++)
			{
				std::cout << temp->link->aiElement[iI] << ' ';
			}
			if (temp->link->parent)
			{
				std::cout << "exits from \" ";
				for (int iI = 0; iI < temp->link->parent->iLength; iI++)
				{
					std::cout << temp->link->parent->aiElement[iI] << ' ';
				}
				std::cout << '\"';
			}
		}
		std::cout << ' ';
		temp = temp->nextLevel;
	}
	std::cout << std::endl;
	temp = buffer;
	Level *temp2;
	temp2 = buffer;
	do
	{
		temp2 = temp;
		temp = temp->nextLevel;
		delete temp2;
	} while (temp);
};

void deleteTree(Tree *buffer)
{
	if (buffer)
	{
		deleteTree(buffer->first);
		deleteTree(buffer->second);
		deleteTree(buffer->third);
		delete buffer;
	}
};

int main()
{
	Tree *tree{ nullptr };
	Level *level{ nullptr };
	int iAnswer = 0;
	std::cin >> iAnswer;
	while (iAnswer != 0)
	{
		insert(tree, iAnswer);
		level = new Level;
		level->link = tree;
		level->iLevel = 1;
		output(level);
		std::cin >> iAnswer;
		std::cout << std::endl;
	}

	deleteTree(tree);
}
