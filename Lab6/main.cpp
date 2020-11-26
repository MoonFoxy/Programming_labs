#include <iostream>
#include <cstring>

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
    const int textSize = 80;
    const int keySize = 10;

    char text[textSize] = { "" };
    char key[keySize] = { "" };

    std::cout << "Enter text: ";
    std::cin.getline(text, textSize);

    std::cout << "Enter key: ";
    std::cin.getline(key, keySize);

    size_t textLen = strlen(text);
    size_t keyLen = strlen(key);

    int matchCount = 0;
    std::string keyReplaced;
    for (int i = 0; text[i];)
    {
        if (text[i] == key[0])
        {
            if (std::string(text).substr(i, keyLen) == key)
            {
                keyReplaced += "\"";
                keyReplaced += key;
                keyReplaced += "\"";
                matchCount++;
                i += keyLen;
                continue;
            }
        }
        keyReplaced += text[i];
        i++;
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
