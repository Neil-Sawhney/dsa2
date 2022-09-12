#include <iostream>
#include "../include/spellcheck.h"

int main()
{

    // prompt the user for the dictionary file
    std::string dictionaryFile;
    std::cout << "Enter the dictionary file: ";
    std::cin >> dictionaryFile;

    std::string spellcheckFile;
    std::cout << "Enter the file to be spell checked: ";
    std::cin >> spellcheckFile;

    std::string outputFile;
    std::cout << "Enter the output file: ";
    std::cin >> outputFile;

    hashTable dictionary(50000);
    loadDictionary(dictionary, dictionaryFile);
    spellcheck(dictionary, spellcheckFile, outputFile);

}
