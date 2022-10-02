#pragma once
#include <vector>
#include <string>
#include <hash.h>

class heap
{
private:
    // Each node in the heap contains:
    // id - a string used as a key.
    // key - a number used to determine the priority of the node.
    // *pData - a pointer to the actual data.
    class node
    {
    public:
        std::string id; // The id of this node
        int key;        // The key of this node
        void *pData;    // A pointer to the actual data
    };

    int m_capacity; // The max number of nodes in the heap
    int m_filled;   // Number of occupied nodes in the heap

    // The declarations of my data vector and hash table pointer
    std::vector<node> data; // The actual binary heap
    hashTable mapping;      // maps ids to node pointer

    // posCur is the current position in the heap
    void percolateUp(int posCur);

    // posCur is the current position in the heap
    void percolateDown(int posCur);

    // get the index of a node in the heap
    int getPos(node *pn);

public:
    enum returnValues
    {
        SUCCESS = 0,
        ID_DOESNT_EXIST = 1,
        ID_ALREADY_EXISTS = 2,
        HEAP_EMPTY = 1,
        HEAP_FULL = 1,
    };

    // The constructor
    heap(int capacity);

    //TODO: REMOVE THESE, FOR DEBUGGING ONLY
    void debugStuff();
    void printHeap();


    // insert - Inserts a new node into the binary heap
    //
    // Inserts a node with the specified id string, key,
    // and optionally a pointer.  They key is used to
    // determine the final position of the new node.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is already filled to capacity
    //   2 if a node with the given id already exists (but the heap
    //     is not filled to capacity)
    //
    int insert(const std::string &id, int key, void *pv = nullptr);

    // setKey - set the key of the specified node to the specified value
    //
    // I have decided that the class should provide this member function
    // instead of two separate increaseKey and decreaseKey functions.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int setKey(const std::string &id, int key);

    //             and delete that node from the binary heap
    //int
    // If pId is supplied (i.e., it is not nullptr), write to that address
    // the id of the node being deleted. If pKey is supplied, write to
    // that address the key of the node being deleted. If ppData is
    // supplied, write to that address the associated void pointer.
    //
    // Filling in ppData in deleteMin:
    // *(static_cast<void **> (ppData)) = data[1].pData;
    //
    // Returns:
    //   0 on success
    //   1 if the heap is empty
    //
    int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

    // remove - delete the node with the specified id from the binary heap
    //
    // If pKey is supplied, write to that address the key of the node
    // being deleted. If ppData is supplied, write to that address the
    // associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);
};

