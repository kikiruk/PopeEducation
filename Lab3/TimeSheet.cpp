#include "TimeSheet.h"
#include <cmath>

using namespace std;

namespace lab3
{
	TimeSheet::TimeSheet(const char* name, unsigned int maxEntries) :
		mName(name),
		mMax(maxEntries),
		mSize(0),
		mEntries(new int[maxEntries])
	{}

	TimeSheet::TimeSheet(const TimeSheet& copy) :
		mName(copy.mName),
		mMax(copy.mMax),
		mSize(copy.mSize),
		mEntries(new int[mMax])
	{
		memcpy(mEntries, copy.mEntries, sizeof(copy.mEntries));
	}

	const TimeSheet& TimeSheet::operator=(const TimeSheet& ather)
	{
		if (this != &ather) //Prevent yourself from being assigned
		{
			mName = ather.mName;
			mMax = ather.mMax;
			mSize = ather.mSize;
			mEntries = new int[mMax];
			memcpy(mEntries, ather.mEntries, sizeof(ather.mEntries));
		}

		return *this;
	}



	TimeSheet::~TimeSheet()
	{
		delete[] mEntries;
	}

	void TimeSheet::AddTime(int timeInHours)
	{
		if (timeInHours <= 0 || timeInHours > 10 || mMax == mSize)
			return;

		mEntries[mSize++] = timeInHours;
	}

	int TimeSheet::GetTimeEntry(unsigned int index) const
	{
		if (index >= mSize)
			return -1;

		return mEntries[index];
	}

	int TimeSheet::GetTotalTime() const
	{
		size_t totalTime = 0;

		for (size_t i = 0; i < mSize; i++)
		{
			totalTime += mEntries[i];
		}

		return totalTime;
	}

	float TimeSheet::GetAverageTime() const
	{
		return static_cast<float>(GetTotalTime()) / static_cast<float>(mSize);
	}

	float TimeSheet::GetStandardDeviation() const
	{
		float average = GetAverageTime();
		float standardDeviation = 0;

		for (size_t i = 0; i < mSize; i++)
		{
			standardDeviation += pow(mEntries[i] - average,2);
		}

		return sqrt(standardDeviation / mSize);
	}

	const std::string& TimeSheet::GetName() const
	{
		return mName;
	}
}