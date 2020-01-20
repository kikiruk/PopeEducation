#pragma once
#include <string>

namespace lab3
{
	class TimeSheet
	{
	public:
		TimeSheet(const char* name, unsigned int maxEntries);
		TimeSheet(const TimeSheet& copy);
		TimeSheet& operator=(const TimeSheet& ather);
		~TimeSheet();

		void AddTime(int timeInHours);
		int GetTimeEntry(unsigned int index) const;
		inline int GetTotalTime() const;
		inline float GetAverageTime() const;
		inline float GetStandardDeviation() const;
		const std::string& GetName() const;
	private:
		std::string mName;
		size_t mMax;
		size_t mSize;
		int* mEntries;
	};

	//ERROR LNK1120
	inline int TimeSheet::GetTotalTime() const
	{
		size_t totalTime = 0;
	
		for (size_t i = 0; i < mSize; i++)
		{
			totalTime += mEntries[i];
		}
	
		return totalTime;
	}
	
	inline float TimeSheet::GetAverageTime() const
	{
		if (mSize == 0)
			return 0;

		return GetTotalTime() / static_cast<float>(mSize);
	}
	
	inline float TimeSheet::GetStandardDeviation() const
	{
		if (mSize == 0)
			return 0.0f;
	
		float average = GetAverageTime();
		float standardDeviation = 0;
	
		for (size_t i = 0; i < mSize; i++)
		{
			standardDeviation += static_cast<float>(pow(mEntries[i] - static_cast<double>(average), 2));
		}
	
		return static_cast<float>(sqrt(standardDeviation / mSize));
	}
}