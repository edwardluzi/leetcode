
#include "stdafx.h"
#include <vector>

using namespace std;

class Solution 
{
public:

	static double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
	{
		int total = (int)nums1.size() + (int)nums2.size();
		int mth = total / 2;
		int count = 1;

		if (mth * 2 == total)
		{
			mth--;
			count = 2;
		}

		vector<int> merged;

		int i = 0;
		int j = 0;
		int l1 = nums1.size();
		int l2 = nums2.size();

		while (i < l1 && j < l2 && merged.size() < mth + count)
		{
			if (nums1[i] <= nums2[j])
			{
				merged.push_back(nums1[i]);
				i++;
			}
			else
			{
				merged.push_back(nums2[j]);
				j++;
			}
		}

		if (merged.size() < mth + count)
		{
			if (i < l1)
			{
				merged.insert(merged.end(), nums1.begin() + i, nums1.end());
			}
			else if (j < l2)
			{
				merged.insert(merged.end(), nums2.begin() + j, nums2.end());
			}
		}

		if (count == 1)
		{
			return merged[mth];
		}
		else
		{
			return (double)(merged[mth] + merged[mth + 1]) / 2.0;
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> num1;
	vector<int> num2;

	num1.push_back(1);
	num1.push_back(2);
	num1.push_back(3);
	num2.push_back(3);
	num2.push_back(4);
	num2.push_back(5);
	num2.push_back(6);

	
	double d = Solution::findMedianSortedArrays(num1, num2);


	num2.push_back(7);

	d = Solution::findMedianSortedArrays(num1, num2);


	return 0;
}

