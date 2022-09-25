void test1()
{
    heap myHeap(100);
    std::string id = "";
    int key = 0;
    int retVal = 0;

    // Insert keys from Insertion Example in the powerpoint
    retVal = myHeap.insert("A", 13);
    retVal = myHeap.insert("B", 21);
    retVal = myHeap.insert("C", 16);
    retVal = myHeap.insert("D", 24);
    retVal = myHeap.insert("E", 31);
    retVal = myHeap.insert("F", 19);
    retVal = myHeap.insert("G", 68);
    retVal = myHeap.insert("H", 65);
    retVal = myHeap.insert("I", 26);
    retVal = myHeap.insert("J", 32);
    retVal = myHeap.insert("K", 14);

    // deleteMin's and check that it's working
    int last = -999999;
    for (int i = 0; i < 11; i++)
    {
        retVal = myHeap.deleteMin(&id, &key);

        std::cout << "\ndeleteMin returned: " << retVal << " id: " << id << " key: " << key << std::endl;

        if (key < last) {
            std::cout << "test failed" << std::endl;
        }
        last = key;
    }
}


