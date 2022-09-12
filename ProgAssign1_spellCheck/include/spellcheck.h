#pragma once

#include "../include/hash.h"
// returns true if the passed in letter is a word seperator
bool isWordSep(char letter);

// return TOO_LONG if the word is >= 20 characters
// return BAD_CHAR if the word contains a non-alphanumeric character
// return VALID if the word is valid
enum invalidReason {VALID, TOO_LONG, BAD_CHAR};
invalidReason wordValidity(std::string word);

// loads the dictionary into the hash table
// converts all words to lowercase
void loadDictionary(hashTable &dictionary, std::string filename);

