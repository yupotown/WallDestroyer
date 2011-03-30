
#include "shape_rectangle.h"

namespace Shape
{
	Rectangle::Rectangle()
		:x(0), y(0),
		width(0), height(0)
	{
	}

	Rectangle::Rectangle(const Rectangle& rhs)
		:x(rhs.x), y(rhs.y),
		width(rhs.width), height(rhs.height)
	{
	}

	Rectangle::Rectangle(int x, int y, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		adjustSize();
	}

	Rectangle::~Rectangle()
	{
	}

	const Rectangle& Rectangle::operator =(const Rectangle& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->width = rhs.width;
		this->height = rhs.height;
		return *this;
	}

	bool Rectangle::IsCollide(const Point& rhs) const
	{
		return rhs.IsCollide(*this);
	}

	bool Rectangle::IsCollide(const Circle& rhs) const
	{
		return rhs.IsCollide(*this);
	}

	bool Rectangle::IsCollide(const Rectangle& rhs) const
	{
		return (
			(this->x < rhs.x + rhs.width) &&
			(this->y < rhs.y + rhs.height) &&
			(rhs.x < this->x + this->width) &&
			(rhs.y < this->y + this->height)
			);
	}

	bool Rectangle::IsCollide(const Line& rhs) const
	{
		return false;
	}

	void Rectangle::Set(int x, int y, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		adjustSize();
	}

	void Rectangle::SetX(int value)
	{
		this->x = value;
	}

	void Rectangle::SetY(int value)
	{
		this->y = value;
	}

	void Rectangle::SetWidth(int value)
	{
		this->width = value;
		adjustSize();
	}

	void Rectangle::SetHeight(int value)
	{
		this->height = height;
		adjustSize();
	}

	int Rectangle::GetX() const
	{
		return x;
	}

	int Rectangle::GetY() const
	{
		return y;
	}

	int Rectangle::GetWidth() const
	{
		return width;
	}

	int Rectangle::GetHeight() const
	{
		return height;
	}

	void Rectangle::adjustSize()
	{
		if (width < 0)
		{
			width = 0;
		}
		if (height < 0)
		{
			height = 0;
		}
	}
}
