#pragma once

#include<iostream>
#include<vector>
#include<string>
#include <algorithm>

#define KEYS 4

struct key {
	int var = 0;
	struct Page* rightPage;
	key()
	{
		rightPage = nullptr;
	}
};

struct Page {
	struct key* page[KEYS];
	struct Page* leftPage;
	int size = 0;
	Page()
	{
		for (int i = 0; i < KEYS; i++)
			page[i] = nullptr;
		leftPage = nullptr;
	}
};



class BPTree{
private:
	Page* rootPage;
public:
	BPTree(int);
	bool search(int, Page*);
	int insert(int, Page*);
	void Delete(int);
	//bool checkPages();
	//void balancePage();
	Page* splitPage(Page*);
	void MergePage();
	Page* getRoot() { return rootPage; }
	~BPTree();
};