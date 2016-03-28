#include "stdafx.h"

#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	static vector<string> restoreIpAddresses(string s)
	{
		vector<string> results;

		for (size_t i = 1; i <= 3; i++)
		{
			restoreIpAddresses(results, s, "", 0, i);
		}

		return results;
	}

	static void restoreIpAddresses(vector<string>& results, const string& s, string prefix, size_t octet, size_t digitCount)
	{
		if (digitCount <= s.length() && (s[0] != '0' || digitCount == 1))
		{
			string token = s.substr(0, digitCount);
			int value = atoi(token.c_str());

			if (value <= 255)
			{
				prefix.append(token);

				if (octet == 3)
				{
					if (s.length() == digitCount)
					{
						results.push_back(prefix);
					}
				}
				else
				{
					octet++;
					prefix.append(".");

					string remainder = s.substr(digitCount);

					for (size_t i = 1; i <= 3; i++)
					{
						restoreIpAddresses(results, remainder, prefix, octet, i);
					}
				}
			}
		}
	}
};

static void print(vector<string>& vectors)
{
	for (vector<string>::iterator it = vectors.begin(); it != vectors.end(); ++it)
	{
		printf("%s\n", (*it).c_str());
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> result = Solution::restoreIpAddresses("010010");

	print(result);

	return 0;
}

