
#include "ball.h"

#include <cmath>

namespace WallDestroyer
{
	Ball::Ball()
	{
	}

	Ball::~Ball()
	{
	}

	void Ball::Update()
	{
		calcSpeedXY();
		//debug
		x += vx;
		y += vy;
		adjustPosition();
	}

	void Ball::MoveTo(double x, double y)
	{
		this->x = x;
		this->y = y;
		adjustPosition();
	}

	void Ball::Move(double x, double y)
	{
		this->x += x;
		this->y += y;
		adjustPosition();
	}

	void Ball::SetMovableRange(int left, int top, int right, int bottom)
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

	void Ball::SetAngle(double angle)
	{
		this->angle = angle;
	}

	void Ball::SetSpeed(double speed)
	{
		this->speed = speed;
	}

	double Ball::GetX() const
	{
		return x;
	}

	double Ball::GetY() const
	{
		return y;
	}

	double Ball::GetAngle() const
	{
		return angle;
	}

	double Ball::GetSpeed() const
	{
		return speed;
	}

	double Ball::GetVx() const
	{
		return std::cos(angle) * speed;
	}

	double Ball::GetVy() const
	{
		return std::sin(angle) * speed;
	}

	void Ball::adjustSize()
	{
		if (radius < 0)
		{
			radius = 0;
		}
		else if (radius * 2 > range_right - range_left)
		{
			radius = (range_right - range_left) / 2;
		}
		adjustPosition();
	}

	void Ball::adjustPosition()
	{
		if (x - radius < range_left)
		{
			x = range_left + radius;
		}
		else if (x + radius > range_right)
		{
			x = range_right - radius;
		}
		if (y - radius < range_top)
		{
			y = range_top + radius;
		}
		else if (y + radius > range_bottom)
		{
			y = range_bottom - radius;
		}
	}

	void Ball::calcSpeedXY()
	{
		vx = speed * std::cos(angle);
		vy = speed * std::sin(angle);
	}
}
