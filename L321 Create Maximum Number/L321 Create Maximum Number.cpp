#include "stdafx.h"

#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

class IndexNode
{
public:

	int number;
	vector<int> pos1;
	vector<int> pos2;

public:

	IndexNode() :
		number(0)
	{
	}

	IndexNode(int n, int which, int pos) :
		number(n)
	{
		append(which, pos);
	}

	void append(int which, int pos)
	{
		if (which == 1)
		{
			pos1.push_back(pos);
		}
		else
		{
			pos2.push_back(pos);
		}
	}
};

class Solution
{
private:

	int mTotalSize;
	int mMaxNumber;
	vector<int> mNums1;
	vector<int> mNums2;
	unordered_map<int, IndexNode*> mIndices;
	unordered_map<string, vector<int>> mCache;

public:

	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k)
	{
		mNums1 = nums1;
		mNums2 = nums2;

		if ((int)mNums1.size() > k)
		{
			reduce(mNums1, k);
		}

		if ((int)mNums2.size() > k)
		{
			reduce(mNums2, k);
		}

		mTotalSize = mNums1.size() + mNums2.size();

		createIndices(mNums1, 1);
		createIndices(mNums2, 2);

		if (mIndices.size() == 1)
		{
			return vector<int>(k, mIndices.begin()->second->number);
		}

		mMaxNumber = 9;

		while (mIndices.find(mMaxNumber) == mIndices.end())
		{
			mMaxNumber--;
		}

		vector<int> result;

		maxNumber(result, 0, 0, k);

		freeIndices();

		return result;
	}

	void maxNumber(vector<int>& candidate, int start1, int start2, int k)
	{
		string key = makeKey(start1, start2, k);
		unordered_map<string, vector<int>>::iterator cit = mCache.find(key);

		if (cit != mCache.end())
		{
			candidate.insert(candidate.end(), cit->second.begin(),
				cit->second.end());
		}
		else
		{
			if (mTotalSize - start1 - start2 == k)
			{
				merge(candidate, start1, start2);

				mCache.insert(pair<string, vector<int>>(key, candidate));
			}
			else
			{
				int maxCandidateNumber = mMaxNumber;

				while (maxCandidateNumber >= 0)
				{
					unordered_map<int, IndexNode*>::iterator it = mIndices.find(
						maxCandidateNumber);

					while (it == mIndices.end())
					{
						if (--maxCandidateNumber < 0)
						{
							return;
						}

						it = mIndices.find(maxCandidateNumber);
					}

					IndexNode* indexNode = it->second;

					vector<int> candidate1;
					vector<int> candidate2;

					peek(candidate1, 1, indexNode, start1, start2, k);
					peek(candidate2, 2, indexNode, start1, start2, k);

					if ((int)candidate1.size() == k && (int)candidate2.size() == k)
					{
						vector<int>& v =
							candidate1 >= candidate2 ?
						candidate1 : candidate2;
						candidate.insert(candidate.end(), v.begin(), v.end());
					}
					else if ((int)candidate1.size() == k)
					{
						candidate.insert(candidate.end(), candidate1.begin(),
							candidate1.end());
					}
					else if ((int)candidate2.size() == k)
					{
						candidate.insert(candidate.end(), candidate2.begin(),
							candidate2.end());
					}
					else
					{
						maxCandidateNumber--;
						continue;
					}

					mCache.insert(pair<string, vector<int>>(key, candidate));

					break;
				}
			}
		}
	}

	inline void peek(vector<int>& candidate, int which, IndexNode* indexNode,
		int start1, int start2, int k)
	{
		int thisStart = which == 1 ? start1 : start2;
		int thatStart = which == 1 ? start2 : start1;
		vector<int>& position = (which == 1 ? indexNode->pos1 : indexNode->pos2);

		for (vector<int>::iterator it = position.begin(); it != position.end();
			it++)
		{
			if (*it < thisStart)
			{
				continue;
			}

			if (mTotalSize - (*it + thatStart) < k)
			{
				break;
			}

			candidate.push_back(indexNode->number);

			if (k - 1 > 0)
			{
				bool removed = false;
				int savedValue = *it;
				int savedPosition = it - position.begin();

				position.erase(it);

				if (indexNode->pos1.size() == 0 && indexNode->pos2.size() == 0)
				{
					removed = true;
					mIndices.erase(indexNode->number);
				}

				if (which == 1)
				{
					maxNumber(candidate, savedValue + 1, start2, k - 1);
				}
				else
				{
					maxNumber(candidate, start1, savedValue + 1, k - 1);
				}

				if (removed)
				{
					mIndices.insert(
						pair<int, IndexNode*>(indexNode->number,
						indexNode));
				}

				position.insert(position.begin() + savedPosition, savedValue);
			}

			break;
		}
	}

	void merge(vector<int>& merged, int start1, int start2)
	{
		int c = 0;

		while (start1 < (int)mNums1.size() && start2 < (int)mNums2.size())
		{
			c = mNums1[start1] - mNums2[start2];

			if (c > 0)
			{
				merged.push_back(mNums1[start1]);
				start1++;
			}
			else if (c < 0)
			{
				merged.push_back(mNums2[start2]);
				start2++;
			}
			else
			{
				int i = start1 + 1;
				int j = start2 + 1;

				if (select(mNums1[start1], i, j) == 1)
				{
					merged.push_back(mNums1[start1]);
					start1++;
				}
				else
				{
					merged.push_back(mNums2[start2]);
					start2++;
				}
			}
		}

		if (start1 < (int)mNums1.size())
		{
			merged.insert(merged.end(), mNums1.begin() + start1, mNums1.end());
		}
		else if (start2 < (int)mNums2.size())
		{
			merged.insert(merged.end(), mNums2.begin() + start2, mNums2.end());
		}
	}

	int select(int n, int& i, int& j)
	{
		int len1 = mNums1.size();
		int len2 = mNums2.size();
		int c = 0;

		for (; i < len1 && j < len2; i++, j++)
		{
			c = mNums1[i] - mNums2[j];

			if (c > 0)
			{
				return 1;
			}
			else if (c < 0)
			{
				return 2;
			}
			else if (mNums1[i] < n)
			{
				return 1;
			}
		}

		return (len1 - i) - (len2 - j) >= 0 ? 1 : 2;
	}

	void reduce(vector<int>& nums, int k)
	{
		vector<int>::iterator start = nums.begin();
		vector<int>::iterator selected;

		while ((int)nums.size() > k)
		{
			int maxNumber = -1;
			int count = nums.size() - k;

			for (vector<int>::iterator it = start;
				count >= 0 && it != nums.end(); it++, count--)
			{
				if (*it > maxNumber)
				{
					maxNumber = *it;
					selected = it;
				}
			}

			if (maxNumber == -1)
			{
				count = nums.size() - k;

				for (; count > 0; count--)
				{
					nums.pop_back();
				}

				break;
			}
			else if (selected == start)
			{
				start++;
			}
			else
			{
				start = nums.erase(start, selected);
			}
		}
	}

	void createIndices(vector<int>& nums, int which)
	{
		for (int i = 0; i < (int)nums.size(); i++)
		{
			unordered_map<int, IndexNode*>::iterator it = mIndices.find(
				nums[i]);

			if (it != mIndices.end())
			{
				it->second->append(which, i);
			}
			else
			{
				mIndices.insert(
					pair<int, IndexNode *>(nums[i],
					new IndexNode(nums[i], which, i)));
			}
		}
	}

	void freeIndices()
	{
		for (unordered_map<int, IndexNode*>::iterator it = mIndices.begin();
			it != mIndices.end(); it++)
		{
			delete it->second;
			it->second = NULL;
		}

		mIndices.clear();
	}

	static string makeKey(int i, int j, int k)
	{
		static char buffer[64];

#if VS2013
		sprintf_s(buffer, 63, "%d,%d,%d", i, j, k);
#else
		sprintf(buffer, "%d,%d,%d", i, j, k);
#endif
		return string(buffer);
	}
};

static void print(vector<int>& vectors)
{
	for (vector<int>::iterator it = vectors.begin(); it != vectors.end(); it++)
	{
		printf("%d", (*it));
	}

	printf("\n");
}

static void maxNumber(int* nums1, int* nums2, int* expected, int len1, int len2,
	int k)
{
	vector<int> result;
	vector<int> v1;
	vector<int> v2;

	v1.insert(v1.end(), nums1, nums1 + len1);
	v2.insert(v2.end(), nums2, nums2 + len2);

	print(v1);
	print(v2);

	Solution s;

	result = s.maxNumber(v1, v2, k);

	if ((int)result.size() != k)
	{
		printf("Error\n");
	}
	else if (expected != NULL)
	{
		bool okay = true;

		for (int i = 0; i < (int)result.size(); i++)
		{
			if (result[i] != expected[i])
			{
				okay = false;
				break;
			}
		}

		printf(okay ? "Okay\n" : "Error\n");
	}

	print(result);
}

static void maxNumber(int* nums1, int* nums2, int len1, int len2, int k)
{
	maxNumber(nums1, nums2, NULL, len1, len2, k);
}

void test0()
{
	int nums1[] = { 1, 1, 1, 1, 1, 1, 1 };
	int nums2[] = { 9, 1, 2, 5, 8, 3, 1 };
	int expected[] = { 9, 8, 3, 1, 1 };

	maxNumber(nums1, nums2, expected, sizeof(nums1) / sizeof(int),
		sizeof(nums2) / sizeof(int), 5);
}

void test1()
{
	int nums1[] = { 3, 4, 6, 5 };
	int nums2[] = { 9, 1, 2, 5, 8, 3 };
	int expected[] = { 9, 8, 6, 5, 3 };

	maxNumber(nums1, nums2, expected, sizeof(nums1) / sizeof(int),
		sizeof(nums2) / sizeof(int), 5);
}
void test2()
{
	int nums1[] = { 3, 9 };
	int nums2[] = { 8, 9 };
	int expected[] = { 9, 8, 9 };

	maxNumber(nums1, nums2, expected, sizeof(nums1) / sizeof(int),
		sizeof(nums2) / sizeof(int), 3);
}

void test3()
{
	int nums3[] = { 6, 7 };
	int nums4[] = { 6, 0, 4 };
	int expected[] = { 6, 7, 6, 0, 4 };

	maxNumber(nums3, nums4, expected, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 5);
}

void test31()
{
	int nums3[] = { 6, 7, 5 };
	int nums4[] = { 4, 8, 1 };
	int expected[] = { 8, 7, 5 };

	maxNumber(nums3, nums4, expected, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 3);
}

void test4()
{
	int nums3[] = { 2, 5, 6, 4, 4, 0 };
	int nums4[] = { 7, 3, 8, 0, 6, 5, 7, 6, 2 };
	int expected[] = { 7, 3, 8, 2, 5, 6, 4, 4, 0, 6, 5, 7, 6, 2, 0 };

	maxNumber(nums3, nums4, expected, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 15);
}

void test13()
{
	int nums3[] =
	{
		2, 1, 2, 1, 2, 2, 1, 2, 2, 1, 1, 2, 1, 0, 2, 0, 1, 0, 1, 1, 2, 0, 0, 2, 2,
		2, 2, 1, 1, 1, 2, 1, 2, 0, 2, 0, 1, 1, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1,
		1, 0, 0, 2, 0, 1, 1, 2, 0, 2, 2, 1, 2, 1, 2, 1, 0, 1, 2, 0, 2, 1, 2,
		2, 2, 0, 1, 1, 0, 2, 0, 1, 1, 0, 0, 0, 2, 1, 1, 1, 0, 1, 1, 0, 1, 2,
		1, 2, 0, 0, 0, 2, 1, 2, 2, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 2, 1, 1,
		0, 2, 0, 2, 2, 0, 2, 0, 0, 2, 0, 1, 2, 1, 1, 1, 2, 1, 0, 1, 1, 0, 2,
		1, 2, 2, 1, 0, 1, 1, 1, 2, 0, 2, 2, 2, 0, 2, 1, 1, 2, 1, 1, 2, 0, 2,
		1, 0, 2, 0, 0, 2, 2, 2, 0, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 1, 1, 2, 0,
		2, 0, 0, 2, 2, 2, 0, 2, 2, 1, 0, 0, 2, 2, 2, 1, 1, 0, 2, 1, 0, 1, 2,
		1, 1, 2, 2, 1, 1, 0, 2, 1, 2, 2, 1, 2, 1, 0, 0, 0, 0, 1, 1, 0, 2, 2,
		2, 2, 2, 2, 2, 2, 1, 1, 0, 2, 1, 0, 0, 0, 0, 2, 1, 1
	};
	int nums4[] =
	{
		1, 1, 0, 2, 0, 1, 1, 1, 0, 2, 2, 2, 1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 2, 2,
		2, 1, 1, 0, 2, 0, 1, 0, 0, 1, 1, 0, 1, 2, 1, 2, 1, 2, 0, 1, 1, 1, 1,
		2, 0, 1, 1, 1, 0, 0, 1, 0, 1, 2, 1, 1, 0, 2, 2, 1, 2, 0, 2, 0, 1, 1,
		2, 0, 1, 1, 2, 2, 1, 0, 1, 2, 2, 0, 1, 1, 2, 2, 0, 2, 2, 0, 2, 1, 0,
		0, 2, 1, 0, 0, 2, 1, 2, 1, 2, 0, 2, 0, 1, 1, 2, 1, 1, 1, 2, 0, 2, 2,
		0, 2, 2, 0, 2, 1, 2, 1, 2, 0, 2, 0, 0, 1, 2, 2, 2, 2, 1, 2, 2, 0, 1,
		0, 0, 2, 2, 2, 2, 0, 1, 0, 2, 1, 2, 2, 2, 1, 1, 1, 1, 2, 0, 0, 1, 0,
		0, 2, 2, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 2, 2, 2, 2, 2, 1, 0, 2, 2, 0,
		0, 1, 0, 0, 1, 1, 1, 2, 2, 0, 0, 2, 0, 0, 0, 1, 2, 0, 2, 0, 1, 2, 0,
		1, 2, 0, 1, 1, 0, 0, 1, 2, 1, 0, 2, 1, 0, 1, 2, 0, 1, 1, 2, 1, 0, 2,
		1, 2, 1, 1, 0, 2, 2, 1, 0, 2, 1, 1, 1, 0, 0, 0, 1, 0
	};
	int expected[] =
	{
		2, 1, 2, 1, 2, 2, 1, 2, 2, 1, 1, 2, 1, 1, 1, 0, 2, 0, 2, 0, 1, 1, 1, 0, 2,
		2, 2, 1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 2, 2, 2, 1, 1, 0, 2, 0, 1, 0,
		1, 1, 2, 0, 1, 0, 0, 2, 2, 2, 2, 1, 1, 1, 2, 1, 2, 0, 2, 0, 1, 1, 0,
		1, 0, 2, 0, 1, 0, 2, 0, 1, 1, 0, 0, 2, 0, 1, 1, 2, 0, 2, 2, 1, 2, 1,
		2, 1, 0, 1, 2, 0, 2, 1, 2, 2, 2, 0, 1, 1, 0, 2, 0, 1, 1, 0, 0, 1, 1,
		0, 1, 2, 1, 2, 1, 2, 0, 1, 1, 1, 1, 2, 0, 1, 1, 1, 0, 0, 1, 0, 1, 2,
		1, 1, 0, 2, 2, 1, 2, 0, 2, 0, 1, 1, 2, 0, 1, 1, 2, 2, 1, 0, 1, 2, 2,
		0, 1, 1, 2, 2, 0, 2, 2, 0, 2, 1, 0, 0, 2, 1, 0, 0, 2, 1, 2, 1, 2, 0,
		2, 0, 1, 1, 2, 1, 1, 1, 2, 0, 2, 2, 0, 2, 2, 0, 2, 1, 2, 1, 2, 0, 2,
		0, 0, 1, 2, 2, 2, 2, 1, 2, 2, 0, 1, 0, 0, 2, 2, 2, 2, 0, 1, 0, 2, 1,
		2, 2, 2, 1, 1, 1, 1, 2, 0, 0, 1, 0, 0, 2, 2, 1, 0, 0, 1, 1, 0, 0, 1,
		1, 0, 2, 2, 2, 2, 2, 1, 0, 2, 2, 0, 0, 1, 0, 0, 1, 1, 1, 2, 2, 0, 0,
		2, 0, 0, 0, 2, 1, 1, 1, 0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 2, 1, 2, 2,
		1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 2, 1, 1, 0, 2, 0, 2, 2, 0, 2, 0, 0,
		2, 0, 1, 2, 1, 1, 1, 2, 1, 0, 1, 1, 0, 2, 1, 2, 2, 1, 0, 1, 1, 1, 2,
		0, 2, 2, 2, 0, 2, 1, 1, 2, 1, 1, 2, 0, 2, 1, 0, 2, 0, 0, 2, 2, 2, 0,
		2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 1, 1, 2, 0, 2, 0, 0, 2, 2, 2, 0, 2, 2,
		1, 0, 0, 2, 2, 2, 1, 1, 0, 2, 1, 0, 1, 2, 1, 1, 2, 2, 1, 1, 0, 2, 1,
		2, 2, 1, 2, 1, 0, 0, 0, 1, 2, 0, 2, 0, 1, 2, 0, 1, 2, 0, 1, 1, 0, 0,
		1, 2, 1, 0, 2, 1, 0, 1, 2, 0, 1, 1, 2, 1, 0, 2, 1, 2, 1, 1, 0, 2, 2,
		1, 0, 2, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 2, 2, 2, 2, 2, 2,
		2, 2, 1, 1, 0, 2, 1, 0, 0, 0, 0, 2, 1, 1, 0
	};

	maxNumber(nums3, nums4, expected, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 500);
}

void test14()
{
	int nums1[] =
	{
		4, 6, 9, 1, 0, 6, 3, 1, 5, 2, 8, 3, 8, 8, 4, 7, 2, 0, 7, 1, 9, 9, 0, 1, 5,
		9, 3, 9, 3, 9, 7, 3, 0, 8, 1, 0, 9, 1, 6, 8, 8, 4, 4, 5, 7, 5, 2, 8,
		2, 7, 7, 7, 4, 8, 5, 0, 9, 6, 9, 2
	};
	int nums2[] =
	{
		9, 9, 4, 5, 1, 2, 0, 9, 3, 4, 6, 3, 0, 9, 2, 8, 8, 2, 4, 8, 6, 5, 4, 4, 2,
		9, 5, 0, 7, 3, 7, 5, 9, 6, 6, 8, 8, 0, 2, 4, 2, 2, 1, 6, 6, 5, 3, 6,
		2, 9, 6, 4, 5, 9, 7, 8, 0, 7, 2, 3
	};

	maxNumber(nums1, nums2, sizeof(nums1) / sizeof(int),
		sizeof(nums2) / sizeof(int), 60);
}

void test15()
{
	int nums3[] =
	{
		2, 0, 2, 1, 2, 2, 2, 2, 0, 1, 0, 0, 2, 0, 2, 0, 2, 1, 0, 1, 1, 0, 1, 0, 1,
		2, 1, 1, 1, 0, 1, 2, 2, 1, 0, 0, 1, 2, 1, 2, 2, 1, 1, 0, 1, 2, 0, 2,
		0, 1, 2, 0, 2, 1, 1, 1, 2, 0, 0, 1, 0, 2, 1, 2, 0, 1, 0, 0, 0, 1, 2,
		1, 0, 1, 1, 2, 0, 2, 2, 0, 0, 1, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 2, 0,
		1, 2, 2, 0, 0, 0, 2, 0, 2, 0, 2, 2, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0,
		2, 2, 2, 2, 0, 2, 0, 1, 0, 0, 2, 1, 0, 0, 2, 0, 2, 1, 1, 1, 1, 0, 1,
		2, 0, 2, 1, 0, 1, 1, 1, 0, 0, 2, 2, 2, 0, 2, 1, 1, 1, 2, 2, 0, 0, 2,
		2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 0, 0, 1, 0, 1, 1, 0, 0, 2, 1, 1, 2, 2,
		2, 1, 2, 2, 0, 0, 2, 1, 0, 2, 1, 2, 1, 1, 1, 0, 2, 0, 1, 1, 2, 1, 1,
		0, 0, 1, 0, 1, 2, 2, 2, 0, 2, 2, 1, 0, 1, 2, 1, 2, 0, 2, 2, 0, 1, 2,
		2, 1, 2, 2, 1, 1, 2, 2, 2, 2, 2, 1, 2, 0, 1, 1, 1, 2, 2, 2, 0, 2, 0,
		2, 0, 2, 1, 1, 0, 2, 2, 2, 1, 0, 2, 1, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 0, 2, 2, 2, 2, 1, 0, 2, 0, 1, 2, 0
	};
	int nums4[] =
	{
		1, 1, 1, 0, 0, 1, 1, 0, 2, 1, 0, 1, 2, 1, 0, 2, 2, 1, 0, 2, 0, 1, 1, 0, 0,
		2, 2, 0, 1, 0, 2, 0, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 2, 1, 0, 2,
		1, 1, 2, 1, 2, 2, 0, 2, 1, 0, 2, 0, 0, 2, 0, 2, 2, 1, 0, 1, 0, 0, 2,
		1, 1, 1, 2, 2, 0, 0, 0, 1, 1, 2, 0, 2, 2, 0, 1, 0, 2, 1, 0, 2, 1, 1,
		1, 0, 1, 1, 2, 0, 2, 0, 1, 1, 2, 0, 2, 0, 1, 2, 1, 0, 2, 0, 1, 0, 0,
		0, 1, 2, 1, 2, 0, 1, 2, 2, 1, 1, 0, 1, 2, 1, 0, 0, 1, 0, 2, 2, 1, 2,
		2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 2, 1, 0, 0, 1, 2, 0, 1, 1, 0, 1,
		0, 2, 2, 2, 1, 1, 0, 1, 1, 2, 1, 0, 2, 2, 2, 1, 2, 2, 2, 2, 0, 1, 1,
		0, 1, 2, 1, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 2, 1, 2, 1, 1, 0, 1, 2, 0,
		1, 2, 1, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 1, 2, 0, 1, 1, 1, 1, 0, 1, 2,
		2, 1, 0, 1, 2, 2, 1, 2, 2, 2, 0, 2, 0, 1, 1, 2, 0, 0, 2, 2, 0, 1, 0,
		2, 1, 0, 0, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 0, 0, 1, 2, 1, 1, 2, 0, 1,
		2, 1, 0, 2, 0, 0, 2, 1, 1, 0, 2, 1, 1, 2, 2, 0, 1, 0, 2, 0, 1, 0
	};

	maxNumber(nums3, nums4, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 600);
}

void test16()
{
	int nums3[] =
	{
		1, 2, 0, 1, 1, 2, 1, 0, 2, 0, 2, 1, 1, 1, 1, 0, 0, 2, 0, 0, 2, 1, 2, 1, 0,
		1, 1, 0, 1, 2, 1, 0, 2, 0, 0, 1, 0, 1, 2, 0, 0, 0, 1, 1, 2, 1, 1, 1,
		0, 0, 0, 0, 1, 2, 1, 2, 1, 1, 1, 2, 2, 2, 1, 2, 2, 0, 2, 0, 0, 0, 2,
		1, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 1, 1, 0, 0, 2, 1, 1, 1, 0, 1,
		1, 1, 1, 2, 1, 0, 0, 1, 1, 1, 2, 1, 1, 1, 0, 0, 0, 2, 2, 2, 1, 2, 0,
		0, 1, 1, 2, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 2, 2, 0, 1, 1, 1, 1, 2, 0,
		2, 2, 1, 0, 2, 0, 1, 0, 1, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 1, 1, 0, 1,
		2, 2, 2, 1, 2, 0, 0, 1, 2, 2, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 2, 2,
		1, 2, 1, 2, 0, 0, 2, 0, 2, 1, 1, 1, 2, 0, 0, 1, 1, 1, 2, 1, 1, 1, 2,
		2, 1, 2, 2, 2, 0, 0, 2, 2, 0, 1, 0, 0, 0, 1, 1, 2, 2, 2, 0, 0, 1, 2,
		0, 0, 2, 2, 1, 0, 2, 1, 0, 0, 0, 0, 1, 0, 2, 1, 0, 1, 2, 1, 1, 0, 1,
		2, 1, 2, 0, 1, 1, 2, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1,
		2, 0, 2, 2, 0, 2, 1, 0, 2, 1, 0, 0, 0, 2, 2, 2, 0, 1, 1, 1, 2, 0, 2,
		1, 0, 2, 2, 0, 1, 1, 0, 1, 2, 2, 0, 2, 2, 0, 1, 0, 2, 0, 1, 1, 1, 0,
		1, 2, 2, 0, 1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 2, 1, 1, 0, 0, 0, 2, 2,
		1, 1, 2, 1, 2, 0, 2, 0, 1, 0, 1, 1, 0, 0, 0, 2, 1, 0, 0, 1, 1, 0, 1,
		0, 0, 1, 1, 0, 1, 1, 2, 0, 0, 0, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 0, 0,
		1, 0, 0, 2, 1, 2, 2
	};
	int nums4[] =
	{
		2, 1, 2, 1, 0, 0, 0, 1, 2, 1, 0, 1, 1, 2, 1, 2, 1, 1, 2, 0, 0, 0, 1, 0, 1,
		0, 2, 0, 1, 2, 0, 2, 0, 1, 2, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 2, 2, 2,
		1, 2, 1, 0, 2, 0, 0, 2, 0, 2, 0, 1, 2, 1, 0, 1, 1, 2, 0, 0, 2, 0, 2,
		2, 2, 2, 1, 2, 1, 2, 1, 1, 0, 0, 1, 2, 2, 2, 1, 1, 1, 1, 1, 0, 1, 0,
		0, 1, 1, 1, 0, 0, 2, 0, 1, 1, 1, 2, 1, 1, 0, 0, 0, 0, 1, 1, 1, 2, 0,
		2, 2, 2, 0, 2, 2, 0, 1, 2, 0, 1, 0, 0, 1, 1, 0, 1, 2, 0, 1, 1, 2, 2,
		1, 1, 0, 2, 1, 0, 2, 2, 0, 1, 2, 1, 1, 2, 1, 0, 2, 2, 1, 1, 1, 1, 1,
		2, 1, 1, 0, 2, 0, 2, 2, 0, 2, 1, 0, 0, 1, 0, 0, 0, 2, 2, 2, 0, 2, 2,
		0, 0, 1, 1, 1, 0, 0, 2, 2, 1, 1, 2, 0, 1, 0, 2, 1, 1, 1, 0, 1, 2, 0,
		2, 2, 1, 1, 0, 0, 2, 1, 1, 2, 1, 1, 0, 1, 1, 0, 2, 1, 0, 2, 2, 2, 1,
		0, 1, 2, 1, 0, 2, 1, 1, 1, 1, 1, 2, 1, 0, 2, 1, 0, 2, 2, 2, 1, 1, 2,
		1, 1, 1, 2, 2, 0, 0, 2, 0, 0, 0, 2, 2, 2, 1, 2, 2, 2, 2, 2, 0, 1, 1,
		0, 2, 1, 2, 2, 2, 1, 0, 2, 2, 2, 0, 1, 1, 0, 1, 1, 0, 2, 1, 1, 2, 1,
		0, 2, 2, 1, 2, 2, 0, 1, 1, 2, 1, 0, 0, 2, 2, 2, 1, 2, 1, 0, 1, 1, 2,
		0, 2, 0, 0, 2, 0, 2, 0, 0, 1, 0, 0, 1, 0, 1, 0, 2, 2, 1, 1, 2, 0, 2,
		1, 2, 0, 1, 2, 1, 0, 0, 2, 1, 2, 2, 1, 0, 0, 2, 2, 1, 2, 2, 1, 1, 2,
		0, 2, 1, 2, 2, 1, 0, 1, 2, 0, 1, 0, 1, 1, 0, 2, 0, 1, 2, 2, 1, 2, 0,
		1, 2, 0, 1, 1, 0, 2
	};

	maxNumber(nums3, nums4, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 800);
}

void test17()
{
	int nums3[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
	};
	int nums4[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
	};

	maxNumber(nums3, nums4, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 300);
}

void test18()
{
	int nums3[] =
	{
		8, 9, 7, 3, 5, 9, 1, 0, 8, 5, 3, 0, 9, 2, 7, 4, 8, 9, 8, 1, 0, 2, 0, 2, 7,
		2, 3, 5, 4, 7, 4, 1, 4, 0, 1, 4, 2, 1, 3, 1, 5, 3, 9, 3, 9, 0, 1, 7,
		0, 6, 1, 8, 5, 6, 6, 5, 0, 4, 7, 2, 9, 2, 2, 7, 6, 2, 9, 2, 3, 5, 7,
		4, 7, 0, 1, 8, 3, 6, 6, 3, 0, 8, 5, 3, 0, 3, 7, 3, 0, 9, 8, 5, 1, 9,
		5, 0, 7, 9, 6, 8, 5, 1, 9, 6, 5, 8, 2, 3, 7, 1, 0, 1, 4, 3, 4, 4, 2,
		4, 0, 8, 4, 6, 5, 5, 7, 6, 9, 0, 8, 4, 6, 1, 6, 7, 2, 0, 1, 1, 8, 2,
		6, 4, 0, 5, 5, 2, 6, 1, 6, 4, 7, 1, 7, 2, 2, 9, 8, 9, 1, 0, 5, 5, 9,
		7, 7, 8, 8, 3, 3, 8, 9, 3, 7, 5, 3, 6, 1, 0, 1, 0, 9, 3, 7, 8, 4, 0,
		3, 5, 8, 1, 0, 5, 7, 2, 8, 4, 9, 5, 6, 8, 1, 1, 8, 7, 3, 2, 3, 4, 8,
		7, 9, 9, 7, 8, 5, 2, 2, 7, 1, 9, 1, 5, 5, 1, 3, 5, 9, 0, 5, 2, 9, 4,
		2, 8, 7, 3, 9, 4, 7, 4, 8, 7, 5, 0, 9, 9, 7, 9, 3, 8, 0, 9, 5, 3, 0,
		0, 3, 0, 4, 9, 0, 9, 1, 6, 0, 2, 0, 5, 2, 2, 6, 0, 0, 9, 6, 3, 4, 1,
		2, 0, 8, 3, 6, 6, 9, 0, 2, 1, 6, 9, 2, 4, 9, 0, 8, 3, 9, 0, 5, 4, 5,
		4, 6, 1, 2, 5, 2, 2, 1, 7, 3, 8, 1, 1, 6, 8, 8, 1, 8, 5, 6, 1, 3, 0,
		1, 3, 5, 6, 5, 0, 6, 4, 2, 8, 6, 0, 3, 7, 9, 5, 5, 9, 8, 0, 4, 8, 6,
		0, 8, 6, 6, 1, 6, 2, 7, 1, 0, 2, 2, 4, 0, 0, 0, 4, 6, 5, 5, 4, 0, 1,
		5, 8, 3, 2, 0, 9, 7, 6, 2, 6, 9, 9, 9, 7, 1, 4, 6, 2, 8, 2, 5, 3, 4,
		5, 2, 4, 4, 4, 7, 2, 2, 5, 3, 2, 8, 2, 2, 4, 9, 8, 0, 9, 8, 7, 6, 2,
		6, 7, 5, 4, 7, 5, 1, 0, 5, 7, 8, 7, 7, 8, 9, 7, 0, 3, 7, 7, 4, 7, 2,
		0, 4, 1, 1, 9, 1, 7, 5, 0, 5, 6, 6, 1, 0, 6, 9, 4, 2, 8, 0, 5, 1, 9,
		8, 4, 0, 3, 1, 2, 4, 2, 1, 8, 9, 5, 9, 6, 5, 3, 1, 8, 9, 0, 9, 8, 3,
		0, 9, 4, 1, 1, 6, 0, 5, 9, 0, 8, 3, 7, 8, 5
	};
	int nums4[] =
	{
		7, 8, 4, 1, 9, 4, 2, 6, 5, 2, 1, 2, 8, 9, 3, 9, 9, 5, 4, 4, 2, 9, 2, 0, 5,
		9, 4, 2, 1, 7, 2, 5, 1, 2, 0, 0, 5, 3, 1, 1, 7, 2, 3, 3, 2, 8, 2, 0,
		1, 4, 5, 1, 0, 0, 7, 7, 9, 6, 3, 8, 0, 1, 5, 8, 3, 2, 3, 6, 4, 2, 6,
		3, 6, 7, 6, 6, 9, 5, 4, 3, 2, 7, 6, 3, 1, 8, 7, 5, 7, 8, 1, 6, 0, 7,
		3, 0, 4, 4, 4, 9, 6, 3, 1, 0, 3, 7, 3, 6, 1, 0, 0, 2, 5, 7, 2, 9, 6,
		6, 2, 6, 8, 1, 9, 7, 8, 8, 9, 5, 1, 1, 4, 2, 0, 1, 3, 6, 7, 8, 7, 0,
		5, 6, 0, 1, 7, 9, 6, 4, 8, 6, 7, 0, 2, 3, 2, 7, 6, 0, 5, 0, 9, 0, 3,
		3, 8, 5, 0, 9, 3, 8, 0, 1, 3, 1, 8, 1, 8, 1, 1, 7, 5, 7, 4, 1, 0, 0,
		0, 8, 9, 5, 7, 8, 9, 2, 8, 3, 0, 3, 4, 9, 8, 1, 7, 2, 3, 8, 3, 5, 3,
		1, 4, 7, 7, 5, 4, 9, 2, 6, 2, 6, 4, 0, 0, 2, 8, 3, 3, 0, 9, 1, 6, 8,
		3, 1, 7, 0, 7, 1, 5, 8, 3, 2, 5, 1, 1, 0, 3, 1, 4, 6, 3, 6, 2, 8, 6,
		7, 2, 9, 5, 9, 1, 6, 0, 5, 4, 8, 6, 6, 9, 4, 0, 5, 8, 7, 0, 8, 9, 7,
		3, 9, 0, 1, 0, 6, 2, 7, 3, 3, 2, 3, 3, 6, 3, 0, 8, 0, 0, 5, 2, 1, 0,
		7, 5, 0, 3, 2, 6, 0, 5, 4, 9, 6, 7, 1, 0, 4, 0, 9, 6, 8, 3, 1, 2, 5,
		0, 1, 0, 6, 8, 6, 6, 8, 8, 2, 4, 5, 0, 0, 8, 0, 5, 6, 2, 2, 5, 6, 3,
		7, 7, 8, 4, 8, 4, 8, 9, 1, 6, 8, 9, 9, 0, 4, 0, 5, 5, 4, 9, 6, 7, 7,
		9, 0, 5, 0, 9, 2, 5, 2, 9, 8, 9, 7, 6, 8, 6, 9, 2, 9, 1, 6, 0, 2, 7,
		4, 4, 5, 3, 4, 5, 5, 5, 0, 8, 1, 3, 8, 3, 0, 8, 5, 7, 6, 8, 7, 8, 9,
		7, 0, 8, 4, 0, 7, 0, 9, 5, 8, 2, 0, 8, 7, 0, 3, 1, 8, 1, 7, 1, 6, 9,
		7, 9, 7, 2, 6, 3, 0, 5, 3, 6, 0, 5, 9, 3, 9, 1, 1, 0, 0, 8, 1, 4, 3,
		0, 4, 3, 7, 7, 7, 4, 6, 4, 0, 0, 5, 7, 3, 2, 8, 5, 1, 4, 5, 8, 5, 6,
		7, 5, 7, 3, 3, 9, 6, 8, 1, 5, 1, 1, 1, 0, 3
	};

	maxNumber(nums3, nums4, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 500);
}

void test19()
{
	int nums3[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};
	int nums4[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	maxNumber(nums3, nums4, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 100);
}

void test11()
{
	int nums3[] = { 7, 9, 0, 4, 7, 0, 7, 1, 2, 9, 5 };
	int nums4[] = { 9, 1, 5, 8, 3, 9 };

	maxNumber(nums3, nums4, sizeof(nums3) / sizeof(int),
		sizeof(nums4) / sizeof(int), 17);
}

int _tmain(int argc, _TCHAR* argv[])
{
	test0();
	test1();
	test11();
	test2();
	test3();
	test31();
	test4();
	test13();
	test14();
	test15();
	test16();
	test17();
	test18();
	test19();

	return 0;
}
