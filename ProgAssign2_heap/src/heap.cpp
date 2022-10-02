#include <heap.h>
#include <iostream>
#include <vector> //TODO: remove this
#include <algorithm> //TODO: remove this
#include <cmath> //TODO: remove this

void heap::printHeap()
{
    //print the heap so that it looks like a binary tree
    int level = 0;
    int levelSize = 1;
    int levelCount = 0;

    int numLevels = std::log2(m_filled) + 1;
    for (int i = 1; i <= m_filled; i++)
    {

        if(!mapping.contains(data[i].id))
        {
            // the data is in the heap, but it's not in the hash table
            throw "THIS IS BREAKING HERE";
        }
        // print appropriate beginning tabs where the first level has the most tabs and the last level has none
        if(levelCount == 0)
        {
            for (int j = 0; j < std::pow(2,numLevels - (level+1)); j++)
            {
                std::cout << "\t";
            }
        }
        std::cout << data[i].id << ": " << data[i].key;
        // print appropriate intermediate tabs
        if (levelCount < levelSize - 1)
        {
            for (int j = 0; j < std::pow(2,numLevels - (level+1)); j++)
            {
                // if we are in the middle
                if( levelCount == levelSize/2 -1)
                {
                    for (int j = 0; j < std::pow(2,numLevels - 1); j++)
                    {
                        std::cout << "\t";
                    }
                    break;
                }
                else
                {
                    std::cout << "\t";
                }
            }
        }
        levelCount++;
        if (levelCount == levelSize)
        {
            std::cout << std::endl;
            level++;
            levelSize = std::pow(2, level);
            levelCount = 0;
        }
    }
    std::cout << std::endl;

}

//TODO: COMMENT THIS OUT, FOR DEBUGGING ONLY
void heap::debugStuff()
{
    std::cout << "Heap: " << std::endl;
    printHeap();


    std::cout << "\nHash Table: " << std::endl;

    int mapping_filled = 0;

    // loops through the hash table
    // make sure nothing in the hash table is pointing to something that isn't in the heap
    for (int i = -10; i <= 10; i++)
    {
        std::string id = "id" + std::to_string(i);
        if (mapping.contains(id)) 
        {
            int key = static_cast<node*>(mapping.getPointer(id))->key;

            std::cout << "id" << i << ": " << key << std::endl;

            mapping_filled++;
           }

        node *node_ptr = static_cast<node *>(mapping.getPointer(id));
        int position = getPos(node_ptr);

        if(position > m_filled)
        {
            throw "THIS IS BREAKING HERE";
        }
        
    }

    if(mapping_filled != m_filled)
    {
        throw "mapping_filled != m_filled";
    }

    // be a crazy person and delete everything, saving it in nodes
/*     std::vector<node> nodes;
    while(m_filled > 0)
    {
        nodes.push_back(data[1]);
        deleteMin();
    }
    // then put it all back in
    std::cout << "\nnodes: "  << std::endl;
    for (int i = 0; i < nodes.size(); i++)
    {
        insert(nodes[i].id, nodes[i].key, nodes[i].pData);
        std::cout << nodes[i].id << ": " << nodes[i].key << std::endl;
        if (i != nodes.size()-1 && nodes[i+1].key < nodes[i].key)
        {
            std::cout << "ERROR: " << nodes[i+1].key << " < " << nodes[i].key << std::endl;
            throw "bad min";
        }
    } */

    // make sure the heap is in order of min to max by checking that the key of the parent is less than the key of the child
    for (int i = 1; i <= m_filled; i++)
    {
        if (i*2 <= m_filled && data[i].key > data[i*2].key)
        {
            std::cout << "ERROR: " << data[i].key << " > " << data[i*2].key << std::endl;
            throw "bad min";
        }
        if (i*2+1 <= m_filled && data[i].key > data[i*2+1].key)
        {
            std::cout << "ERROR: " << data[i].key << " > " << data[i*2+1].key << std::endl;
            throw "bad min";
        }
    }


}

// leave plenty of room in the hash table to avoid rehashing
heap::heap(int capacity) : mapping(2*capacity)
{
    // Allocate space for the nodes (0 slot is not used)
    data.resize(capacity + 1);

    m_filled = 0;
    m_capacity = capacity;
}

// TODO: use holes instead of recursing
//TODO: Make sure for 2 vals of the same key, the one that was inserted first is the one that is deleted first
void heap::percolateUp(int posCur)
{
    // If we are at the root, we are done.
    if (posCur == 1)
        return;

    // Compute parent position.
    int parentPos = posCur / 2;

    // If key is less than the parent's key,
    // swap with parent.
    if (data[posCur].key < data[parentPos].key)
    {
        // Swap the nodes.
        node temp = data[posCur];
        data[posCur] = data[parentPos];
        data[parentPos] = temp;

        // Swap the pointers in the hash table.
        mapping.setPointer(data[posCur].id, &data[posCur]);
        mapping.setPointer(data[parentPos].id, &data[parentPos]);

        // Recursively percolate up.
        percolateUp(parentPos);
    }

    // Otherwise, we are done.
}

// TODO: use holes instead of recursing
//TODO: Make sure for 2 vals of the same key, the one that was inserted first is the one that is deleted first
void heap::percolateDown(int posCur)
{
    // if we are at a leaf, we are done
    if (posCur * 2 > m_filled)
        return;

    int minChildPos;
    // if we have a right child, find the smaller child
    if (posCur * 2 + 1 <=m_filled)
    {
        // compute the positions of the children
        int leftChildPos = posCur * 2;
        int rightChildPos = posCur * 2 + 1;

        // find the smaller of the two children
        minChildPos = data[leftChildPos].key < data[rightChildPos].key ? leftChildPos : rightChildPos;
    }
    else
    {
        // if we only have a left child, it is the smaller child
        minChildPos = posCur * 2;
    }


    // if the smaller child is smaller than the current node,
    // swap with the smaller child
    if (data[minChildPos].key < data[posCur].key)
    {
        // swap the nodes
        node temp = data[posCur];
        data[posCur] = data[minChildPos];
        data[minChildPos] = temp;

        // swap the pointers in the hash table
        mapping.setPointer(data[posCur].id, &data[posCur]);
        mapping.setPointer(data[minChildPos].id, &data[minChildPos]);

        // recursively percolate down
        percolateDown(minChildPos);
    }

    // otherwise, we are done
}

int heap::getPos(node *pn)
{
    // A simple getPos implementation
    return (pn - &data[0]);
}

int heap::insert(const std::string &id, int key, void *pv)
{
    if (m_filled == m_capacity)
        return HEAP_FULL;

    if (mapping.contains(id))
        return ID_ALREADY_EXISTS;

    // Create a new node.
    node newNode;
    newNode.id = id;
    newNode.key = key;
    newNode.pData = pv;

    // Insert the new node at the end of the heap
    data[++m_filled] = newNode;

    // Insert the new node into the hash table.
    mapping.insert(id, &data[m_filled]);
    // Percolate up.
    percolateUp(m_filled);

    return SUCCESS;
}

int heap::setKey(const std::string &id, int key)
{
    if (!mapping.contains(id)){
        return ID_DOESNT_EXIST;
    }

   // find the node pointer in the hash table
   node *node_ptr = static_cast<node *>(mapping.getPointer(id));

   // set the node's key to the new key
   node_ptr->key = key;

   // percolate up or down as necessary
   percolateUp(getPos(node_ptr));
   percolateDown(getPos(node_ptr));

    return SUCCESS;
}


int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if (m_filled == 0)
        return HEAP_EMPTY;

    // place the last node first
    node temp = data[1];
    data[1] = data[m_filled];

    //fix the hash table
    mapping.setPointer(data[1].id, &data[1]);

    m_filled--;
    mapping.remove(temp.id);

    if (pId != nullptr)
        *pId = temp.id;
    if (pKey != nullptr)
        *pKey = temp.key;
    if (ppData != nullptr)
        *(static_cast<void **>(ppData)) = temp.pData;

    // percolate down
    percolateDown(1);

    return SUCCESS;
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    //FIXME: NOT REMOVING PROPERLY AT DEBUG 993 b/c the node in the hash table is pointing to the wrong node
    if (!mapping.contains(id))
        return ID_DOESNT_EXIST;

    // find the node pointer in the hash table
    node *node_ptr = static_cast<node *>(mapping.getPointer(id));

    int position = getPos(node_ptr);

    *pKey = data[position].key;
    ppData = data[position].pData;

    // bring the last node into position
    data[position] = data[m_filled]; // remove the last node from the hash table
    // fix the hash table
    mapping.setPointer(data[position].id, &data[position]);
    m_filled--;
    mapping.remove(id);

    // percolate up and down
    percolateUp(position);
    percolateDown(position);

    return SUCCESS;
}
