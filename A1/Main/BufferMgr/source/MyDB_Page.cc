
#ifndef PAGE_C
#define PAGE_C

#include <memory>
#include <string>
#include "MyDB_Table.h"
#include "MyDB_BufferManager.h"
#include "MyDB_Page.h"

void *MyDB_Page :: getBytes () {
	return this->bytes;
}
void MyDB_Page::incRef() {
    this->ref++;
}
void MyDB_Page::decRef() {
    this->ref--;
    if(this->ref == 0){
        this->isPinned = false;
    }
}
MyDB_Page ::MyDB_Page(pair<MyDB_TablePtr,long> pageId, void* bytesVal, MyDB_BufferManager &boss){
    this->boss = boss;
    this->pageId = pageId;
    this->bytes = bytesVal;
}
MyDB_Page ::~MyDB_Page(){
}

#endif