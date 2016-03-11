#include "stdafx.h"

#include <vector>
#include <stack>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution
{
public:
	static int candy(vector<int>& ratings)
	{
		vector<int> candies(ratings.size(), 1);

		for (int i = 0; i < (int)ratings.size() - 1; i++)
		{
			if (ratings[i + 1] > ratings[i])
			{
				if (candies[i + 1] <= candies[i])
				{
					candies[i + 1] = candies[i] + 1;
				}
			}
		}

		for (int i = (int)ratings.size() - 1; i > 0; i--)
		{
			if (ratings[i - 1] > ratings[i])
			{
				if (candies[i - 1] <= candies[i])
				{
					candies[i - 1] = candies[i] + 1;
				}
			}
		}

		Print("Ratings", ratings);
		Print("Candies", candies);

		return accumulate(candies.begin(), candies.end(), 0);
	}

	static void Print(string name, vector<int>& vectors)
	{
		bool firstNumber = true;

		printf("%s: ", name.c_str());

		for (vector<int>::iterator it = vectors.begin(); it != vectors.end(); it++)
		{
			if (firstNumber)
			{
				printf("%d", *it);
				firstNumber = false;
			}
			else
			{
				printf(", %d", *it);
			}
		}

		printf("\n");
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> ratings;

	ratings.push_back(1);
	ratings.push_back(2);
	ratings.push_back(2);

	printf("Candy Count = %d\n\n", Solution::candy(ratings));

	ratings.clear();

	ratings.push_back(3);
	ratings.push_back(1);
	ratings.push_back(2);
	ratings.push_back(2);

	printf("Count = %d\n\n", Solution::candy(ratings));

	return 0;
}

