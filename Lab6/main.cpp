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
    char acText[TEXT_SIZE] = { "" };
    char acKey[KEY_SIZE] = { "" };

    std::cout << "Enter text: ";
    std::cin.getline(acText, TEXT_SIZE);

    std::cout << "Enter key: ";
    std::cin.getline(acKey, KEY_SIZE);

    size_t iTextLen = strlen(acText);
    size_t iKeyLen = strlen(acKey);

    int iMatchCount = 0;
    char acKeyReplaced[TEXT_SIZE * 3] = { "" };
    char acMark[KEY_SIZE + 2] = { "" };

    std::strcat(acMark, "\"");
    std::strcat(acMark, acKey);
    std::strcat(acMark, "\"");
    for (int iI = 0, iJ = 0; acText[iI];)
    {
        if (acText[iI] == acKey[0])
        {
            if (std::string(acText).substr(iI, iKeyLen) == acKey)
            {
                std::strcat(acKeyReplaced, acMark);
                iMatchCount++;
                iI += iKeyLen;
                iJ += iKeyLen + 2;
                continue;
            }
        }
        acKeyReplaced[iJ] = acText[iI];
        iI++;
        iJ++;
    }

    std::cout << "(1): " << acKey << " - " << iMatchCount << "\n";
    std::cout << "(2): " << acKeyReplaced << "\n";

    int iMaxCount = 0;
    char cMaxChar;
    for (int iI = 0; iI < iTextLen; iI++)
    {
        int count = 0;
        for (int iJ = iI; iJ < iTextLen; iJ++)
        {
            if (acText[iI] == acText[iJ]) count++;
        }
        if (count > iMaxCount)
        {
            iMaxCount = count;
            cMaxChar = acText[iI];
        }
    }

    std::cout << "(3): " << cMaxChar << " - " << iMaxCount << "\n";
    std::cout << "(4):";

    char acCharts[9] = " ,.-!?:;";
    char* pcNextToken = NULL;
    char* pcToken = strtok_r(acText, acCharts, &pcNextToken);
    while (pcToken != NULL)
    {
        std::cout << "\t" << pcToken << ",\n";
        pcToken = strtok_r(NULL, acCharts, &pcNextToken);
    }

    return 0;
}
