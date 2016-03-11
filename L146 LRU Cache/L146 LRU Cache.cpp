#include "stdafx.h"

#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct LinkedNode
{
	int key;
	int value;
	LinkedNode* prev;
	LinkedNode* next;
	LinkedNode() : key(0), value(0), prev(NULL), next(NULL){}
	LinkedNode(int k, int v) : key(k), value(v), prev(NULL), next(NULL){}
};

class LRUCache{

private:

	int mCapacity;
	unordered_map<int, LinkedNode*> mData;

	LinkedNode* mHeader;
	LinkedNode* mTail;

public:

	LRUCache(int capacity) {
		mCapacity = capacity;
		mHeader = NULL;
		mTail = NULL;
	}

	int get(int key) {

		unordered_map<int, LinkedNode*>::iterator it = mData.find(key);

		if (it != mData.end())
		{
			LinkedNode* node = (*it).second;

			moveToHeader(node);

			return node->value;
		}
		else
		{
			return -1;
		}
	}

	void set(int key, int value)
	{
		unordered_map<int, LinkedNode*>::iterator it = mData.find(key);

		if (it != mData.end())
		{
			(*it).second->value = value;
			moveToHeader((*it).second);
		}
		else if ((int)mData.size() < mCapacity)
		{
			LinkedNode* node = new LinkedNode(key, value);
			mData.insert(pair<int, LinkedNode*>(key, node));

			insertToHeader(node);
		}
		else
		{
			LinkedNode* tail = removeTail();

			mData.erase(tail->key);

			tail->key = key;
			tail->value = value;

			mData.insert(pair<int, LinkedNode*>(key, tail));

			insertToHeader(tail);
		}
	}

	void insertToHeader(LinkedNode* node)
	{
		if (mHeader == NULL)
		{
			mHeader = mTail = node;
		}
		else
		{
			node->next = mHeader;
			mHeader->prev = node;
			mHeader = node;
		}
	}

	LinkedNode* removeTail()
	{
		LinkedNode* tail = mTail;

		if (mHeader == mTail)
		{
			mHeader = mTail = NULL;
		}
		else
		{
			mTail = mTail->prev;
			mTail->next = NULL;
		}

		tail->prev = NULL;
		tail->next = NULL;

		return tail;
	}

	void moveToHeader(LinkedNode* node)
	{
		if (node == mHeader)
		{
			return;
		}
		else
		{
			if (node == mTail)
			{
				removeTail();
				insertToHeader(node);
			}
			else
			{
				node->prev->next = node->next;
				node->next->prev = node->prev;

				node->prev = NULL;
				node->next = NULL;

				insertToHeader(node);
			}
		}
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	LRUCache cache(3);

	cache.set(1, 4);
	cache.set(1, 5);
	cache.set(2, 1);
	cache.set(3, 1);
	cache.set(4, 1);

	cache.get(1);



	LRUCache c1(2);

	c1.set(2, 1);
	c1.set(1, 1);
	c1.get(2);
	c1.set(4, 1);
	c1.get(1);
	c1.get(2);

	return 0;
}

