#include<climits> 
#include<climits> 
#include "Lab6.h"

namespace lab6
{
	int Sum(const std::vector<int>& v)
	{
		if (v.empty())
			return 0;

		int answer = 0;

		for (unsigned int i = 0; i < v.size(); i++)
			answer += v[i];

		return answer;
	}

	int Min(const std::vector<int>& v)
	{
		int minNum = INT_MAX;

		for (unsigned int i = 0; i < v.size(); i++)
		{
			if (minNum > v[i])
				minNum = v[i];
		}

		return minNum;
	}

	int Max(const std::vector<int>& v)
	{
		int maxNum = INT_MIN;

		for (unsigned int i = 0; i < v.size(); i++)
		{
			if (maxNum < v[i])
				maxNum = v[i];
		}

		return maxNum;

	}

	float Average(const std::vector<int>& v)
	{
		if (v.empty())
			return 0.0f;

		return static_cast<float>(Sum(v)) / v.size();
	}

	int NumberWithMaxOccurrence(const std::vector<int>& v)
	{
		int answer = 0;
		int numberNow = 0;
		int numberCount = 0;
		int maxCount = 0;
		
		for (auto i = v.begin(); i != v.end(); i++)
		{
			numberNow = *i;
			for (auto j = i + 1; j != v.end(); j++)
			{
				if (numberNow == *j)
					numberCount++;
			}
			
			if (maxCount < numberCount)
			{
				maxCount = numberCount;
				answer = numberNow;
			}
		}
		
		return answer;
	}

	void SortDescending(std::vector<int>& v)
	{
		quickSort(0, v.size() - 1, v);
	}

	void quickSort(int left, int right, std::vector<int>& v)
	{
		int pivot = left;
		int j = pivot;
		int i = left + 1;
		int tmp;
	
		if (left < right) 
		{
			for (; i <= right; i++) 
			{
				if (v[i] > v[pivot]) 
				{
					j++;
					tmp = v[j];
					v[j] = v[i];
					v[i] = tmp;
				}
			}
			tmp = v[left];
			v[left] = v[j];
			v[j] = tmp;
			pivot = j;
	
			quickSort(left, pivot - 1, v);
			quickSort(pivot + 1, right, v);
		}
	}
}