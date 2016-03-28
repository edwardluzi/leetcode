#include "stdafx.h"

#include <cstdio>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:

	static vector<string> fullJustify(vector<string>& words, int maxWidth)
	{
		vector<string> justified;

		if (words.size() > 0)
		{
			int length = 0;
			vector<string> line;

			for (vector<string>::iterator it = words.begin(); it != words.end(); ++it)
			{
				if (canAddMore(length, line.size(), it->length(), maxWidth))
				{
					line.push_back(*it);
					length += it->length();
				}
				else
				{
					justified.push_back(distribute(line, length, maxWidth));

					line.clear();
					line.push_back(*it);
					length = it->length();
				}
			}

			vector<int> spaces(line.size(), 1);
			justified.push_back(format(line, spaces, maxWidth));
		}

		return justified;
	}

	static string distribute(vector<string>& words, int length, int maxWidth)
	{
		string text;

		if (words.size() == 1)
		{
			text = words[0];
			text.insert(text.end(), maxWidth - length, ' ');
		}
		else
		{
			float avg = (float)(maxWidth - length) / (float)(words.size() - 1);
			int ravg = (int)round(avg);

			if (ravg * ((int)words.size() - 1) == maxWidth - length)
			{
				vector<int> spaces(words.size(), ravg);
				text = format(words, spaces, maxWidth);
			}
			else
			{
				int num = (int)round((avg - (int)avg) * (words.size() - 1));
				vector<int> spaces(num, (int)ceil(avg));
				spaces.insert(spaces.end(), words.size() - num, (int)avg);
				text = format(words, spaces, maxWidth);
			}
		}

		return text;
	}

	static string format(vector<string>& words, vector<int>& spaces, int maxWidth)
	{
		vector<string>::iterator itw = words.begin();
		vector<int>::iterator its = spaces.begin();
		string text = *itw;

		for (++itw; itw != words.end(); ++itw, ++its)
		{
			text.insert(text.end(), *its, ' ');
			text.insert(text.end(), itw->begin(), itw->end());
		}

		int length = text.length();

		if (length < maxWidth)
		{
			text.insert(text.end(), maxWidth - length, ' ');
		}

		return text;
	}

	inline static bool canAddMore(int length, int wordCout, int added, int maxWidth)
	{
		return length + wordCout + added <= maxWidth;
	}
};

void print(vector<string>& vectors)
{
	for (vector<string>::iterator it = vectors.begin(); it != vectors.end(); ++it)
	{
		printf("%s\n", (*it).c_str());
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	string ws[] = { "This", "is", "an", "example", "of", "text", "justification." };

	vector<string> words(ws, ws + sizeof(ws) / sizeof(string));

	vector<string> results = Solution::fullJustify(words, 16);

	print(results);

	return 0;
}
