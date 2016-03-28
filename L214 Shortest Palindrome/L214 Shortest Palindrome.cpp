#include "stdafx.h"

#include <algorithm>
#include <cstdio>
#include <iterator>
#include <string>
#include <vector>

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

		if (reversed == s)
		{
			return s;
		}

		vector<int> table;
		buildKmpTable(s, table);

		int position = search(reversed, s, table);

		return reversed.substr(0, position).append(s);
	}

	static void buildKmpTable(const string& w, vector<int>& t)
	{
		int pos = 2;
		int cnd = 0;
		int len = w.length();

		t.resize(len, 0);

		t[0] = -1;
		t[1] = 0;

		while (pos < len)
		{
			if (w[pos - 1] == w[cnd])
			{
				t[pos] = ++cnd;
				pos++;
			}
			else if (cnd > 0)
			{
				cnd = t[cnd];
			}
			else
			{
				t[pos] = 0;
				pos++;
			}
		}
	}

	static int search(const string& text, const string& pattern, vector<int>& table)
	{
		int i = 0;
		int j = 0;
		int l = (int)text.length();

		while (i < l)
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

void test(string s, string expected)
{
	string result = Solution::shortestPalindrome(s);
	printf("Original  : %s\n", s.c_str());
	printf("Palindrome: %s\n", result.c_str());
	printf(expected == result ? "Okay\n" : "Failed\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	test("", "");
	test("abacab", "bacabacab");
	test("aacecaaa", "aaacecaaa");
	test("abcd", "dcbabcd");
	test("abbacd", "dcabbacd");
	test("3211234", "43211234");
	test("aaa", "aaa");

	return 0;
}
