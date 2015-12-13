#include "b+tree.h"

BPTree::BPTree(int iVar)
{
	key* temp = new key();
	Page* tempPage = new Page();
	temp->var = iVar;
	rootPage->page[0] = temp;
	rootPage->size++;
}
bool BPTree::search(int iVar, Page* keypage)
{
	if (keypage->leftPage != nullptr)
	{
		for (int i = 0; i < keypage->size; i++)
		{
			if (iVar < keypage->page[i]->var && i == 0)
				return search(iVar, keypage->leftPage);
			else if (i == keypage->size - 1 && iVar > keypage->page[i]->var)
				return search(iVar, keypage->page[i]->rightPage);
			else if (iVar > keypage->page[i]->var && iVar < keypage->page[i + 1]->var)
				return search(iVar, keypage->page[i]->rightPage);
		}
	}
	else 
	{
		for (int i = 0; i < keypage->size; i++)
		{
			if (iVar == keypage->page[i]->var)
				return true;
		}
	}
	return false;
}
int BPTree::insert(int iVar, Page* keypage)
{
	key* temp = new key();
	temp->var = iVar;
	if (keypage->size == KEYS)
	{
		keypage = splitPage(keypage);
		if (iVar > keypage->page[0]->var)
			return insert(iVar, keypage->page[0]->rightPage);
		else
			return insert(iVar, keypage->leftPage);
		
	}
	else if (keypage->leftPage == nullptr)
	{
		keypage->page[keypage->size] = temp;
		std::sort(keypage->page, keypage->page + keypage->size);
		keypage->size++;
	}
	else
	{
		for (int i = 0; i < keypage->size; i++)
		{
			if (i == 0 && iVar < keypage->page[i]->var)
				return insert(iVar, keypage->leftPage);
			else if (i == keypage->size - 1 && iVar > keypage->page[i]->var)
				return insert(iVar, keypage->page[i]->rightPage);
			else if (iVar > keypage->page[i]->var && iVar < keypage->page[i + 1]->var)
				return insert(iVar, keypage->page[i]->rightPage);
		}
	}
	return 0;
}
Page* BPTree::splitPage(Page* keypage)
{
	struct Page* tempLeft = new Page();
	struct Page* tempRight = new Page();
	if (keypage == rootPage)
	{
		tempLeft->page[0] = keypage->page[0];
		tempLeft->page[1] = keypage->page[1];
		tempRight->page[0] = keypage->page[2];
		tempRight->page[1] = keypage->page[3];
		tempLeft->size = sizeof(tempLeft->page);
		tempRight->size = sizeof(tempRight->page);
		keypage->page[0] = keypage->page[(KEYS / 2) - 1];
		keypage->page[1] = nullptr;
		keypage->page[2] = nullptr;
		keypage->page[3] = nullptr;
		keypage->leftPage = tempLeft;
		keypage->page[0]->rightPage = tempRight;
		tempLeft->size = 2;
		tempRight->size = 2;
		keypage->size = 1;
	}
	else 
	{
		rootPage->page[rootPage->size] = keypage->page[(KEYS / 2) - 1];
		rootPage->page[rootPage->size]->rightPage = tempRight;
		rootPage->size++;
		tempRight->page[0] = keypage->page[2];
		tempRight->page[1] = keypage->page[3];
		tempRight->size = 2;
		keypage->page[2] = nullptr;
		keypage->size--;
		keypage->page[3] = nullptr;
		keypage->size--;
	}
	return keypage;
}
BPTree::~BPTree()
{
	delete rootPage;
}