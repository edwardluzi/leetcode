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
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

class Solution
{
public:
	static int maxPoints(vector<Point>& points) 
	{
		if (points.size() <= 1)
		{
			return points.size();
		}

		int length = (int)points.size();
		unordered_map<string, unordered_set<int>> lines;

		bool vertical;
		double slope;
		double ordinate;
		string key;
		unordered_map<string, unordered_set<int>>::iterator it;

		for (int i = 0; i < length - 1; i++)
		{
			for (int j = i + 1; j < length; j++)
			{
				calculate(points[i], points[j], slope, ordinate, vertical);

				key = toString(slope, ordinate, vertical);

				it = lines.find(key);

				if (it == lines.end())
				{
					unordered_set<int> set;
					set.insert(i);
					set.insert(j);
					lines.insert(pair<string, unordered_set<int>>(key, set));
				}
				else
				{
					unordered_set<int>& set = (*it).second;

					if (set.find(i) == set.end())
					{
						set.insert(i);
					}

					if (set.find(j) == set.end())
					{
						set.insert(j);
					}
				}
			}
		}

		int max = 0;

		for (unordered_map<string, unordered_set<int>>::iterator it = lines.begin(); it != lines.end(); it++)
		{
			int size = (*it).second.size();

			if (size > max)
			{
				max = size;
			}
		}

		return max;
	}

	inline static string toString(double slope, double ordinate, bool vertical)
	{
		static char buffer[32];

		if (vertical)
		{
			sprintf_s(buffer, 32, "vertical, %.8f", ordinate);
		}
		else
		{
			sprintf_s(buffer, 32, "%.8f, %.8f", slope, ordinate);
		}

		return string(buffer);
	}

	inline static void calculate(const Point& p1, const Point& p2, double& slope, double & ordinate, bool& vertical)
	{
		if (p2.x == p1.x)
		{
			vertical = true;
			ordinate = p1.x;
		}
		else if (p2.y == p1.y)
		{
			vertical = false;
			slope = 0;
			ordinate = p2.y;
		}
		else
		{
			vertical = false;
			slope = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
			ordinate = p2.y - p2.x * slope;
		}
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

	int count = Solution::maxPoints(points);

	return 0;
}

