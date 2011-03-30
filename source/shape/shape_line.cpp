
#include "shape_line.h"

namespace Shape
{
	Line::Line()
	{
	}

	Line::Line(const Line& rhs)
	{
		p[0] = rhs.p[0];
		p[1] = rhs.p[1];
	}

	Line::~Line()
	{
	}

	const Line& Line::operator =(const Line& rhs)
	{
		p[0] = rhs.p[0];
		p[1] = rhs.p[1];
		return *this;
	}

	bool Line::IsCollide(const Point& rhs) const
	{
		return rhs.IsCollide(*this);
	}

	bool Line::IsCollide(const Circle& rhs) const
	{
		return rhs.IsCollide(*this);
	}

	bool Line::IsCollide(const Rectangle& rhs) const
	{
		return rhs.IsCollide(*this);
	}

	bool Line::IsCollide(const Line& rhs) const
	{
		//X座標ラフチェック
		if (this->p[0].x > this->p[1].x)
		{
			if (
				(rhs.p[0].x > this->p[0].x && rhs.p[1].x > this->p[0].x) ||
				(rhs.p[0].x < this->p[1].x && rhs.p[1].x < this->p[1].x)
				)
			{
				return false;
			}
		}
		else
		{
			if (
				(rhs.p[0].x < this->p[0].x && rhs.p[1].x < this->p[0].x) ||
				(rhs.p[0].x > this->p[1].x && rhs.p[1].x > this->p[1].x)
				)
			{
				return false;
			}
		}

		//Y座標ラフチェック
		if (this->p[0].y > this->p[1].y)
		{
			if (
				(rhs.p[0].y > this->p[0].y && rhs.p[1].y > this->p[0].y) ||
				(rhs.p[0].y < this->p[1].y && rhs.p[1].y < this->p[1].y)
				)
			{
				return false;
			}
		}
		else
		{
			if (
				(rhs.p[0].y < this->p[0].y && rhs.p[1].y < this->p[0].y) ||
				(rhs.p[0].y > this->p[1].y && rhs.p[1].y > this->p[1].y)
				)
			{
				return false;
			}
		}

		//交差判定
		if (
			(
				(this->p[0].x - this->p[1].x) * (rhs.p[0].y - this->p[0].y) +
				(this->p[0].y - this->p[1].y) * (this->p[0].x - rhs.p[0].x)
			) *
			(
				(this->p[0].x - this->p[1].x) * (rhs.p[1].y - this->p[0].y) +
				(this->p[0].y - this->p[1].y) * (this->p[0].x - rhs.p[1].x)
			) > 0
		)
		{
			return false;
		}
		if (
			(
				(rhs.p[0].x - rhs.p[1].x) * (this->p[0].y - rhs.p[0].y) +
				(rhs.p[0].y - rhs.p[1].y) * (rhs.p[0].x - this->p[0].x)
			) *
			(
				(rhs.p[0].x - rhs.p[1].x) * (this->p[1].y - rhs.p[0].y) +
				(rhs.p[0].y - rhs.p[1].y) * (rhs.p[0].x - this->p[1].x)
			)
		)
		{
			return false;
		}

		return true;
	}
}
