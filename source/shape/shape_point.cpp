
#include "shape_point.h"

namespace Shape
{
	Point::Point()
		:x(0), y(0)
	{
	}

	Point::Point(const Point& rhs)
		:x(rhs.x), y(rhs.y)
	{
	}

	Point::Point(int x, int y)
		:x(x), y(y)
	{
	}

	Point::~Point()
	{
	}

	const Point& Point::operator =(const Point& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}

	bool Point::IsCollide(const Point& rhs) const
	{
		return (rhs.x == this->x && rhs.y == this->y);
	}

	bool Point::IsCollide(const Circle& rhs) const
	{
		return (
			(this->x - rhs.x) * (this->x - rhs.x) +
			(this->y - rhs.y) * (this->y - rhs.y) <=
			(rhs.radius * rhs.radius)
			);
	}

	bool Point::IsCollide(const Rectangle& rhs) const
	{
		return (
			(this->x >= rhs.x) &&
			(this->y >= rhs.y) &&
			(this->x < rhs.x + rhs.width) &&
			(this->y < rhs.y + rhs.height)
			);
	}

	bool Point::IsCollide(const Line& rhs) const
	{
		return false;
	}

	void Point::Set(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void Point::SetX(int value)
	{
		this->x = value;
	}

	void Point::SetY(int value)
	{
		this->y = value;
	}

	int Point::GetX() const
	{
		return x;
	}

	int Point::GetY() const
	{
		return y;
	}
}
