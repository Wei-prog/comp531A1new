
#ifndef PAGE_HANDLE_C
#define PAGE_HANDLE_C

#include <memory>
#include "MyDB_Page.h"
#include "MyDB_PageHandle.h"

void *MyDB_PageHandleBase :: getBytes () {
	return this->myPage->getBytes();
}

void MyDB_PageHandleBase :: wroteBytes () {
	this->myPage->isDirty = true;
}

MyDB_PageHandleBase :: ~MyDB_PageHandleBase () {
	this->myPage->decRef();
}
MyDB_PageHandleBase :: MyDB_PageHandleBase(MyDB_PagePtr myPage){
	this->myPage = myPage;
	this->myPage->incRef();
}

#endif

