#include "stdafx.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution
{
public:

	static 	vector<string> fullJustify(vector<string>& words, int maxWidth)
	{
		vector<string> justified;
		
		if (words.size() > 0)
		{
			vector<string> lineWords;
			int lineLength = 0;

			for (vector<string>::iterator it = words.begin(); it != words.end(); it++)
			{
				if (canAddMore(lineWords, lineLength, *it, maxWidth))
				{
					lineWords.push_back(*it);
					lineLength += (*it).length();
				}
				else
				{
					justified.push_back(format(maxWidth, lineWords, lineLength));

					lineWords.clear();

					lineWords.push_back(*it);
					lineLength = (*it).length();
				}
			}

			vector<int> spaces(lineWords.size(), 1);
			justified.push_back(format(maxWidth, lineWords, spaces));
		}

		return justified;
	}

	static string format(int maxWidth, vector<string>& words, int length)
	{
		string text;

		if (words.size() == 1)
		{
			text = words[0];
			text.insert(text.end(), maxWidth - length,' ');
		}
		else
		{
			double avg = (float)(maxWidth - length) / (float)(words.size() - 1);
			int ravg = round(avg);

			if (ravg * (words.size() - 1) == maxWidth - length)
			{
				vector<int> spaces(words.size(), ravg);
				text = format(maxWidth, words, spaces);
			}
			else
			{
				int num = round((avg - (int)avg) * (words.size() - 1));

				vector<int> spaces(num, ceil(avg));
				spaces.insert(spaces.end(), words.size() - num, (int)avg);
				text = format(maxWidth, words, spaces);
			}
		}

		return text;
	}

	static string format(int maxWidth, vector<string>& words, vector<int>& spaces)
	{
		string text;
		bool firstWord = true;

		vector<int>::iterator its = spaces.begin();

		for (vector<string>::iterator it = words.begin(); it != words.end(); it++)
		{
			if (firstWord)
			{
				text = *it;
				firstWord = false;
			}
			else
			{
				text.insert(text.end(), *its, ' ');
				text.insert(text.end(), (*it).begin(), (*it).end());

				its++;
			}
		}

		int length = text.length();

		if (length < maxWidth)
		{
			text.insert(text.end(), maxWidth - length, ' ');
		}

		return text;
	}

	inline static bool canAddMore(vector<string>& line, int lineLength, string& word, int maxWidth)
	{
		return lineLength + line.size() + word.length() <= maxWidth;
	}

	static void print(vector<string>& vectors)
	{
		for (vector<string>::iterator it = vectors.begin(); it != vectors.end(); it++)
		{
			printf("%s\n", (*it).c_str());
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	string ws[] = { "This", "is", "an", "example", "of", "text", "justification." };

	vector<string> words;

	for (int i = 0; i < sizeof(ws) / sizeof(string); i++)
	{
		words.push_back(ws[i]);
	}

	vector<string>  results = Solution::fullJustify(words, 16);

	Solution::print(results);

	return 0;
}

