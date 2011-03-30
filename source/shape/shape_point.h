
#pragma once

#include "shape.h"

#include "shape_all.h"

namespace Shape
{
	class Point : public Shape
	{
		friend class Circle;
		friend class Rectangle;
		friend class Line;

	public:
		Point();
		Point(const Point& rhs);
		Point(int x, int y);
		virtual ~Point();

		const Point& operator =(const Point& rhs);

		bool IsCollide(const Point& rhs) const;
		bool IsCollide(const Circle& rhs) const;
		bool IsCollide(const Rectangle& rhs) const;
		bool IsCollide(const Line& rhs) const;		//–¢ŽÀ‘•

		void Set(int x, int y);
		void SetX(int value);
		void SetY(int value);
		int GetX() const;
		int GetY() const;

	private:
		int x, y;
	};
}
