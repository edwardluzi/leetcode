// ConsoleApplication7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
	static vector<string> restoreIpAddresses(string s)
	{
		vector<string> results;

		for (int i = 1; i <= 3; i++)
		{
			Solution::append(results, restoreIpAddresses("", 0, s, i));
		}

		return results;
	}

	static vector<string> restoreIpAddresses(string prefix, int number, string s, int count)
	{
		vector<string> results;

		if (number < 4 && count <= (int)s.length() && (count == 1 || s[0] != '0'))
		{
			string token = s.substr(0, count);

			int value = atoi(token.c_str());

			if (value <= 255)
			{
				prefix.append(token);

				if (s.length() == count && number == 3)
				{
					results.push_back(prefix);
				}
				else
				{
					prefix.append(".");

					append(results, restoreIpAddresses(prefix, number + 1, s.substr(count), 1));
					append(results, restoreIpAddresses(prefix, number + 1, s.substr(count), 2));
					append(results, restoreIpAddresses(prefix, number + 1, s.substr(count), 3));
				}
			}
		}

		return results;
	}

	static void append(vector<string>& v1, vector<string> v2)
	{
		v1.insert(v1.begin(), v2.begin(), v2.end());
	}

	static void print(string name, vector<string>& vectors)
	{
		bool firstNumber = true;

		printf("%s: ", name.c_str());

		for (vector<string>::iterator it = vectors.begin(); it != vectors.end(); it++)
		{
			if (firstNumber)
			{
				printf("%s", (*it).c_str());
				firstNumber = false;
			}
			else
			{
				printf(", %s", (*it).c_str());
			}
		}

		printf("\n");
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> result = Solution::restoreIpAddresses("010010");

	Solution::print("Output", result);

	return 0;
}

