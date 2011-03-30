
#pragma once

#include "shape.h"

#include "shape_all.h"

namespace Shape
{
	class Line : public Shape
	{
		friend class Point;
		friend class Circle;
		friend class Rectangle;

	public:
		Line();
		Line(const Line& rhs);
		~Line();

		const Line& operator =(const Line& rhs);

		bool IsCollide(const Point& rhs) const;
		bool IsCollide(const Circle& rhs) const;
		bool IsCollide(const Rectangle& rhs) const;
		bool IsCollide(const Line& rhs) const;

	private:
		Point p[2];
	};
}
