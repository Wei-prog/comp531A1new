
#ifndef LRU_H
#define LRU_H

#include "MyDB_Page.h"
#include "MyDB_Table.h"
#include "MyDB_BufferManager.h"
#include <list>
#include <string>
#include <iostream>
#include <memory>

using namespace std;
class LRU{

public:

    LRU(size_t length ,MyDB_BufferManager &boss);
    ~LRU();
    void* getBytes();
    size_t currLeftMem();
    void load(MyDB_PagePtr page); //save to mem buffer, same time update lru
    void evict(); //evict from lru, page not killed(see ref), not in buffer
    void houseKeeping(); //check everything fine in mem buffer and LRU

private:

    std::list< pair<MyDB_PagePtr,void*> > li;
    std::list<void*> avail;
    size_t length;
    MyDB_BufferManager &boss;    
    
};

#endif