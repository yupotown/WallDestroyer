
#pragma once

#include "shape.h"

#include "shape_all.h"

namespace Shape
{
	class Circle : public Shape
	{
		friend class Point;
		friend class Rectangle;
		friend class Line;

	public:
		Circle();
		Circle(int x, int y, int radius);
		Circle(const Circle& rhs);
		~Circle();

		const Circle& operator =(const Circle& rhs);

		bool IsCollide(const Point& rhs) const;
		bool IsCollide(const Circle& rhs) const;
		bool IsCollide(const Rectangle& rhs) const;
		bool IsCollide(const Line& rhs) const;		//–¢ŽÀ‘•

		void Set(int x, int y, int radius);
		void SetX(int value);
		void SetY(int value);
		void SetRadius(int value);
		int GetX() const;
		int GetY() const;
		int GetRadius() const;

	private:
		void adjustRadius();

		int x, y;
		int radius;
	};
}
