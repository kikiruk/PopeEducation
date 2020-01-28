#include "Point.h"

namespace lab4
{
	Point::Point(float x, float y) :
		mX(x),
		mY(y)
	{
	}

	Point::Point(const Point& other) :
		mX(other.mX),
		mY(other.mY)
	{
	}

	Point::Point() : 
		mX(0),
		mY(0)
	{
	}

	Point Point::operator+(const Point& other) const
	{
		return Point(this->mX + other.mX, this->mY + other.mY);
	}

	Point Point::operator-(const Point& other) const
	{
		return Point(this->mX - other.mX, this->mY - other.mY);
	}

	float Point::Dot(const Point& other) const
	{
		return (this->mX * other.mX) + (this->mY * other.mY);
	}

	Point Point::operator*(float operand) const
	{
		return Point(this->mX * operand, this->mY * operand);
	}

	//This is not a member
	Point operator*(float operand, const Point& operand2)
	{
		return Point(operand2.mX * operand, operand2.mY * operand);
	}
}
