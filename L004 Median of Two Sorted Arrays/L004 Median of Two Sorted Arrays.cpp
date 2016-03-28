#include "stdafx.h"
#include <vector>

using namespace std;

class Solution
{
public:

	static double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
	{
		size_t total = nums1.size() + nums2.size();
		size_t mth = total / 2;
		size_t count = 1;

		if (mth * 2 == total)
		{
			mth--;
			count = 2;
		}

		vector<int> merged;

		size_t i = 0;
		size_t j = 0;
		size_t l1 = nums1.size();
		size_t l2 = nums2.size();

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

void test(int* anums1, int anumsLen1, int* anums2, int anumsLen2)
{
	vector<int> nums1(anums1, anums1 + anumsLen1);
	vector<int> nums2(anums2, anums2 + anumsLen2);

	double m = Solution::findMedianSortedArrays(nums1, nums2);

	printf("%f\n", m);

}

int _tmain(int argc, _TCHAR* argv[])
{
	int nums1[] = { 1, 2, 3 };
	int nums2[] = { 3, 4, 5, 6 };

	test(nums1, sizeof(nums1) / sizeof(int), nums2, sizeof(nums2) / sizeof(int));

	int nums3[] = { 3, 4, 5, 6, 7 };

	test(nums1, sizeof(nums1) / sizeof(int), nums3, sizeof(nums3) / sizeof(int));

	return 0;
}