
#pragma once

#include "shape.h"

#include "shape_all.h"

namespace Shape
{
	class Rectangle : public Shape
	{
		friend class Point;
		friend class Circle;
		friend class Line;

	public:
		Rectangle();
		Rectangle(int x, int y, int width, int height);
		Rectangle(const Rectangle& rhs);
		~Rectangle();

		const Rectangle& operator =(const Rectangle& rhs);

		bool IsCollide(const Point& rhs) const;
		bool IsCollide(const Circle& rhs) const;
		bool IsCollide(const Rectangle& rhs) const;
		bool IsCollide(const Line& rhs) const;		//–¢ŽÀ‘•

		void Set(int x, int y, int width, int height);
		void SetX(int value);
		void SetY(int value);
		void SetWidth(int value);
		void SetHeight(int value);
		int GetX() const;
		int GetY() const;
		int GetWidth() const;
		int GetHeight() const;

	private:
		void adjustSize();

		int x, y;
		int width, height;
	};
}
