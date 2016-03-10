#include "stdafx.h"

#include <vector>
#include <stack>
#include <string>
#include <numeric>
#include <algorithm>
#include <fstream>

using namespace std;

class Solution
{
public:
	static string shortestPalindrome(string s)
	{
		if (s.length() == 0)
		{
			return s;
		}

		string reversed = s;

		reverse(reversed.begin(), reversed.end());

		vector<int> table;

		buildTable(s, table);

		int position = search(reversed, s, table);

		return reversed.substr(0, position).append(s);
	}

	static void print(string name, vector<int>& vectors)
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

	static void buildTable(const string& pattern, vector<int>& table)
	{
		table.resize(pattern.length() + 1, 0);

		table[0] = -1;

		for (int i = 0; i < (int)pattern.length(); i++)
		{
			table[i + 1] = table[i] + 1;

			while (table[i + 1] > 0 && pattern[i] != pattern[table[i + 1] - 1])
			{
				table[i + 1] = table[table[i + 1] - 1] + 1;
			}
		}
	}

	static int search(const string& text, const string& pattern, vector<int>& table)
	{
		int i = 0;
		int j = 0;

		while (i < (int)text.length())
		{
			if (j < 0 || text[i] == pattern[j])
			{
				++i, ++j;
			}
			else
			{
				j = table[j];
			}
		}

		return i - j;
	}
};

void test(string s)
{
	printf("Original  : %s\n", s.c_str());
	printf("Palindrome: %s\n", Solution::shortestPalindrome(s).c_str());
}

int _tmain(int argc, _TCHAR* argv[])
{
	test("");
	test("abacab");
	test("aacecaaa");
	test("abcd");
	test("abbacd");
	test("3211234");
	test(string(40014, 'a'));
	test(string(40015, 'a'));

	return 0;
}
