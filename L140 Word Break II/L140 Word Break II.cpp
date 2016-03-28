#include "stdafx.h"
#include "../StopWatch.h"

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
	unordered_map<char, TrieNode*> nexts;
	TrieNode() :
		isWord(false)
	{
	}
};

class Solution
{
private:

	vector<vector<size_t>> mSentences;
	unordered_map<size_t, vector<pair<size_t, size_t>>> mCache;

public:
	vector<string> wordBreak(string s, unordered_set<string>& wordDict)
	{
		vector<string> result;

		if (s.length() > 0 && wordDict.size() > 0)
		{
			mSentences.clear();
			mCache.clear();

			TrieNode rootNode;
			buildTrieTree(&rootNode, wordDict);

			vector<size_t> prefix;
			wordBreak(s, 0, &rootNode, prefix);

			convert(s, mSentences, result);
		}

		return result;
	}

	void wordBreak(const string& s, size_t offset, TrieNode* rootNode, vector<size_t>& prefix)
	{
		if (!hitCache(offset, prefix))
		{
			size_t baseline = mSentences.size();

			pair<size_t, TrieNode*> word = peekWord(s, offset, rootNode);

			while (word.second != NULL)
			{
				if (word.first >= s.length() - 1)
				{
					prefix.push_back(word.first);
					mSentences.push_back(prefix);
					prefix.pop_back();

					break;
				}
				else
				{
					prefix.push_back(word.first);
					wordBreak(s, word.first + 1, rootNode, prefix);
					prefix.pop_back();

					if (word.second->nexts.size() > 0)
					{
						word = peekWord(s, word.first + 1, word.second);
					}
					else
					{
						break;
					}
				}
			}

			updateCache(offset, baseline, prefix.size());
		}
	}

	inline pair<size_t, TrieNode*> peekWord(const string& s, size_t offset, TrieNode* parentNode)
	{
		size_t length = s.length();
		unordered_map<char, TrieNode*>::iterator it;

		while (offset < length)
		{
			it = parentNode->nexts.find(s[offset]);

			if (it == parentNode->nexts.end())
			{
				return pair<size_t, TrieNode*>(0, NULL);
			}
			else if (it->second->isWord)
			{
				return pair<size_t, TrieNode*>(offset, it->second);
			}

			offset++;
			parentNode = it->second;
		}

		return pair<size_t, TrieNode*>(0, NULL);
	}

	inline bool hitCache(size_t offset, vector<size_t>& prefix)
	{
		unordered_map<size_t, vector<pair<size_t, size_t>>>::iterator it = mCache.find(offset);

		if (it != mCache.end())
		{
			size_t original = prefix.size();

			vector<pair<size_t, size_t>>& content = it->second;

			for (vector<pair<size_t, size_t>>::iterator sit = content.begin(); sit != content.end(); ++sit)
			{
				vector<size_t>& match = mSentences[sit->first];
				prefix.insert(prefix.end(), match.begin() + sit->second, match.end());
				mSentences.push_back(prefix);
				prefix.erase(prefix.begin() + original, prefix.end());
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	inline void updateCache(size_t offset, size_t baseline, size_t position)
	{
		size_t current = mSentences.size();
		vector<pair<size_t, size_t>>content;

		for (size_t i = baseline; i < current; i++)
		{
			content.push_back(pair<size_t, size_t>(i, position));
		}

		mCache.insert(pair<size_t, vector<pair<size_t, size_t>>>(offset, content));
	}

	void buildTrieTree(TrieNode* rootNode, const unordered_set<string>& words)
	{
		for (unordered_set<string>::const_iterator it = words.begin(); it != words.end(); ++it)
		{
			insertNode(rootNode, *it);
		}
	}

	void insertNode(TrieNode* rootNode, const string& s)
	{
		if (s.length() == 0)
		{
			return;
		}

		TrieNode* current = rootNode;

		for (string::const_iterator it = s.begin(); it != s.end(); ++it)
		{
			unordered_map<char, TrieNode*>& nexts = current->nexts;
			unordered_map<char, TrieNode*>::iterator nit = nexts.find(*it);

			if (nit == nexts.end())
			{
				TrieNode* newNode = new TrieNode();
				nexts.insert(pair<char, TrieNode*>(*it, newNode));
				current = newNode;
			}
			else
			{
				current = (*nit).second;
			}
		}

		current->isWord = true;
	}

	void convert(const string& s, vector<vector<size_t>>& vv, vector<string>& v)
	{
		for (vector<vector<size_t>>::iterator it = vv.begin(); it != vv.end(); ++it)
		{
			string ss = s;
			vector<size_t>::reverse_iterator sit = it->rbegin();

			if (sit != it->rend())
			{
				++sit;

				for (; sit != it->rend(); ++sit)
				{
					ss.insert(*sit + 1, 1, ' ');
				}

				v.push_back(ss);
			}
		}
	}
};

void print(vector<string>& vectors)
{
	for (vector<string>::iterator it = vectors.begin(); it != vectors.end(); ++it)
	{
		printf("%s\n", (*it).c_str());
	}
}

void test(string& s, string* words, int wordSize, size_t expected)
{
	unordered_set<string> wordDict(words, words + wordSize);
	Solution solution;
	vector<string> result = solution.wordBreak(s, wordDict);
	printf(result.size() == expected ? "Okay\n" : "Failed\n");
	print(result);
}

void test1()
{
	string words[] = { "cat", "cats", "and", "sand", "dog" };
	string s = "catsanddog";
	test(s, words, sizeof(words) / sizeof(string), 2);
}

void test2()
{
	string words[] = { "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa" };
	string s =
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	test(s, words, sizeof(words) / sizeof(string), 0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	StopWatch sw;

	sw.start();

	for (int i = 0; i < 10; i++)
	{
		test1();
		test2();
	}

	sw.stop();

	printf("%d\n", (int)sw.getElapsed());

	return 0;
}
