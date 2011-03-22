
#include "ball.h"

#include <cmath>

namespace WallDestroyer
{
	Ball::Ball()
		:x(0.0), y(0.0),
		angle(0.0),
		speed(0.0),
		radius(0.0),
		range_left(0), range_right(0), range_top(0), range_bottom(0),
		vx(0.0), vy(0.0)
	{
	}

	Ball::~Ball()
	{
	}

	void Ball::Update()
	{
		calcSpeedXY();
		x += vx;
		y += vy;

		//bounce
		if (x - radius < range_left)
		{
			vx = std::fabs(vx);
			calcAngle();
		}
		else if (x + radius >= range_right)
		{
			vx = -std::fabs(vx);
			calcAngle();
		}
		if (y - radius < range_top)
		{
			vy = std::fabs(vy);
			calcAngle();
		}
		else if (y + radius >= range_bottom)
		{
			vy = -std::fabs(vy);
			calcAngle();
		}

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
		adjustAngle();
	}

	void Ball::SetSpeed(double speed)
	{
		this->speed = speed;
	}

	void Ball::Bounce(double wall_angle)
	{
		angle = 2 * (M_PI + wall_angle) - angle;
		adjustAngle();
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

	double Ball::GetRadius() const
	{
		return radius;
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

	void Ball::adjustAngle()
	{
		while (angle >= M_PI)
		{
			angle -= M_PI * 2;
		}
		while (angle < -M_PI)
		{
			angle += M_PI * 2;
		}
	}

	void Ball::calcSpeedXY()
	{
		vx = speed * std::cos(angle);
		vy = speed * std::sin(angle);
	}

	void Ball::calcAngle()
	{
		angle = std::atan2(vy, vx);
		adjustAngle();
	}

	void Ball::calcSpeed()
	{
		speed = std::sqrt(vx * vx + vy * vy);
	}

	void Ball::calcVector()
	{
		calcAngle();
		calcSpeed();
	}
}
