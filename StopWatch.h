#include "stdafx.h"
#include <ctime>

class StopWatch
{
private:

	clock_t mStart;
	clock_t mStop;

public:

	StopWatch() :
		mStart(0), mStop(0)
	{
	}

public:

	void start()
	{
		mStart = clock();
	}

	void stop()
	{
		mStop = clock();
	}

	void reset()
	{
		mStart = 0;
		mStop = 0;
	}

	clock_t getElapsed()
	{
		return mStop - mStart;
	}
};
