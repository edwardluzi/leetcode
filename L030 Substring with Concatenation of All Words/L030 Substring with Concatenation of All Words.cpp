#include "stdafx.h"
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution
{
public:
	static vector<int> findSubstring(string s, vector<string>& words)
	{
		vector<int> positions;

		if (s.length() > 0 && words.size() > 0)
		{
			unordered_map<string, int> indices;
			buildIndices(words, indices);

			int pos = 0;
			int wordLen = words[0].length();
			int subLen = wordLen * words.size();

			for (; pos <= (int)s.length() - subLen;)
			{
				pos = findSubstring(s, pos, wordLen, subLen, words, indices);

				if (pos == -1)
				{
					break;
				}

				positions.push_back(pos);
				pos++;
			}
		}

		return positions;
	}

	static int findSubstring(string& s, int start, int wordLen, int subLen,
		vector<string>& words, unordered_map<string, int>& indices)
	{
		int candidate = peekWord(s, start, wordLen, true, indices);

		if (candidate == -1)
		{
			return -1;
		}

		int found = 1;
		string word = s.substr(candidate, wordLen);
		int count = words.size();
		int next = candidate + wordLen;

		unordered_map<string, int> copy;
		unordered_map<string, int>::iterator it;

		copy.insert(indices.begin(), indices.end());
		copy.find(word)->second--;

		while (found < count)
		{
			next = peekWord(s, next, wordLen, false, indices);

			if (next >= 0)
			{
				word = s.substr(next, wordLen);

				it = copy.find(word);

				if (it != copy.end() && it->second > 0)
				{
					it->second--;
					found++;
					next += wordLen;

					continue;
				}
			}

			if (candidate + 1 > (int)s.length() - subLen)
			{
				return -1;
			}

			candidate = peekWord(s, candidate + 1, wordLen, true, indices);

			if (candidate == -1)
			{
				return -1;
			}

			word = s.substr(candidate, wordLen);

			copy.clear();
			copy.insert(indices.begin(), indices.end());
			copy.find(word)->second--;

			found = 1;

			next = candidate + wordLen;
		}

		return found == count ? candidate : -1;
	}

	inline static int peekWord(const string& s, int start, int wordLen,
		bool forward, const unordered_map<string, int>& indices)
	{
		int last = s.length() - wordLen;

		while (start <= last)
		{
			if (indices.find(s.substr(start, wordLen)) != indices.end())
			{
				return start;
			}

			if (forward)
			{
				start++;
			}
			else
			{
				return -1;
			}
		}

		return -1;
	}

	inline static void buildIndices(vector<string>& words,
		unordered_map<string, int>& indices)
	{
		for (string& w : words)
		{
			++indices[w];
		}
	}
};

void test(string& str, string* word, int wordSize, int* expected,
	int expectedSize)
{
	vector<string> words(word, word + wordSize);
	vector<int> expecteds(expected, expected + expectedSize);

	vector<int> result = Solution::findSubstring(str, words);

	printf(result == expecteds ? "Okay\n" : "Failed\n");
}

void test1()
{
	string words[] = { "foo", "bar" };
	int expected[] = { 0, 9 };
	string str = "barfoothefoobarman";

	test(str, words, sizeof(words) / sizeof(string), expected,
		sizeof(expected) / sizeof(int));
}

void test2()
{
	string words[] = { "foo", "bar" };
	int expected[] = { 0, 12 };
	string str = "barfoothefoofoobarmanfooddc";

	test(str, words, sizeof(words) / sizeof(string), expected,
		sizeof(expected) / sizeof(int));
}

void test3()
{
	string words[] = { "bar", "foo", "the" };
	int expected[] = { 6, 9, 12 };
	string str = "barfoofoobarthefoobarman";

	test(str, words, sizeof(words) / sizeof(string), expected,
		sizeof(expected) / sizeof(int));
}

void test4()
{
	string words[] = { "word", "good", "best", "good" };
	int expected[] = { 8 };
	string str = "wordgoodgoodgoodbestword";

	test(str, words, sizeof(words) / sizeof(string), expected,
		sizeof(expected) / sizeof(int));
}

void test5()
{
	string words[] = { "aa", "cc", "ca" };
	int expected[] = { 3 };
	string str = "acccaccaa";

	test(str, words, sizeof(words) / sizeof(string), expected,
		sizeof(expected) / sizeof(int));
}

void test6()
{
	string words[] = { "ab", "ba", "ba" };
	int expected[] = { 1 };
	string str = "ababaab";

	test(str, words, sizeof(words) / sizeof(string), expected,
		sizeof(expected) / sizeof(int));
}

void test7()
{
	string words[] =
	{ 
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
		"a", "a", "a", "a", "a", "a", "a" 
	};
	
	string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	test(str, words, sizeof(words) / sizeof(string), NULL, 0);
}

void test8()
{
	string words[] =
	{ 
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab",
		"ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab",
		"ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab",
		"ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab",
		"ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab",
		"ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab",
		"ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab",
		"ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab",
		"ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
		"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba", "ab",
		"ba" 
	};
	string str = "abababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababab";

	test(str, words, sizeof(words) / sizeof(string), NULL, 0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();

	return 0;
}