
#ifndef LRU_C
#define LRU_C

#include "MyDB_Page.h"
#include "../headers/MyDB_LRU.h"
//#include "MyDB_BufferManager.h"
#include <list>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

LRU :: LRU(size_t length,size_t pageSize,void* buffLoc,MyDB_BufferManager &boss):boss(boss){
    this->length = length;
    this->pageSize = pageSize;
    this->li = std::list<pair<MyDB_PagePtr,void*> >();
    for(size_t i = 0;i<length;i++){
        (this->avail).push_back(((char*)buffLoc)+(pageSize*i));
    } //ptrs to loc in memBuffer
}

LRU :: ~LRU(){
    //for(auto ptr : this->avail){
    //    delete(ptr);
    //}
   // for(auto node : this->li){
     //   delete(node);
   // }
}

size_t LRU :: currLeftMem(){
    return this->avail.size();
}
void LRU :: houseKeeping(){

}
void* LRU :: getBytes(){
    if(this->avail.size()<= 0){
        evict();
    }
    if(this->avail.size()<=0){
        return nullptr;
    }
    void* res = this->avail.front();
    this->avail.pop_front();
    cout<<"page Byte:"
    return res; //make sure byte is not lost
}

void LRU:: load(MyDB_PagePtr page){
    void* pos = page->getBytes();
    pair<MyDB_PagePtr,void*> node= make_pair(page,pos);
    this->li.push_back(node);
}

void LRU:: evict(){
    std::list<pair<MyDB_PagePtr,void*> >::iterator node;
    for (node=this->li.begin();node->first->isPinned==true;node++){
        if (node == this->li.end()){
            exit(0);
        }
    }
    void* loc = node->second;
    MyDB_PagePtr temp = node->first;
    this->li.erase(node);
    //write to disk, set dirty to false
    //pages are written to disk, right now memory is not cleaned, so data length in pageSize must be same
    if(temp->isDirty==true){
        temp->writeDisk(this->pageSize,loc);
    }
    this->avail.push_back(loc);
}

#endif


