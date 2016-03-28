#include "stdafx.h"

#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
private:

	const int MinValue = (int)0x80000000;

private:

	int mWidth;
	int mHeight;
	vector<vector<int>> mCache;

public:

	Solution() :mWidth(0), mHeight(0){}

public:

	int calculateMinimumHP(vector<vector<int>>& dungeon)
	{
		if ((mHeight = dungeon.size()) == 0 || (mWidth = dungeon[0].size()) == 0)
		{
			return 0;
		}

		mCache.resize(mHeight, vector<int>(mWidth, MinValue));

		int hp = calculateMinimumHP(dungeon, 0, 0);

		if (hp <= 0)
		{
			return 1 - hp;
		}
		else
		{
			return 1;
		}
	}

	int calculateMinimumHP(vector<vector<int>>& dungeon, int x, int y)
	{
		if (x == mWidth - 1 && y == mHeight - 1)
		{
			return dungeon[y][x];
		}
		else
		{
			int hp = mCache[y][x];

			if (hp != MinValue)
			{
				return hp;
			}

			int hp1 = (x < mWidth - 1) ? calculateMinimumHP(dungeon, x + 1, y) : MinValue;
			int hp2 = (y < mHeight - 1) ? calculateMinimumHP(dungeon, x, y + 1) : MinValue;
			int cur = dungeon[y][x];

			hp = (hp1 > hp2 ? hp1 : hp2) + cur;

			if (hp > cur)
			{
				hp = cur;
			}

			mCache[y][x] = hp;

			return hp;
		}
	}
};

void test1()
{
	int row1[] = { -2, -3, 3 };
	int row2[] = { -5, -10, 1 };
	int row3[] = { 10, 30, -5 };

	vector<vector<int>> dungeon;

	dungeon.push_back(vector<int>(row1, row1 + sizeof(row1) / sizeof(int)));
	dungeon.push_back(vector<int>(row2, row2 + sizeof(row2) / sizeof(int)));
	dungeon.push_back(vector<int>(row3, row3 + sizeof(row3) / sizeof(int)));

	Solution s;

	int result = s.calculateMinimumHP(dungeon);

	printf(result == 7 ? "Okay - %d \n" : "Failed - %d\n", result);
}

void test2()
{
	int row1[] = { -200 };

	vector<vector<int>> dungeon;

	dungeon.push_back(vector<int>(row1, row1 + sizeof(row1) / sizeof(int)));

	Solution s;

	int result = s.calculateMinimumHP(dungeon);

	printf(result == 201 ? "Okay - %d \n" : "Failed - %d\n", result);
}

void test3()
{
	int row1[] = { 100 };

	vector<vector<int>> dungeon;

	dungeon.push_back(vector<int>(row1, row1 + sizeof(row1) / sizeof(int)));

	Solution s;

	int result = s.calculateMinimumHP(dungeon);

	printf(result == 1 ? "Okay - %d \n" : "Failed - %d\n", result);
}

int _tmain(int argc, _TCHAR* argv[])
{
	test1();
	test2();
	test3();

	return 0;
}
