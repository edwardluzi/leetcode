#include "stdafx.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Point
{
	int x;
	int y;
	Point() :
		x(0), y(0)
	{
	}
	Point(int a, int b) :
		x(a), y(b)
	{
	}
};

#if VS2013
#define INT64 __int64
#else
#define INT64 long long
#endif

class Solution
{
private:

	static const INT64 VERT = (INT64)0x7FFFFFFFFFFFFFFF;

public:
	static int maxPoints(vector<Point>& points)
	{
		if (points.size() <= 2)
		{
			return points.size();
		}

		int length = (int)points.size();

		int max = 0;
		int same = 0;
		INT64 slope = 0;
		unordered_map<INT64, int> lines;

		for (int i = 0; i < length - 1; i++)
		{
			for (int j = i + 1; j < length; j++)
			{
				if (calculate(points[i], points[j], slope))
				{
					++lines[slope];
				}
				else
				{
					same++;
				}
			}

			if (lines.size() > 0)
			{
				for (auto& line : lines)
				{
					max = (line.second + same) > max ? (line.second + same) : max;
				}
			}
			else
			{
				max = same > max ? same : max;
			}

			lines.clear();
			same = 0;
		}

		return max + 1;
	}

	inline static bool calculate(const Point& p1, const Point& p2, INT64& slope)
	{
		if (p2.x == p1.x && p2.y == p1.y)
		{
			return false;
		}
		else if (p2.x == p1.x)
		{
			slope = true;
		}
		else if (p2.y == p1.y)
		{
			slope = VERT;
		}
		else
		{
			slope = (INT64)(((float)(p2.y - p1.y) / (float)(p2.x - p1.x)) * 100000000);
		}

		return true;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	vector<Point> points;

	points.push_back(Point(0, 0));
	points.push_back(Point(1, 1));
	points.push_back(Point(2, 2));
	points.push_back(Point(3, 3));
	points.push_back(Point(2, 3));
	points.push_back(Point(1, 3));

	int max = Solution::maxPoints(points);

	printf(max == 4 ? "Okay\n" : "Failed\n");

	points.clear();

	points.push_back(Point(0, 0));
	points.push_back(Point(0, 0));
	points.push_back(Point(0, 0));

	max = Solution::maxPoints(points);

	printf(max == 3 ? "Okay\n" : "Failed\n");

	return 0;
}
