
#ifndef LRU_C
#define LRU_C

#include "MyDB_Page.h"
#include "LRU.h"
#include "MyDB_Table.h"
#include "MyDB_BufferManager.h"
#include <list>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

LRU :: LRU(size_t length,size_t pageSize,void* buffLoc,MyDB_BufferManager &boss){
    this->boss = boss;
    this->length = length;
    this->pageSize = pageSize;
    this->li = null;
    for(size_t i = 0;i<length;i++){
        (this->avail).push_back(((char*)buffLoc)+(pageSize*i));
    } //ptrs to loc in memBuffer
}

LRU :: ~LRU(){
    for(auto ptr : this->avail){
        free(ptr);
    }
    for(auto node : this->li){
        free(node);
    }
}

LRU :: load(MyDB_PagePtr page){
    //.first //.second
}

#endif


