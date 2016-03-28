#include "stdafx.h"
#include "../StopWatch.h"

#include <cstdio>
#include <ctime>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	static int candy(vector<int>& ratings)
	{
		int last = (int)ratings.size();

		vector<int> candies(last, 1);

		last--;

		for (int i = 0, j = 1; i < last; i++, j++)
		{
			if (ratings[j] > ratings[i] && candies[j] <= candies[i])
			{
				candies[j] = candies[i] + 1;
			}
		}

		int sum = 0;

		for (int i = last, j = last - 1; i > 0; i--, j--)
		{
			if (ratings[j] > ratings[i] && candies[j] <= candies[i])
			{
				candies[j] = candies[i] + 1;
			}

			sum += candies[i];
		}

		sum += candies[0];

		return sum;
	}
};

void print(string name, vector<int>& vectors)
{
	printf("%s: ", name.c_str());

	vector<int>::iterator it = vectors.begin();

	if (it != vectors.end())
	{
		printf("%d", *it);
		++it;
	}

	for (; it != vectors.end(); ++it)
	{
		printf(", %d", *it);
	}

	printf("\n");
}

void test(int* ratings, int size, int expected)
{
	vector<int> v(ratings, ratings + size);
	int count = Solution::candy(v);
	printf(count == expected ? "Okay\n" : "Failed\n");
}

void test1()
{
	int ratings[] = { 1, 2, 2 };
	test(ratings, sizeof(ratings) / sizeof(int), 4);
}

void test2()
{
	int ratings[] = { 3, 1, 2, 2 };
	test(ratings, sizeof(ratings) / sizeof(int), 6);
}

int _tmain(int argc, _TCHAR* argv[])
{
	StopWatch sw;

	sw.start();

	for (int i = 0; i < 100; i++)
	{
		test1();
		test2();
	}

	sw.stop();

	printf("%d\n", (int)sw.getElapsed());

	return 0;
}
