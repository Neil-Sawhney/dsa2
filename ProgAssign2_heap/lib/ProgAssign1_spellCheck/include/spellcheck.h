#pragma once
#include "../include/hash.h"

// returns true if the passed in letter is a word seperator
bool isWordSep(char letter);

// return VALID if the word is valid
// return CONTAIN_NUMBERS if the word is valid but contains numbers
// return TOO_LONG if the word is >= 20 characters
// return BAD_CHAR if the word contains a non-alphanumeric character
// return EMPTY if the word is empty
enum wordType {VALID, CONTAINS_NUMBERS, TOO_LONG, BAD_CHAR, EMPTY};
wordType chkWord(std::string word);

// loads the dictionary into the hash table
// converts all words to lowercase
// prints the cpu time to the standard output
void loadDictionary(hashTable &dictionary, std::string &filename);

// prints to the output file any unrecognized words along with their line number
// If a word is too long, indicate that, print the first 20 characters and the line number
// The first line in the document is line 1
// Ignores any words that contain numbers
// prints the cpu time to the standard output
void spellcheck(hashTable &dictionary, std::string &spellcheckFile, std::string &outputFile);


// checks if the word is valid, and if its too long, and prints the appropriate message
void checkAndPrint(hashTable &dictionary ,std::string word, int lineNum, std::ofstream &output);