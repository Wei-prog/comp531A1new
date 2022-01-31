
#ifndef PAGE_C
#define PAGE_C

#include <memory>
#include <string>
#include <fcntl.h>
#include <unistd.h>
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
int MyDB_Page ::getRef(){
    return this->ref;
}
void MyDB_Page::writeDisk(size_t pageSize,void* loc){
    MyDB_TablePtr dest = this->pageId.first;
    long offset = this->pageId.second;
    int fd;
    if(dest== nullptr){
        //write anonymous page
        fd = open(this->boss.tempFile.c_str(),O_CREAT | O_RDWR | O_SYNC, 0666);
    }else{
        fd = open(dest->getStorageLoc().c_str(), O_CREAT | O_RDWR | O_SYNC, 0666);
    }
    lseek(fd,offset*pageSize,SEEK_SET);
    write(fd,loc,pageSize);
    close(fd);
    this->isDirty=false;
}
MyDB_Page ::MyDB_Page(pair<MyDB_TablePtr,long> pageId, void* bytesVal, MyDB_BufferManager &boss){
    this->ref = 0;
    this->boss = boss;
    this->pageId = pageId;
    this->bytes = bytesVal;
}
MyDB_Page ::~MyDB_Page(){
    free(this);
}

#endif