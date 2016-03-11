
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
	bool a = Solution::isPowerOfTwo(1);
	a = Solution::isPowerOfTwo(2);
	a = Solution::isPowerOfTwo(6);
	a = Solution::isPowerOfTwo(8);

	return 0;
}

