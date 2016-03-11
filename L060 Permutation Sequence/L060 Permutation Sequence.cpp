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
		vector<int> permutation;

		for (int i = 1; i <= n; i++)
		{
			nums.push_back(i);
		}

		int index = 0;
		int fact = 0;

		for (int i = n; i >= 1; i--)
		{
			fact = factorial(i - 1);
			index = k / fact;

			k = k % fact;

			permutation.push_back(nums[index]);

			nums.erase(nums.begin() + index);
		}

		return toString(permutation);
	}

	static string toString(vector<int>& v)
	{
		char temp[16];
		string text;

		for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		{
			memset(temp, 0, sizeof(temp));

			text = text + __itoa(*it, 10);
		}

		return text;
	}

	inline static int factorial(int n)
	{
		int fact = 1;

		for (int i = n; i >= 1; i--)
		{
			fact *= i;
		}

		return fact;
	}

	static string __itoa(int val, int base)
	{
		static char buf[32] = { 0 };

		int index = 30;

		for (; val && index; --index, val /= base)
		{
			buf[index] = "0123456789abcdef"[val % base];
		}

		return &buf[index + 1];
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	string s;

	for (int i = 1; i <= 6; i++)
	{
		s = Solution::getPermutation(3, i);

		printf("%s\n", s.c_str());
	}

	return 0;
}

