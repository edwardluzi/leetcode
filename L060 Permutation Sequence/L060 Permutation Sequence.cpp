#include "stdafx.h"

#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	static string getPermutation(int n, int k)
	{
		if (n < 1 || k < 1)
		{
			return "";
		}

		k--;

		vector<int> nums;
		vector<int> facts;

		for (int i = 1; i <= n; i++)
		{
			nums.push_back(i);
		}

		calcFacts(facts, n);

		string result;
		char alphabet[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

		for (int i = n; i >= 1; i--)
		{
			int fact = facts[i - 1];
			int index = k / fact;

			result.push_back(alphabet[nums[index]]);
			nums.erase(nums.begin() + index);

			k = k % fact;
		}

		return result;
	}

	static inline const char* itoa(int val)
	{
		static char buf[32] = { 0 };

		int index = 30;

		for (; val && index; --index, val /= 10)
		{
			buf[index] = "0123456789"[val % 10];
		}

		return &buf[index + 1];
	}

	static inline void calcFacts(vector<int>& facts, int n)
	{
		int fact = 1;

		facts.push_back(1);

		for (int i = 1; i <= n; i++)
		{
			fact *= i;
			facts.push_back(fact);
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	string s;

	for (int i = 1; i <= 6; i++)
	{
		s = Solution::getPermutation(9, i);

		printf("%s\n", s.c_str());
	}

	return 0;
}
