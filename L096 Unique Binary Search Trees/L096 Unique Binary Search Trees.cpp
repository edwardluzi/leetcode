// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Solution
{
public:
	static int numTrees(int n)
	{
		initCache(n);

		return numTress(1, n);
	}

private:

	static int size;
	static int* cache;

	static void initCache(int n)
	{
		if (cache != NULL)
		{
			delete[]cache;
		}

		size = n;
		cache = new int[n];

		memset(cache, 0, sizeof(int)* n);
	}

	static int numTress(int small, int big)
	{
		if (small >= big)
		{
			return 1;
		}
		else
		{
			if (cache[big - small] != 0)
			{
				return cache[big - small];
			}

			int num = 0;
			int left = 0;
			int right = 0;

			for (int root = small; root <= big; root++)
			{
				left = numTress(small, root - 1);
				right = numTress(root + 1, big);

				num += (left * right);
			}

			cache[big - small] = num;

			return num;
		}
	}
};

int* Solution::cache = NULL;
int Solution::size = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	int num = Solution::numTrees(19);

	while (1)
	{
		printf("Please input a number, 0 to exit: ");
		scanf_s("%d", &num);

		if (num <= 0)
		{
			break;
		}

		printf("Total count of unique BST is: %d\n\n", Solution::numTrees(num));
	}

	return 0;
}

