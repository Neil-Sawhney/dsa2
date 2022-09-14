#include <stdlib.h>
#include <iostream>
#include <vector>

#include "../include/hash.h"

hashTable::hashTable(int size)
{
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);

}

int hashTable::insert(const std::string &key, void *pv)
{

    // check if we should rehash 
    if (filled >= capacity/2)
    {
        if (!rehash())
            return REHASH_FAIL;
    }

    int index = hash(key);
    int i = index;
    int j = 0;
    while (data[i].isOccupied)
    {
        // if the key is already in the hash table
        if (data[i].key == key)
        {
            // check to make sure it's not deleted
            if (data[i].isDeleted)
            {
                // if it is deleted, undelete it
                data[i].isDeleted = false;
                return SUCCESS;
            }
            
            // if it's not deleted, return KEY_EXISTS
            return KEY_EXISTS;
        }

        // if the key is not in the location we are looking in, find the next open spot
        // using linear probing where p(x) = x
        i = (index + j) % capacity;
        j++;
    }

    // if the key is not in the hash table, and we're at an open spot, insert it
    data[i].key = key;
    data[i].isOccupied = true;
    data[i].isDeleted = false;
    data[i].pv = pv;
    filled++;

    return SUCCESS;
}

bool hashTable::contains(const std::string &key)
{
    int index = hash(key);
    int i = index;
    int j = 0;
    while (data[i].isOccupied)
    {
        // if the key is in the hash table
        if (data[i].key == key)
        {
            // check to make sure it's not deleted
            if (data[i].isDeleted)
            {
                // if it is deleted, return false
                return false;
            }
            
            // if it's not deleted, return true
            return true;
        }

        // if the key is not in the location we are looking in, find the next open spot
        // using linear probing where p(x) = x
        i = (index + j) % capacity;
        j++;
    }

    // if we hit a blank spot, the key is not in the hash table, return false
    return false;
}

int hashTable::hash(const std::string &key)
{
    unsigned int hashVal = 0;

    for (char ch : key)
        hashVal = 37 * hashVal + ch;

    return hashVal % capacity;
}

int hashTable::findPos(const std::string &key)
{
    int index = hash(key);
    int i = index;
    int j = 0;
    while (data[i].isOccupied)
    {
        // if the key is in the hash table
        if (data[i].key == key)
        {
            // check to make sure it's not deleted
            if (data[i].isDeleted)
            {
                // if it is deleted, return -1
                return -1;
            }
            
            // if it's not deleted, return the index
            return i;
        }

        // if the key is not in the location we are looking in, find the next open spot
        // using linear probing where p(x) = x
        i = (index + j) % capacity;
        j++;
    }

    // if we hit a blank spot, the key is not in the hash table, return -1
    return -1;
}

bool hashTable::rehash()
{
    try
    {
        int oldCapacity = capacity;
        std::vector<hashItem> oldData = data;

        capacity = getPrime(capacity);
        data.resize(capacity);

        // reinitialize the new hash table
        for (int i = 0; i < capacity; i++)
        {
            data[i].isOccupied = false;
        }

        // insert all the old data into the new hash table
        for (int i = 0; i < oldCapacity; i++)
        {
            if (oldData[i].isOccupied && !oldData[i].isDeleted)
            {
                // insert the key into the new hash table
                insert(oldData[i].key);
            }
        }

        return true;
    }
    catch(std::bad_alloc&)
    {
        std::cerr << "Error: unable to allocate memory for new hash table" << std::endl;
    }
    return false;
    
}

unsigned int hashTable::getPrime(int size)
{
    int primes[] = { 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741 };
    for (int i = 0; i < 26; i++)
    {
        if (primes[i] > size)
        {
            return primes[i];
        }
    }
    return primes[25];
}