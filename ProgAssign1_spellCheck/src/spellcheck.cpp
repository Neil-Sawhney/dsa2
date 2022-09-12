#include <fstream>
#include "../include/spellcheck.h"

bool isWordSep(char letter)
{
    if (isalnum(letter) || letter == '-' || letter == '\'')
    {
        return false;
    }
    return true;
}

invalidReason wordValidity(std::string word)
{
    if(word.length() >= 20)
        return TOO_LONG;

    for (int i = 0; i < word.length(); i++)
    {
        if (!isalnum(word[i]) && word[i] != '-' && word[i] != '\'')
        {
            return BAD_CHAR;
        }
    }
    return VALID;
}

void loadDictionary(hashTable &dictionary, std::string filename)
{
    std::ifstream file(filename);
    std::string word;
    while (file >> word)
    {
        if (wordValidity(word) == VALID)
        {
            // convert word to lowercase
            for (int i = 0; i < word.length(); i++)
            {
                word[i] = tolower(word[i]);
            }
            dictionary.insert(word);
        }
    }
}
