#include "stdafx.h"

#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:

	static const int MinValue = (int)0x80000000;

public:
	static int calculateMinimumHP(vector<vector<int>>& dungeon)
	{
		if (dungeon.size() == 0 || dungeon[0].size() == 0)
		{
			return 0;
		}

		unordered_map<string, int> cache;

		int hp = calculateMinimumHP(dungeon, dungeon[0].size(), dungeon.size(),
			0, 0, cache);

		if (hp <= 0)
		{
			return 1 - hp;
		}
		else
		{
			return 1;
		}
	}

	static int calculateMinimumHP(vector<vector<int>>& dungeon, int width,
		int height, int x, int y, unordered_map<string, int>& cache)
	{
		if (x == width - 1 && y == height - 1)
		{
			return dungeon[y][x];
		}
		else
		{
			string key = makeKey(x, y);
			unordered_map<string, int>::iterator it = cache.find(key);

			if (it != cache.end())
			{
				return it->second;
			}

			int hp1 =
				(x < width - 1) ?
				calculateMinimumHP(dungeon, width, height, x + 1, y,
				cache) :
				MinValue;

			int hp2 =
				(y < height - 1) ?
				calculateMinimumHP(dungeon, width, height, x, y + 1,
				cache) :
				MinValue;

			int cur = dungeon[y][x];
			int hp = (hp1 > hp2 ? hp1 : hp2) + cur;

			hp = hp <= cur ? hp : cur;

			cache.insert(pair<string, int>(key, hp));

			return hp;
		}
	}

	static string makeKey(int x, int y)
	{
		static char buffer[64];

#if VS2013
		sprintf_s(buffer, 63, "%d,%d", x, y);
#else
		sprintf(buffer, "%d,%d", x, y);
#endif
		return string(buffer);
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

	int result = Solution::calculateMinimumHP(dungeon);

	printf(result == 7 ? "Okay - %d \n" : "Failed - %d\n", result);
}

void test2()
{
	int row1[] = { -200 };

	vector<vector<int>> dungeon;

	dungeon.push_back(vector<int>(row1, row1 + sizeof(row1) / sizeof(int)));

	int result = Solution::calculateMinimumHP(dungeon);

	printf(result == 201 ? "Okay - %d \n" : "Failed - %d\n", result);
}

void test3()
{
	int row1[] = { 100 };

	vector<vector<int>> dungeon;

	dungeon.push_back(vector<int>(row1, row1 + sizeof(row1) / sizeof(int)));

	int result = Solution::calculateMinimumHP(dungeon);

	printf(result == 1 ? "Okay - %d \n" : "Failed - %d\n", result);
}

int _tmain(int argc, _TCHAR* argv[])
{
	test1();
	test2();
	test3();

	return 0;
}
