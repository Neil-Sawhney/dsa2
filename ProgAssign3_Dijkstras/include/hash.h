#pragma once
#include <vector>
#include <string>

class hashTable
{

public:
  // The constructor initializes the hash table.
  // Uses getPrime to choose a prime number at least as large as
  // the specified size for the initial size of the hash table.
  hashTable(int size = 0);

  // Insert the specified key into the hash table.
  // If an optional pointer is provided,
  // associate that pointer with the key.
  // Returns entryType::SUCCESS if the key is inserted.
  // Returns entryType::KEY_EXISTS if the key is already in the hash table.
  // Returns entryType::REHASH_FAIL if the key is not inserted because the rehash fails.
  int insert(const std::string &key, void *pv = nullptr);
  enum entryType
  {
    SUCCESS,
    KEY_EXISTS,
    REHASH_FAIL
  };

  // Check if the specified key is in the hash table.
  // If so, return true; otherwise, return false.
  bool contains(const std::string &key);

  // Get the pointer associated with the specified key.
  // If the key does not exist in the hash table, return nullptr.
  // If an optional pointer to a bool is provided,
  // set the bool to true if the key is in the hash table,
  // and set the bool to false otherwise.
  //  mapping.setPointer(data[posCur].id, &data[posCur]);
  void *getPointer(const std::string &key, bool *b = nullptr);

  // Set the pointer associated with the specified key.
  // Returns 0 on success,
  // 1 if the key does not exist in the hash table.
  //  node *pn = static_cast<node *> (mapping.getPointer(id, &b));
  int setPointer(const std::string &key, void *pv);

  // Delete the item with the specified key.
  // Returns true on success,
  // false if the specified key is not in the hash table.
  bool remove(const std::string &key);

private:
  // Each item in the hash table contains:
  // key - a string used as a key.
  // isOccupied - if false, this entry is empty,
  //              and the other fields are meaningless.
  // isDeleted - if true, this item has been lazily deleted.
  // pv - a pointer related to the key;
  //      nullptr if no pointer was provided to insert.
  class hashItem
  {
  public:
    std::string key{""};
    bool isOccupied{false};
    bool isDeleted{false};
    void *pv{nullptr};

    hashItem() = default;
  };

  int capacity; // The current capacity of the hash table.
  int filled;   // Number of occupied items in the table.

  std::vector<hashItem> data; // The actual entries are here.

  // The hash function.
  int hash(const std::string &key);

  // Search for an item with the specified key.
  // Return the position if found, -1 otherwise.
  int findPos(const std::string &key);

  // The rehash function; makes the hash table bigger.
  // Returns true on success, false if memory allocation fails.
  bool rehash();

  // Return a prime number at least as large as size.
  // Uses a precomputed sequence of selected prime numbers.
  static unsigned int getPrime(int size);
};
