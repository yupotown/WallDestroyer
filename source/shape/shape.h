
#pragma once

namespace Shape
{
	class Point;
	class Circle;
	class Rectangle;
	class Line;

	class Shape
	{
	public:
		Shape();
		virtual ~Shape();

		virtual bool IsCollide(const Point& rhs) const = 0;
		virtual bool IsCollide(const Circle& rhs) const = 0;
		virtual bool IsCollide(const Rectangle& rhs) const = 0;
		virtual bool IsCollide(const Line& rhs) const = 0;
	};
}
