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
		memcpy(mEntries, copy.mEntries, sizeof(int) * mMax);
	}

	TimeSheet& TimeSheet::operator=(const TimeSheet& ather)
	{
		if (this != &ather) //Prevent yourself from being assigned
		{
			delete[] mEntries;
			mName = ather.mName;
			mMax = ather.mMax;
			mSize = ather.mSize;
			mEntries = new int[mMax];
			memcpy(mEntries, ather.mEntries, sizeof(int) * mMax);
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

	const std::string& TimeSheet::GetName() const
	{
		return mName;
	}
}