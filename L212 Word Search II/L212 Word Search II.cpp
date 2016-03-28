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
	vector<TrieNode*> nexts;

	TrieNode() :
		isWord(false), nexts(26, NULL)
	{
	}
};

class Solution
{
public:
	static vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
	{
		vector<string> result;

		if (board.size() > 0 && board[0].size() > 0)
		{
			TrieNode rootNode;
			buildTrieTree(&rootNode, words);

			unordered_set<string> matched;
			findWords(board, &rootNode, matched);
			result.insert(result.end(), matched.begin(), matched.end());
			sort(result.begin(), result.end());
		}

		return result;
	}

	static void findWords(const vector<vector<char>>& board, TrieNode* rootNode, unordered_set<string>& matched)
	{
		size_t rows = board.size();
		size_t cols = board[0].size();

		for (size_t row = 0; row < rows; row++)
		{
			for (size_t col = 0; col < cols; col++)
			{
				vector<vector<bool>> visited(rows, vector<bool>(cols, false));
				findWords(board, rootNode, row, col, matched, visited);
			}
		}
	}

	static void findWords(const vector<vector<char>>& board, const TrieNode* parent, size_t row, size_t col,
		unordered_set<string>& matched, vector<vector<bool>>& visited)
	{
		TrieNode* nextNode = parent->nexts[board[row][col] - 'a'];

		if (nextNode == NULL)
		{
			return;
		}

		visited[row][col] = true;

		if (nextNode->isWord)
		{
			matched.insert(nextNode->word);
		}

		size_t rows = board.size();
		size_t cols = board[0].size();

		if (col >= 1 && !visited[row][col - 1])
		{
			findWords(board, nextNode, row, col - 1, matched, visited);
		}

		if (col + 1 < cols &&!visited[row][col + 1])
		{
			findWords(board, nextNode, row, col + 1, matched, visited);
		}

		if (row >= 1 && !visited[row - 1][col])
		{
			findWords(board, nextNode, row - 1, col, matched, visited);
		}

		if (row + 1 < rows&& !visited[row + 1][col])
		{
			findWords(board, nextNode, row + 1, col, matched, visited);
		}

		visited[row][col] = false;
	}

	static void buildTrieTree(TrieNode* rootNode, const vector<string>& words)
	{
		for (auto& s : words)
		{
			insertNode(rootNode, s);
		}
	}

	static void insertNode(TrieNode* rootNode, const string& s)
	{
		TrieNode* current = rootNode;

		for (auto& c : s)
		{
			int index = c - 'a';
			TrieNode* next = current->nexts[index];

			if (next == NULL)
			{
				TrieNode* newNode = new TrieNode();
				current->nexts[index] = newNode;
				current = newNode;
			}
			else
			{
				current = next;
			}
		}

		current->isWord = true;
		current->word = s;
	}
};

void print(vector<string>& vectors)
{
	for (vector<string>::iterator it = vectors.begin(); it != vectors.end(); ++it)
	{
		printf("%s\n", (*it).c_str());
	}
}

void test(string* board, int boardSize, string* word, int wordSize, string* expected, int expectedSize)
{
	vector<vector<char>> boards;

	for (int i = 0; i < boardSize; i++)
	{
		boards.push_back(vector<char>(board[i].begin(), board[i].end()));
	}

	vector<string> words(word, word + wordSize);
	vector<string> expecteds(expected, expected + expectedSize);

	vector<string> result = Solution::findWords(boards, words);

	printf(result == expecteds ? "Okay\n" : "Failed\n");
}

void test1()
{
	string bs[] = { "oaan", "etae", "ihkr", "iflv" };
	string ws[] = { "oath", "pea", "eat", "rain" };
	string ex[] = { "eat", "oath" };

	test(bs, sizeof(bs) / sizeof(string), ws, sizeof(ws) / sizeof(string), ex, sizeof(ex) / sizeof(string));
}

void test2()
{
	string bs[] = { "babba" };
	string ws[] = { "baa", "abba", "baab", "aba" };
	string ex[] = { "abba" };

	test(bs, sizeof(bs) / sizeof(string), ws, sizeof(ws) / sizeof(string), ex, sizeof(ex) / sizeof(string));
}

extern void test3();
extern void test4();

#include "../StopWatch.h"

int _tmain(int argc, _TCHAR* argv[])
{
	StopWatch sw;

	sw.start();

	test1();
	test2();
	test3();
	test4();

	sw.stop();

	printf("%d", (int)sw.getElapsed());

	return 0;
}
