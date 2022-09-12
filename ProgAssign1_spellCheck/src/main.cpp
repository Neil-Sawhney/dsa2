#include <iostream>
#include "../include/spellcheck.h"

int main()
{
    // prompt the user for the dictionary file
    std::string dictionaryFile;
    std::cout << "Enter the dictionary file: ";
    std::cin >> dictionaryFile;

    hashTable dictionary(50000);
    loadDictionary(dictionary, dictionaryFile);

}
