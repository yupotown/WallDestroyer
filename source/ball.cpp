
#include "ball.h"

#include <cmath>

namespace WallDestroyer
{
	Ball::Ball()
		:unit(100),
		x(0.0), y(0.0),
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
			vx = std::abs(vx);
			calcAngle();
		}
		else if (x + radius >= range_right)
		{
			vx = -std::abs(vx);
			calcAngle();
		}
		if (y - radius < range_top)
		{
			vy = std::abs(vy);
			calcAngle();
		}
		else if (y + radius >= range_bottom)
		{
			vy = -std::abs(vy);
			calcAngle();
		}

		adjustPosition();
	}

	void Ball::MoveTo(int x, int y)
	{
		this->x = x * unit;
		this->y = y * unit;
		adjustPosition();
	}

	void Ball::Move(int x, int y)
	{
		this->x += x * unit;
		this->y += y * unit;
		adjustPosition();
	}

	void Ball::SetMovableRange(int left, int top, int right, int bottom)
	{
		if (left > right)
		{
			range_left = right * unit;
			range_right = left * unit;
		}
		else
		{
			range_left = left * unit;
			range_right = right * unit;
		}
		if (top > bottom)
		{
			range_top = bottom * unit;
			range_bottom = top * unit;
		}
		else
		{
			range_top = top * unit;
			range_bottom = bottom * unit;
		}
		adjustPosition();
	}

	void Ball::SetAngle(float angle)
	{
		this->angle = angle;
		adjustAngle();
	}

	void Ball::SetSpeed(float speed)
	{
		this->speed = static_cast<int>(speed * unit);
	}

	void Ball::SetRadius(int radius)
	{
		this->radius = radius * unit;
	}

	void Ball::Bounce(float wall_angle)
	{
		angle = 2 * (M_PI + wall_angle) - angle;
		adjustAngle();
	}

	int Ball::GetX() const
	{
		return x / unit;
	}

	int Ball::GetY() const
	{
		return y / unit;
	}

	float Ball::GetAngle() const
	{
		return angle;
	}

	float Ball::GetSpeed() const
	{
		return static_cast<float>(speed) / unit;
	}

	int Ball::GetRadius() const
	{
		return radius / unit;
	}

	int Ball::GetVx() const
	{
		return std::cos(angle) * (speed / unit);
	}

	int Ball::GetVy() const
	{
		return std::sin(angle) * (speed / unit);
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
