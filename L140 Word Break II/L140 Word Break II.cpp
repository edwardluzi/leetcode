#include "stdafx.h"

#include <algorithm>
#include <cstdio>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TrieNode
{
	bool isWord;
	string word;
	unordered_map<char, TrieNode*> nexts;
	TrieNode() :
		isWord(false)
	{
	}
};

class Solution
{
public:
	static vector<string> wordBreak(string s, unordered_set<string>& wordDict)
	{
		vector<string> result;

		if (s.length() > 0 && wordDict.size() > 0)
		{
			TrieNode rootNode;
			buildTrieTree(&rootNode, wordDict);

			vector<string> prefix;
			vector<vector<string>> matched;
			unordered_map<int, vector<pair<int, int>>> cache;

			wordBreak(s, 0, &rootNode, prefix, matched, cache);

			for (vector<vector<string>>::iterator it = matched.begin();
				it != matched.end(); it++)
			{
				string sentence;
				bool firstWord = true;

				for (vector<string>::iterator sit = it->begin();
					sit != it->end(); sit++)
				{
					if (firstWord)
					{
						sentence = *sit;
						firstWord = false;
					}
					else
					{
						sentence.push_back(' ');
						sentence.insert(sentence.end(), sit->begin(),
							sit->end());
					}
				}

				result.push_back(sentence);
			}
		}

		return result;
	}

	static void wordBreak(const string& s, int index, TrieNode* root,
		vector<string>& prefix, vector<vector<string>>& matched,
		unordered_map<int, vector<pair<int, int>>>& cache)
	{
		unordered_map<int, vector<pair<int, int>>>::iterator it = cache.find(index);

		if (it != cache.end())
		{
			vector<pair<int, int>>& v = it->second;

			for (vector<pair<int, int>>::iterator sit = v.begin(); sit != v.end(); sit++)
			{
				vector<string>& m = matched[sit->first];
				vector<string> temp = prefix;

				temp.insert(temp.end(), m.begin() + sit->second, m.end());

				matched.push_back(temp);
			}

			return;
		}

		int backup = index;
		int start = matched.size();

		TrieNode* wordNode = peekWord(s, index, root);

		while (wordNode != NULL)
		{
			if (index >= (int)s.length() - 1)
			{
				prefix.push_back(wordNode->word);
				matched.push_back(prefix);
				prefix.erase(prefix.end() - 1);

				break;
			}
			else
			{
				prefix.push_back(wordNode->word);
				wordBreak(s, index + 1, root, prefix, matched, cache);
				prefix.erase(prefix.end() - 1);

				if (wordNode->nexts.size() > 0)
				{
					index++;
					wordNode = peekWord(s, index, wordNode);
				}
				else
				{
					break;
				}
			}
		}

		int stop = matched.size();

		vector<pair<int, int>> v;

		for (int i = start; i < stop; i++)
		{
			v.push_back(pair<int, int>(i, prefix.size()));
		}

		cache.insert(pair<int, vector<pair<int, int>>>(backup, v));
	}

	static TrieNode* peekWord(const string& s, int& index, TrieNode* parentNode)
	{
		unordered_map<char, TrieNode*>::iterator it;

		while (index < (int)s.length())
		{
			it = parentNode->nexts.find(s[index]);

			if (it == parentNode->nexts.end())
			{
				return NULL;
			}

			if (it->second->isWord)
			{
				return it->second;
			}
			else
			{
				index++;
				parentNode = it->second;
			}
		}

		return NULL;
	}

	static void buildTrieTree(TrieNode* rootNode, const unordered_set<string>& words)
	{
		for (unordered_set<string>::const_iterator it = words.begin(); it != words.end(); it++)
		{
			insertNode(rootNode, *it);
		}
	}

	static void insertNode(TrieNode* rootNode, const string& s)
	{
		if (s.length() == 0)
		{
			return;
		}

		TrieNode* current = rootNode;

		for (string::const_iterator it = s.begin(); it != s.end(); it++)
		{
			unordered_map<char, TrieNode*>::iterator cit = current->nexts.find(*it);

			if (cit == current->nexts.end())
			{
				TrieNode* newNode = new TrieNode();

				current->nexts.insert(pair<char, TrieNode*>(*it, newNode));

				current = newNode;
			}
			else
			{
				current = (*cit).second;
			}
		}

		current->isWord = true;
		current->word = s;
	}

	static void print(vector<string>& vectors)
	{
		for (vector<string>::iterator it = vectors.begin(); it != vectors.end();
			it++)
		{
			printf("%s\n", (*it).c_str());
		}
	}
};

void test2(string)
{
	string list2[] = { "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa" };

	unordered_set<string> dict(list2, list2 + sizeof(list2) / sizeof(string));


	string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	vector<string> result = Solution::wordBreak(s, dict);

	Solution::print(result);
}

int _tmain(int argc, _TCHAR* argv[])
{
	unordered_set<string> dict;
	vector<string> result;

	string list[] = { "cat", "cats", "and", "sand", "dog" };

	for (int i = 0; i < sizeof(list) / sizeof(string); i++)
	{
		dict.insert(list[i]);
	}

	result = Solution::wordBreak("catsanddog", dict);

	Solution::print(result);



	return 0;
}