
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include "MyDB_LRU.h"
#include "MyDB_PageHandle.h"
#include "MyDB_BufferManager.h"
#include "../../Catalog/headers/MyDB_Table.h"
#include "MyDB_Page.h"
#include <cstdlib>
#include <map>
#include <vector>
#include <memory>
#include<string>


MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr whichTable, long i) {
	if(whichTable == nullptr){
		exit(0);
	}
	pair<MyDB_TablePtr,long> pageId = make_pair(whichTable,i);
	map<pair<MyDB_TablePtr,long>, MyDB_PagePtr>::iterator row;
	row = this->lookupTable.find(pageId);
	if(row == this->lookupTable.end()){
		void* dst = this->lru->getBytes();
		if(dst == nullptr){
			exit(0); //buffer memeory all pinned
		}
		MyDB_PagePtr naPage = make_shared <MyDB_Page> (pageId,dst,*this);
		this->lookupTable[pageId] = naPage;
		return make_shared <MyDB_PageHandleBase> (naPage);
	} else {
		MyDB_PagePtr oldPage = this->lookupTable[pageId];
		if(oldPage==nullptr || oldPage->getRef()<=0){
			delete(oldPage); //?
			void* dst = this->lru->getBytes();
			if(dst == nullptr){
				exit(0); //buffer memeory all pinned
			}
			MyDB_PagePtr naPage = make_shared <MyDB_Page> (pageId,dst,*this);
			this->lookupTable[pageId] = naPage;
			return make_shared <MyDB_PageHandleBase> (naPage);
		}else{
			return make_shared <MyDB_PageHandleBase> (oldPage);
		}
	}
}
MyDB_PageHandle MyDB_BufferManager :: getPage () {
	pair<MyDB_TablePtr,long > a = make_pair(nullptr,this->fileOffset);
	void* dst = this->lru->getBytes();
	MyDB_PagePtr aPage = make_shared<MyDB_Page>(a,dst,*this);
	this->fileOffset ++;
	return make_shared<MyDB_PageHandleBase> (aPage);
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage (MyDB_TablePtr whichTable, long i) {
	if(whichTable == nullptr){
		exit(0);
	}
	pair<MyDB_TablePtr,long> pageId = make_pair(whichTable,i);
	map<pair<MyDB_TablePtr,long>, MyDB_PagePtr>::iterator row;
	row = this->lookupTable.find(pageId);
	if(row == this->lookupTable.end()){
		void* dst = this->lru->getBytes();
		if(dst == nullptr){
			exit(0); //buffer memeory all pinned
		}
		MyDB_PagePtr naPage = make_shared <MyDB_Page> (pageId,dst,*this);
		naPage->isPinned = true;
		this->lookupTable[pageId] = naPage;
		return make_shared <MyDB_PageHandleBase> (naPage);
	} else {
		MyDB_PagePtr oldPage = this->lookupTable[pageId];
		if(oldPage==nullptr || oldPage->getRef()<=0){
			delete(oldPage); //?
			void* dst = this->lru->getBytes();
			if(dst == nullptr){
				exit(0); //buffer memeory all pinned
			}
			MyDB_PagePtr naPage = make_shared <MyDB_Page> (pageId,dst,*this);
			naPage->isPinned = true;
			this->lookupTable[pageId] = naPage;
			return make_shared <MyDB_PageHandleBase> (naPage);
		}else{
			return make_shared <MyDB_PageHandleBase> (oldPage);
		}
	}	
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage () {
	pair<MyDB_TablePtr,long > a = make_pair(nullptr,this->fileOffset);
	void* dst = this->lru->getBytes();
	MyDB_PagePtr aPage = make_shared<MyDB_Page>(a,dst,*this);
	aPage->isPinned = true;
	this->fileOffset ++;
	return make_shared<MyDB_PageHandleBase> (aPage);	
}

void MyDB_BufferManager :: unpin (MyDB_PageHandle unpinMe) {
	unPinMe->myPage->isPinned = false;
}

MyDB_BufferManager :: MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile) {
	this->pageSize = pageSize;
	this->numPages = numPages;
	this->tempFile = tempFile;
	this->fileOffset = 0;
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


