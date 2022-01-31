
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include "MyDB_LRU.h"
#include "MyDB_PageHandle.h"
#include "MyDB_Table.h"
#include "MyDB_Page.h"
#include <cstdlib>
#include <map>
#include <vector>
#include<string>


MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr, long) {
	return nullptr;		
}

MyDB_PageHandle MyDB_BufferManager :: getPage () {
	return nullptr;		
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage (MyDB_TablePtr, long) {
	return nullptr;		
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage () {
	return nullptr;		
}

void MyDB_BufferManager :: unpin (MyDB_PageHandle unpinMe) {
	
}

MyDB_BufferManager :: MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile) {
	this->pageSize = pageSize;
	this->numPages = numPages;
	this->tempFile = tempFile;
	this->lookupTable = std::map<pair<MyDB_TablePtr,long>, MyDB_PagePtr>();
	for (size_t i =0 ; i<numPages;i++){
		this->memBuffer.push_back((void*)malloc(pageSize));
	}
	this->lru = new LRU(numPages, pageSize,&(this->memBuffer).front(),*this);
}

MyDB_BufferManager :: ~MyDB_BufferManager () {
	this->memBuffer.clear();
	delete(this->lru);
}
	
#endif


