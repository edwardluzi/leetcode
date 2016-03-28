#include "stdafx.h"

#include <string>
#include <list>

using namespace std;

class Solution
{
public:
	static bool isMatch(string s, string p)
	{
		int count = 0;
		bool begining = false;
		bool ending = false;

		list<string> elements = split(p, '*', count, begining, ending);

		if (count > 0)
		{
			if (elements.size() == 0)
			{
				return true;
			}

			return isMatch(s, elements, p, begining, ending);
		}
		else
		{
			return matchPart(s, 0, s.length(), p);
		}
	}

	static bool matchPart(const string& s, size_t start, size_t end, const string& p)
	{
		if (end - start != p.length())
		{
			return false;
		}
		else
		{
			for (; start < end; start++)
			{
				if (s[start] == p[start] || p[start] == '?')
				{
					continue;
				}

				return false;
			}

			return true;
		}
	}

	static bool isMatch(string& s, list<string>& elements, const string& p, bool beginingWithStar, bool endingWithStar)
	{
		if (!beginingWithStar && !matchBegining(s, elements, p))
		{
			return false;
		}

		if (elements.size() == 0)
		{
			return true;
		}

		if (!endingWithStar && !matchEnding(s, elements, p))
		{
			return false;
		}

		if (elements.size() == 0)
		{
			return true;
		}

		size_t offset = 0;

		for (list<string>::iterator it = elements.begin(); it != elements.end(); ++it)
		{
			if (!matchPart(s, offset, *it))
			{
				return false;
			}

			offset += it->length();
		}

		return true;
	}

	static bool matchPart(const string& s, size_t& offset, const string& p)
	{
		size_t patLength = p.length();
		size_t strLength = s.length();

		if (strLength - offset < patLength)
		{
			return false;
		}

		while (offset <= strLength - patLength)
		{
			bool match = true;

			for (size_t i = 0; i < patLength; i++)
			{
				if (s[offset + i] == p[i] || p[i] == '?')
				{
					continue;
				}

				match = false;
				break;
			}

			if (match)
			{
				return true;
			}
			else
			{
				offset++;
			}
		}

		return false;
	}

	static bool matchBegining(string& s, list<string>& elements, const string& p)
	{
		const string& first = elements.front();
		size_t firstLength = first.length();

		if (p.substr(0, firstLength) == first)
		{
			if (s.length() < firstLength)
			{
				return false;
			}

			for (size_t i = 0; i < firstLength; i++)
			{
				if (s[i] == first[i] || first[i] == '?')
				{
					continue;
				}

				return false;
			}

			s.erase(0, firstLength);
			elements.pop_front();
		}

		return true;
	}

	static bool matchEnding(string& s, list<string>& elements, const string& p)
	{
		const string& last = elements.back();
		size_t lastLength = last.length();

		if (p.substr(p.length() - lastLength, lastLength) == last)
		{
			size_t strLength = s.length();

			if (strLength < lastLength)
			{
				return false;
			}

			string suffix = s.substr(strLength - lastLength);

			for (size_t i = 0; i < lastLength; i++)
			{
				if (suffix[i] == last[i] || last[i] == '?')
				{
					continue;
				}

				return false;
			}

			s.erase(strLength - lastLength, lastLength);
			elements.pop_back();
		}

		return true;
	}

	static list<string> split(const string& s, const char delimiter, int& count, bool& beginingWithDelimiter,
		bool& endingWithDelimiter)
	{
		list<string> elements;
		size_t len = s.length();
		size_t start = 0;
		size_t end = s.find_first_of(delimiter);

		while (end != string::npos)
		{
			if (end == 0)
			{
				beginingWithDelimiter = true;
			}
			else if (end == len - 1)
			{
				endingWithDelimiter = true;
			}

			if (end > start)
			{
				elements.emplace_back(s.substr(start, end - start));
			}

			start = end + 1;
			end = s.find_first_of(delimiter, start);
			count++;
		}

		elements.emplace_back(s.substr(start, end - start));

		return elements;
	}
};

void test(string s, string p, bool expected)
{
	printf("%s, %s ==> %s\n", s.c_str(), p.c_str(), Solution::isMatch(s, p) == expected ? "Okay" : "Failed");
}

int _tmain(int argc, _TCHAR* argv[])
{
	test("b", "*a", false);
	test("b", "a*", false);
	test("b", "b", true);
	test("b", "*", true);
	test("abefcdgiescdfimde", "ab*cd?i*de", true);
	test("b", "*?*?", false);
	test("aa", "a", false);
	test("aa", "aa", true);
	test("aaa", "aa", false);
	test("aa", "*", true);
	test("aa", "**", true);
	test("ab", "?*", true);
	test("aab", "c*a*b", false);
	test("aab", "a*a*b", true);

	return 0;
}
