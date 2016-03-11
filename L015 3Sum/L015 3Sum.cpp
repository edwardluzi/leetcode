
#include "stdafx.h"

#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:

	static vector<vector<int>> threeSum(vector<int>& nums)
	{
		int sum1 = 0;
		int sum2 = 0;
		vector<vector<int>> results;

		sort(nums.begin(), nums.end());

		for (int i = 0; i < (int)nums.size()-2; i++)
		{
			if (nums[i] > 0)
			{
				break;
			}

			if (i > 0 && nums[i] == nums[i - 1])
			{
				continue;
			}

			for (int j = i + 1; j < (int)nums.size()-1; j++)
			{
				sum1 = nums[i] + nums[j];

				if (sum1 > 0)
				{
					break;
				}

				if (j > i + 1 && nums[j] == nums[j - 1])
				{
					continue;
				}

				for (int k = j + 1; k < (int)nums.size(); k++)
				{
					if (k > j + 1 && nums[k] == nums[k - 1])
					{
						continue;
					}

					sum2 = sum1 + nums[k];

					if (sum2 > 0)
					{
						break;
					}
					else if (sum2 == 0)
					{
						vector<int> good;

						good.push_back(nums[i]);
						good.push_back(nums[j]);
						good.push_back(nums[k]);

						results.push_back(good);

						break;
					}
				}
			}
		}

		return results;
	}

	static void print(vector<vector<int>>& vectors)
	{
		bool firstNumber = true;

		printf("Total: %d\n", vectors.size());

		for (vector<vector<int>>::iterator it1 = vectors.begin(); it1 != vectors.end(); it1++)
		{
			firstNumber = true;

			printf("[");

			for (vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
			{
				if (firstNumber)
				{
					printf("%d", *it2);
					firstNumber = false;
				}
				else
				{
					printf(", %d", *it2);
				}
			}

			printf("]\n");
		}
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> s;

	s.push_back(-1);
	s.push_back(0);
	s.push_back(1);
	s.push_back(2);
	s.push_back(-1);
	s.push_back(-4);

	vector<vector<int>> r = Solution::threeSum(s);

	Solution::print(r);

	return 0;
}

