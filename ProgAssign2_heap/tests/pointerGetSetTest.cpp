#include <hash.h>
#include <iostream>
#include <vector>

std::vector<bool> TEST;

void test() {
    hashTable ht(50'000);
    int goat = 12;

    ht.insert("cat");
    ht.insert("boat");
    TEST.push_back( ht.getPointer("cat") == nullptr );
    TEST.push_back( ht.getPointer("boat") == nullptr );

    ht.setPointer("cat", &goat);

    TEST.push_back(ht.getPointer("cat") == &goat );

    int* toad = static_cast<int*>(ht.getPointer("cat"));
    (*toad)++;

    TEST.push_back( *static_cast<int*>(ht.getPointer("cat")) == 13 );

    // print index of failed test
    for (int i = 0; i < TEST.size(); i++) {
        if (!TEST[i]) {
            std::cout << "Failed test " << i << std::endl;
        }
    }
}