#include <iostream>
#include <fstream>
#include <time.h>
#include "../include/spellcheck.h"

bool isWordSep(char letter)
{
    if (isalnum(letter) || letter == '-' || letter == '\'')
    {
        return false;
    }
    return true;
}

wordType chkWord(std::string word)
{
    if(word.length() > 20)
        return TOO_LONG;

    if(word.length() == 0)
        return EMPTY;

    bool containsNumbers = false;
    for (int i = 0; i < word.length(); i++)
    {
        char currChar = word[i];

        if(isdigit(currChar))
            containsNumbers = true;

        if (!isalnum(currChar) && currChar != '-' && currChar != '\'')
        {
            return BAD_CHAR;
        }
    }

    if(containsNumbers)
        return CONTAINS_NUMBERS;
    return VALID;
}

void checkAndPrint(hashTable &dictionary ,std::string word, int lineNum, std::ofstream &output)
{
    if (chkWord(word) == TOO_LONG)
    {
        output << "Long word at line " << lineNum << ", starts: " << word.substr(0, 20) << std::endl;
    }

    else if (chkWord(word) == VALID)
    {
        if (!dictionary.contains(word))
        {
            output << "Unknown word at line " << lineNum << ": " << word << std::endl;
        }
    }

}

void loadDictionary(hashTable &dictionary, std::string &filename)
{
    // start the clock
    clock_t start = clock();

    std::ifstream file(filename);
    std::string word;
    while (file >> word)
    {
        if (chkWord(word) == VALID || chkWord(word) == CONTAINS_NUMBERS)
        {
            // convert word to lowercase
            for (int i = 0; i < word.length(); i++)
            {
                word[i] = tolower(word[i]);
            }
            dictionary.insert(word);
        }
    }

    // stop the clock
    clock_t end = clock();
    double cpuTime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPU time to load dictionary (in seconds): " << cpuTime << std::endl;
}

void spellcheck(hashTable &dictionary, std::string &spellcheckFile, std::string &outputFile)
{
    // start the clock
    clock_t start = clock();

    std::ofstream output(outputFile);

    std::ifstream file(spellcheckFile);

    int lineNum = 1;
    std::string line;
    std::string word;

    std::getline(file, line);
    // loop until end of file
    while(!file.eof())
    {
        // skip if its a blank line
        if(line.length() == 0)
        {
            word = "";

            lineNum++;
            std::getline(file, line);
            continue;
        }

        // loop through every letter in the line
        for (int i = 0; i < line.length(); i++)
        {
            // convert letter to lowercase
            line[i] = tolower(line[i]);


            if (isWordSep(line[i]))
            {
                checkAndPrint(dictionary, word, lineNum, output);
                word = "";
            }
            
            else
                word += line[i];
        }

        checkAndPrint(dictionary, word, lineNum, output);
        word = "";

        lineNum++;
        std::getline(file, line);
    }

    // stop the clock
    clock_t end = clock();
    double cpuTime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPU time to spellcheck file (in seconds): " << cpuTime << std::endl;
}
