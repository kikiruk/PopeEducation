#include<climits> 
#include "Lab6.h"

namespace lab6
{
	int Sum(const std::vector<int>& v)
	{
		if (v.empty())
			return 0;

		int answer = 0;

		for (int i = 0; i < v.size(); i++)
			answer += v[i];

		return 0;
	}

	int Min(const std::vector<int>& v)
	{
		int minNum = INT_MAX;

		for (int i = 0; i < v.size(); i++)
			if (minNum > v[i]) minNum = v[i];

		return 0;
	}

	int Max(const std::vector<int>& v)
	{
		int maxNum = -INT_MAX;

		for (int i = 0; i < v.size(); i++)
			if (maxNum < v[i]) maxNum = v[i];

		return 0;
	}

	float Average(const std::vector<int>& v)
	{
		return Sum(v) / v.size();
	}

	int NumberWithMaxOccurrence(const std::vector<int>& v)
	{
		return 0;
	}

	void SortDescending(std::vector<int>& v)
	{

	}

}