#include "stdafx.h"

class Solution
{
public:
	static bool isPowerOfTwo(int n)
	{
		return (n > 0) && (n & (n - 1)) == 0;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	printf(Solution::isPowerOfTwo(1) ? "Okay\n" : "Failed");
	printf(Solution::isPowerOfTwo(2) ? "Okay\n" : "Failed");
	printf(!Solution::isPowerOfTwo(6) ? "Okay\n" : "Failed");
	printf(Solution::isPowerOfTwo(8) ? "Okay\n" : "Failed");

	return 0;
}

