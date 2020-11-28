#include <iostream>
#include <cstring>

#define TEXT_SIZE 80
#define KEY_SIZE 10

/*
  С клавиатуры вводится произвольная строка длиной не более 80 символов. Затем вводится ключ - подстрока, длиной не более 10 символов.

  Необходимо:
    1). Определить количество вхождений ключа в строку (с учётом возможного наложения расположения одного ключа на другой).
    2). Вставить перед и после вхождения подстроки символы кавычки " ".
    3). Определить символ наиболее часто встречающийся в строке.
    4). Вывести на экран все слова, содержащиеся в строке (возможные разделители (- , . ! ? ; <пробел>))
*/

int main()
{
    char text[TEXT_SIZE] = { "" };
    char key[KEY_SIZE] = { "" };

    std::cout << "Enter text: ";
    std::cin.getline(text, TEXT_SIZE);

    std::cout << "Enter key: ";
    std::cin.getline(key, KEY_SIZE);

    size_t textLen = strlen(text);
    size_t keyLen = strlen(key);

    int matchCount = 0;
    char keyReplaced[TEXT_SIZE * 3] = { "" };
    char mark[KEY_SIZE + 2] = { "" };

    std::strcat(mark, "\"");
    std::strcat(mark, key);
    std::strcat(mark, "\"");
    for (int i = 0, j = 0; text[i];)
    {
        if (text[i] == key[0])
        {
            if (std::string(text).substr(i, keyLen) == key)
            {
                std::strcat(keyReplaced, mark);
                matchCount++;
                i += keyLen;
                j += keyLen + 2;
                continue;
            }
        }
        keyReplaced[j] = text[i];
        i++;
        j++;
    }

    std::cout << "(1): " << key << " - " << matchCount << "\n";
    std::cout << "(2): " << keyReplaced << "\n";

    int maxCount = 0;
    char maxChar;
    for (int i = 0; i < textLen; i++)
    {
        int count = 0;
        for (int j = i; j < textLen; j++)
        {
            if (text[i] == text[j]) count++;
        }
        if (count > maxCount)
        {
            maxCount = count;
            maxChar = text[i];
        }
    }

    std::cout << "(3): " << maxChar << " - " << maxCount << "\n";
    std::cout << "(4):";

    char charts[9] = " ,.-!?:;";
    char* delim = strtok(text, charts);
    while (delim)
    {
        std::cout << "\t" << delim << ",\n";
        delim = strtok(NULL, charts);
    }

    system("pause");
    return 0;
}
