#include "stdafx.h"

#include <list>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#if VS2013
#define INT64 __int64
#else
#define INT64 long long
#endif

class Solution
{
private:

	unordered_map<size_t, vector<list<INT64>>> mNumbersCache;

public:
	vector<string> addOperators(string num, int target)
	{
		vector<string> results;

		if (num.length() > 0)
		{
			vector<list<INT64>> numbers;
			getNumbers(num, 0, numbers);

			for (auto n : numbers)
			{
				vector<string> sub;
				evaluate(n, target, sub);

				results.insert(results.end(), sub.begin(), sub.end());
			}
		}

		return results;
	}

	void getNumbers(string& num, size_t offset, vector<list<INT64>>& numbers)
	{
		unordered_map<size_t, vector<list<INT64>>>::iterator it = mNumbersCache.find(offset);

		if (it == mNumbersCache.end())
		{
			size_t length = num.length();
			size_t index = offset;

			for (; index < length - 1; index++)
			{
				vector<list<INT64>> subs;
				getNumbers(num, index + 1, subs);

				for (auto& v : subs)
				{
					v.insert(v.begin(), atoi(num.substr(offset, index - offset + 1).c_str()));
					numbers.push_back(v);
				}

				if (num[offset] == '0')
				{
					index = string::npos;
					break;
				}
			}

			if (index != string::npos)
			{
				numbers.push_back(list<INT64>(1, atol(num.substr(offset, index - offset + 1).c_str())));
			}

			mNumbersCache.insert(pair<size_t, vector<list<INT64>>>(offset, numbers));
		}
		else
		{
			numbers.insert(numbers.end(), it->second.begin(), it->second.end());
		}
	}

	void evaluate(list<INT64>& num, INT64 target, vector<string>& result)
	{
		if (num.size() == 1)
		{
			if (num.front() == target)
			{
				result.push_back(itoa(num.front()));
			}
		}
		else
		{
			list<INT64>::iterator it = num.begin();
			INT64 n = *it++;

			string prefix(itoa(n));

			evaluate(target, num, it, prefix, '+', 0, n, result);
			evaluate(target, num, it, prefix, '-', 0, n, result);
			evaluate(target, num, it, prefix, '*', 0, n, result);
		}
	}

	void evaluate(INT64 target, list<INT64>& num, list<INT64>::iterator it, string prefix, char op, INT64 sum, INT64 product, vector<string>& result)
	{
		INT64 n = *it++;

		prefix.push_back(op);
		prefix.append(itoa(n));

		switch (op)
		{
			case '+':
			{
						sum += product;
						product = n;
						break;
			}
			case '-':
			{
						sum += product;
						product = -n;
						break;
			}
			default:
			{
					   product *= n;
					   break;
			}
		}

		if (it == num.end())
		{
			sum += product;

			if (sum == target)
			{
				result.push_back(prefix);
			}
		}
		else
		{
			evaluate(target, num, it, prefix, '+', sum, product, result);
			evaluate(target, num, it, prefix, '-', sum, product, result);
			evaluate(target, num, it, prefix, '*', sum, product, result);
		}
	}

	inline const char* itoa(INT64 val)
	{
		static char buf[32] =
		{ 0 };

		int index = 30;

		if (val == 0)
		{
			buf[index] = '0';
			index--;
		}
		else
		{
			for (; val && index; --index, val /= 10)
			{
				buf[index] = "0123456789"[val % 10];
			}
		}

		return &buf[index + 1];
	}
};

void print(vector<vector<int>>& vectors)
{
	printf("Total: %d\n", (int)vectors.size());

	for (vector<vector<int>>::iterator it1 = vectors.begin(); it1 != vectors.end(); ++it1)
	{
		printf("[");

		vector<int>::iterator it2 = (*it1).begin();

		if (it2 != (*it1).end())
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

void test(const string& num, INT64 target, string* expected, int expectedSize)
{
	vector<string> expecteds(expected, expected + expectedSize);

	Solution s;

	vector<string> result = s.addOperators(num, target);

	printf(expecteds == result ? "Okay\n" : "Failed\n");
}

void test1()
{
	string expected[] = { "1+2+3", "1*2*3" };
	test("123", 6, expected, sizeof(expected) / sizeof(string));
}

void test2()
{
	string expected[] = { "2+3*2", "2*3+2" };
	test("232", 8, expected, sizeof(expected) / sizeof(string));
}

void test3()
{
	string expected[] = { "1*0+5", "10-5" };
	test("105", 5, expected, sizeof(expected) / sizeof(string));
}

void test4()
{
	string expected[] = { "0+0", "0-0", "0*0" };
	test("00", 0, expected, sizeof(expected) / sizeof(string));
}

void test5()
{
	test("3456237490", 9191, NULL, 0);
}

void test6()
{
	test("2147483648", -2147483648LL, NULL, 0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*test1();
	test2();
	test3();
	test4();
	test5();*/
	test6();

	return 0;
}
