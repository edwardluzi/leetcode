#include "stdafx.h"

#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:

	static vector<vector<int>> threeSum(vector<int>& nums)
	{
		vector<vector<int>> results;

		int sum1 = 0;
		int sum2 = 0;
		size_t size = nums.size();

		sort(nums.begin(), nums.end());

		for (size_t i = 0; i < size - 2; i++)
		{
			if (nums[i] > 0)
			{
				break;
			}

			if (i > 0 && nums[i] == nums[i - 1])
			{
				continue;
			}

			for (size_t j = i + 1; j < size - 1; j++)
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

				for (size_t k = j + 1; k < size; k++)
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
};

void print(vector<vector<int>>& vectors)
{
	printf("Total: %d\n", (int)vectors.size());

	for (vector<vector<int>>::iterator it1 = vectors.begin(); it1 != vectors.end(); ++it1)
	{
		printf("[");

		vector<int>::iterator it2 = (*it1).begin();

		if (it2 != it1->end())
		{
			printf("%d", *it2);

			++it2;
		}

		for (; it2 != (*it1).end(); ++it2)
		{
			printf(", %d", *it2);
		}

		printf("]\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nums[] = { -1, 0, 1, 2, -1, -4 };
	vector<int> v(nums, nums + sizeof(nums) / sizeof(int));
	vector<vector<int>> r = Solution::threeSum(v);
	print(r);

	return 0;
}
