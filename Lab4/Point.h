#pragma once

namespace lab4
{
	class Point
	{
		friend Point operator*(float operand, const Point& operand2);
		friend class PolyLine;

	public:
		Point(float x, float y);
		Point(const Point& other);
		~Point() = default;
		Point() = delete;

		Point operator+(const Point& other) const;
		Point operator-(const Point& other) const;
		Point operator*(float operand) const;
		float Dot(const Point& other) const;

		inline float GetX() const;
		inline float GetY() const;

	private:
		float mX;
		float mY;
	};

	inline float Point::GetX() const
	{
		return mX;
	}

	inline float Point::GetY() const
	{
		return mY;
	}
}
