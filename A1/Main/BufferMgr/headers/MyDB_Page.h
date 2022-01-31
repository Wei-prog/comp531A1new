
#ifndef PAGE_H
#define PAGE_H

#include "../../Catalog/headers/MyDB_Table.h"
#include "MyDB_BufferManager.h"
#include <string>
#include <memory>

using namespace std;
class MyDB_Page;
typedef shared_ptr <MyDB_Page> MyDB_PagePtr;
class MyDB_BufferManager;
class MyDB_Page{

public:

    bool isDirty;
    bool isPinned;

    MyDB_Page(pair<MyDB_TablePtr,long> pageId, void* bytesVal, MyDB_BufferManager &boss);
    ~MyDB_Page();
    void *getBytes();
    void incRef();
    void decRef();
    int getRef();
    void writeDisk(size_t pageSize,void* loc);

private:

    MyDB_BufferManager &boss;
    pair<MyDB_TablePtr,long> pageId;
    void* bytes;
    int ref;
    
    
};

#endif