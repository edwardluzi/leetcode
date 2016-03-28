#include "stdafx.h"

class Solution
{
public:

	Solution() :
		mSize(0), mCache(0)
	{
	}

	int numTrees(int n)
	{
		initCache(n);
		return numTress(1, n);
	}

private:

	int mSize;
	int* mCache;

private:

	void initCache(int n)
	{
		if (mCache != NULL)
		{
			delete[] mCache;
		}

		mSize = n;
		mCache = new int[n];

		memset(mCache, 0, sizeof(int)* n);
	}

	int numTress(int small, int big)
	{
		if (small >= big)
		{
			return 1;
		}
		else
		{
			if (mCache[big - small] != 0)
			{
				return mCache[big - small];
			}

			int num = 0;
		
			for (int root = small; root <= big; root++)
			{
				num += (numTress(small, root - 1) * numTress(root + 1, big));
			}

			mCache[big - small] = num;

			return num;
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	Solution s;

	int num = s.numTrees(19);

	for (;;)
	{
		printf("Please input a number, 0 to exit: ");
		scanf_s("%d", &num);

		if (num <= 0)
		{
			break;
		}

		printf("Total count of unique BST is: %d\n\n", s.numTrees(num));
	}

	return 0;
}

