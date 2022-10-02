#include <heap.h>
#include <iostream>

//TODO: REMOVE THIS, FOR DEBUGGING ONLY
void heap::debugStuff()
{
    std::cout << "Heap: " << std::endl;
    //loop through the heap
    for (int i = 1; i <= m_filled; i++)
    {
        std::cout << data[i].id << ": " << data[i].key << std::endl;

        if(!mapping.contains(data[i].id))
        {
            throw "THIS IS BREAKING HERE";
        }
    }
    std::cout << "\nHash Table: " << std::endl;

    int mapping_filled = 0;

    // loops through the hash table
    for (int i = -10; i <= 10; i++)
    {
        std::string id = "id" + std::to_string(i);
        if (mapping.contains(id)) 
        {
            int key = static_cast<node*>(mapping.getPointer(id))->key;

            std::cout << "id" << i << ": " << key << std::endl;

            mapping_filled++;
           }
    }

    if(mapping_filled != m_filled)
    {
        throw "mapping_filled != m_filled";
    }


    std::cout << "---------------------" << std::endl;
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
    debugStuff(); //TODO: REMOVE THIS, FOR DEBUGGING ONLY
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
    debugStuff(); //TODO: REMOVE THIS, FOR DEBUGGING ONLY
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
    debugStuff(); //TODO: REMOVE THIS, FOR DEBUGGING ONLY

    if (m_filled == 0)
        return HEAP_EMPTY;

    // place the last node first
    node temp = data[1];
    data[1] = data[m_filled];

    //FIXME: remove the last node from the hash table
    m_filled--;
    mapping.remove(temp.id);

    *pId = temp.id;
    *pKey = temp.key;
    ppData = temp.pData;


    // percolate down
    percolateDown(1);

    return SUCCESS;
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    //FIXME: NOT REMOVING PROPERLY AT DEBUG 951
    debugStuff(); //TODO: REMOVE THIS, FOR DEBUGGING ONLY
    if (!mapping.contains(id))
        return ID_DOESNT_EXIST;

    // find the node pointer in the hash table
    node *node_ptr = static_cast<node *>(mapping.getPointer(id));

    int position = getPos(node_ptr);

    *pKey = data[position].key;
    ppData = data[position].pData;

    // bring the last node into position
    data[position] = data[m_filled]; // remove the last node from the hash table
    m_filled--;
    mapping.remove(id);

    // percolate down
    percolateDown(position);

    return SUCCESS;
}
