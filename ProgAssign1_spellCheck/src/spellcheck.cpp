#include <iostream>
#include "../include/hash.h"

bool isWordSep(char letter);

int main(int argc, char *argv[])
{

}

bool isWordSep(char letter)
{
    if (isalnum(letter) || letter == '-' || letter == '\'')
    {
        return false;
    }
    return true;
}