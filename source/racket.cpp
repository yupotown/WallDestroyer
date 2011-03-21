
#include "racket.h"

namespace WallDestroyer
{
	Racket::Racket()
		:x(0), y(0),
		width(0), height(0),
		range_left(0), range_right(0), range_top(0), range_bottom(0)
	{
	}

	Racket::~Racket()
	{
	}

	void Racket::SetMovableRange(int left, int top, int right, int bottom)
	{
		if (left > right)
		{
			range_left = right;
			range_right = left;
		}
		else
		{
			range_left = left;
			range_right = right;
		}
		if (top > bottom)
		{
			range_top = bottom;
			range_bottom = top;
		}
		else
		{
			range_top = top;
			range_bottom = bottom;
		}
		adjustPosition();
	}

	void Racket::SetSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		adjustSize();
	}

	void Racket::MoveTo(int x, int y)
	{
		this->x = x;
		this->y = y;
		adjustPosition();
	}

	void Racket::Move(int x, int y)
	{
		this->x += x;
		this->y += y;
		adjustPosition();
	}

	int Racket::GetX() const
	{
		return x;
	}

	int Racket::GetY() const
	{
		return y;
	}

	int Racket::GetWidth() const
	{
		return width;
	}

	int Racket::GetHeight() const
	{
		return height;
	}

	int Racket::GetMovableRangeLeft() const
	{
		return range_left;
	}

	int Racket::GetMovableRangeRight() const
	{
		return range_right;
	}

	int Racket::GetMovableRangeTop() const
	{
		return range_top;
	}

	int Racket::GetMovableRangeBottom() const
	{
		return range_bottom;
	}

	void Racket::adjustPosition()
	{
		if (x < range_left)
		{
			x = range_left;
		}
		else if (x + width > range_right)
		{
			x = range_right - width;
		}
		if (y < range_top)
		{
			y = range_top;
		}
		else if (y + height > range_bottom)
		{
			y = range_bottom - height;
		}
	}

	void Racket::adjustSize()
	{
		if (width < 0)
		{
			width = 0;
		}
		else if (width > range_right - range_left)
		{
			width = range_right - range_left;
		}
		if (height < 0)
		{
			height = 0;
		}
		else if (height > range_bottom - range_top)
		{
			height = range_bottom - range_top;
		}
		adjustPosition();
	}
}
