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
		int maxNum = -INT_MAX;

		for (unsigned int i = 0; i < v.size(); i++)
		{
			if (maxNum < v[i])
				maxNum = v[i];
		}

		return maxNum;
	}

	float Average(const std::vector<int>& v)
	{
		return static_cast<float>(Sum(v)) / v.size();
	}

	int NumberWithMaxOccurrence(const std::vector<int>& v)
	{
		//std::vector<int> tmp(v);
		//SortDescending(tmp);
		//
		//int answer = v[0];
		//int maxCount = 1;
		//int numberNow = v[0];
		//int numberCount = 1;
		//
		//for (unsigned int i = 1; i < tmp.size(); i++)
		//{
		//	if (numberNow == v[i])
		//		numberCount++;
		//	else
		//	{
		//		if (maxCount < numberCount)
		//		{
		//			maxCount = numberCount;
		//			answer = numberNow;
		//		}
		//
		//		numberCount = 1;
		//		numberNow = v[i];
		//	}
		//}

		//return answer;
		return 0;
	}

	void SortDescending(std::vector<int>& v)
	{
		//quickSort(0, v.size() - 1, v);
	}

	//void quickSort(int left, int right, std::vector<int>& v)
	//{
	//	int pivot = left;
	//	int j = pivot;
	//	int i = left + 1;
	//	int tmp;
	//
	//	if (left < right) 
	//	{
	//		for (; i <= right; i++) 
	//		{
	//			if (v[i] > v[pivot]) 
	//			{
	//				j++;
	//				tmp = v[j];
	//				v[j] = v[i];
	//				v[i] = tmp;
	//			}
	//		}
	//		tmp = v[left];
	//		v[left] = v[j];
	//		v[j] = tmp;
	//		pivot = j;
	//
	//		quickSort(left, pivot - 1, v);
	//		quickSort(pivot + 1, right, v);
	//	}
	//}
}