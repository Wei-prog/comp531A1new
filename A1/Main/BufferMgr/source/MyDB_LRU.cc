
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

LRU size_t :: currLeftMem(){
    return this->avail.size();
}
LRU void :: housekeeping(){

}
LRU void* :: getBytes(){
    if(this->avail.size() <= 0){
        houseKeeping();
    }
    if(this->avail.size()<=0){
        return nullptr;
    }
    return this->avail.pop_front(); //make sure byte is not lost
}

LRU void :: load(MyDB_PagePtr page){
    void* pos = page->getBytes();
    pair<MyDB_PagePtr,void*> node= make_pair(page,pos);
    this->li.push_back(node);
}

LRU void :: evict(){
    std::list<pair<MyDB_PagePtr,void*> >::iterator node;
    for (node=this->li.begin();node.second->isPinned==true;node++){
        ;
    }
    void* loc = node->first;
    MyDB_PagePtr temp = node->second;
    this->li.erase(node);
    //write to disk, set dirty to false
    //pages are written to disk, right now memory is not cleaned, so data length in pageSize must be same
    if(temp->isDirty()==true){
        temp->writeDisk(this->pageSize,loc);
    }
    this->avail.push_back(loc);
}

#endif


