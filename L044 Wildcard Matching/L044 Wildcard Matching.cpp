#include "stdafx.h"

#include <string>
#include <sstream>;
#include <vector>

using namespace std;

class Solution
{
public:
	static bool isMatch(string s, string p) {

		bool match = true;

		if (p.find('*') == string::npos)
		{
			match = isMatch1(s, p);
		}
		else
		{
			match = isMatch2(s, p);
		}

		return match;
	}

	static bool isMatch1(const string& s, const string& p)
	{
		int length = s.length();

		if (length != p.length())
		{
			return false;
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				if (s[i] != p[i] && p[i] != '?')
				{
					return false;
				}
			}
		}

		return true;
	}

	static bool isMatch2(string s, const string& p)
	{
		vector<string> elements = split(p, '*');

		if (elements.size() == 00)
		{
			return true;
		}

		string::iterator its = s.begin();

		string& firstElement = elements[0];
		int firstLength = firstElement.length();

		if (p.substr(0, firstLength) == firstElement)
		{
			if (s.length() < firstLength)
			{
				return false;
			}

			for (int i = 0; i < firstLength; i++)
			{
				if (s[i] != firstElement[i] && firstElement[i] != '?')
				{
					return false;
				}
			}

			s = s.substr(firstLength);

			elements.erase(elements.begin());
		}

		if (elements.size() == 0)
		{
			return true;
		}

		string& lastElement = elements[elements.size() - 1];
		int lastLength = lastElement.length();

		if (p.substr(p.length() - lastLength, lastLength) == lastElement)
		{
			if (s.length() < lastLength)
			{
				return false;
			}

			string suffix = s.substr(s.length() - lastLength);

			for (int i = 0; i < lastLength; i++)
			{
				if (suffix[i] != lastElement[i] && lastElement[i] != '?')
				{
					return false;
				}
			}

			s = s.substr(0, s.length() - lastLength);
			elements.erase(elements.end() - 1);
		}

		if (elements.size() == 0)
		{
			return true;
		}

		int offset = 0;

		for (vector<string>::iterator it = elements.begin(); it != elements.end(); it++)
		{
			string& ss = *it;
			int length = ss.length();

			while (offset <= (int)s.length() - (int)ss.length())
			{
				bool match = true;

				for (int i = 0; i < length; i++)
				{
					if (s[offset + i] != ss[i] && ss[i] != '?')
					{
						match = false;
						break;
					}
				}

				if (match)
				{
					break;
				}
				else
				{
					offset++;
				}
			}


			if (offset > (int)s.length() - (int)ss.length())
			{
				return false;
			}

			offset += ss.length();
		}

		return true;
	}


	static vector<string> split(const string& s, char delim)
	{
		vector<string> elems;
		stringstream ss(s);
		string item;

		while (getline(ss, item, delim))
		{
			if (item.length() == 0)
			{
				continue;
			}

			elems.push_back(item);
		}

		return elems;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	Solution::isMatch("b", "*a*");

	Solution::isMatch("abefcdgiescdfimde", "ab*cd?i*de");



	Solution::isMatch("b", "*?*?");

	
	
	Solution::isMatch("aa", "a");
	Solution::isMatch("aa", "aa");
	Solution::isMatch("aaa", "aa");
	Solution::isMatch("aa", "*");
	Solution::isMatch("aa", "**");
	Solution::isMatch("ab", "?*");
	Solution::isMatch("aab", "c*a*b");
	Solution::isMatch("aab", "a*a*b");
	return 0;
}

