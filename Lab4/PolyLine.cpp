#include <cstring>
#include <cmath>
#include <cfloat>
#include "PolyLine.h"

namespace lab4
{
	PolyLine::PolyLine() :
		mSize(0)
	{
	}

	PolyLine::PolyLine(const PolyLine& other) :
		mSize(other.mSize)
	{
		for (size_t i = 0; i < other.mSize; i++)
		{
			mPoints[i] = new Point(*(other.mPoints[i]));
		}
	}

	PolyLine::~PolyLine()
	{
		for (size_t i = 0; i < mSize; i++)
		{
			delete mPoints[i];
		}
	}

	bool PolyLine::AddPoint(float x, float y)
	{
		if (mSize == PointMax)
			return false;

		mPoints[mSize++] = new Point(x, y);

		return true;
	}

	bool PolyLine::AddPoint(const Point* point)
	{
		if (mSize == PointMax)
			return false;

		mPoints[mSize++] = point;

		return true;
	}

	bool PolyLine::RemovePoint(unsigned int i)
	{
		if (i >= mSize)
			return false;

		delete mPoints[i];
		memcpy(mPoints + i, mPoints + i + 1, sizeof(Point*) * (mSize - i - 1));
		mSize--;

		return true;
	}

	bool PolyLine::TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const
	{
		if (mSize < 2)
			return false;

		float minX = FLT_MAX;
		float minY = FLT_MAX;
		float maxX = -FLT_MAX;
		float maxY = -FLT_MAX;

		float mX = 0;
		float mY = 0;
		for (size_t i = 0; i < mSize; i++)
		{
			mX = mPoints[i]->mX;
			mY = mPoints[i]->mY;

			if (mX < minX)
				minX = mX;

			if (mY < minY)
				minY = mY;

			if (mX > maxX)
				maxX = mX;

			if (mY > maxY)
				maxY = mY;
		}

		if (minX == maxX || minY == maxY)
			return false;

		outMin->mX = minX;
		outMin->mY = minY;
		outMax->mX = maxX;
		outMax->mY = maxY;

		return true;
	}

	const Point& PolyLine::operator=(const PolyLine& other)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			delete mPoints[i];
		}

		for (size_t i = 0; i < other.mSize; i++)
		{
			mPoints[i] = new Point(*(other.mPoints[i]));
		}

		mSize = other.mSize;
	}

	const Point* PolyLine::operator[](unsigned int i) const
	{
		if (i >= mSize)
			return nullptr;

		return mPoints[i];
	}
}