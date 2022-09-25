#include <heap.h>

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

    // compute the positions of the children
    int leftChild = posCur * 2;
    int rightChild = posCur * 2 + 1;

    // find the smaller of the two children
    int minChild = std::min(data[leftChild].key, data[rightChild].key);

    // if the smaller child is smaller than the current node,
    // swap with the smaller child
    if (minChild < data[posCur].key)
    {
        // swap the nodes
        node temp = data[posCur];
        data[posCur] = data[minChild];
        data[minChild] = temp;

        // swap the pointers in the hash table
        mapping.setPointer(data[posCur].id, &data[posCur]);
        mapping.setPointer(data[minChild].id, &data[minChild]);

        // recursively percolate down
        percolateDown(minChild);
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

    // percolate up or down as necessary
    if (key < data[getPos(node_ptr)].key){
        percolateUp(getPos(node_ptr));
    }
    else{
        percolateDown(getPos(node_ptr));
    }

   // set the node's key to the new key
   node_ptr->key = key;

    return SUCCESS;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if (m_filled == 0)
        return HEAP_EMPTY;

    // swap the root with the last node
    node temp = data[1];
    data[1] = data[m_filled];
    data[m_filled] = temp;
    m_filled--;
    //FIXME: remove the last node from the hash table
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
    if (!mapping.contains(id))
        return ID_DOESNT_EXIST;

    // find the node pointer in the hash table
    node *node_ptr = static_cast<node *>(mapping.getPointer(id));

    // swap the node with the last node
    node temp = data[getPos(node_ptr)];
    data[getPos(node_ptr)] = data[m_filled];
    data[m_filled--] = temp;

    // remove the last node from the hash table
    *pKey = data[m_filled + 1].key;
    ppData = data[m_filled + 1].pData;
    //FIXME: remove the last node from the hash table
    mapping.remove(id);

    // percolate down
    percolateDown(getPos(node_ptr));

    return SUCCESS;
}