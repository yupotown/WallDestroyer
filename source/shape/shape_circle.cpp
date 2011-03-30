
#include "shape_circle.h"

namespace Shape
{
	Circle::Circle()
		:x(0), y(0),
		radius(1)
	{
	}

	Circle::Circle(int x, int y, int radius)
		:x(x), y(y), radius(radius)
	{
		adjustRadius();
	}

	Circle::Circle(const Circle& rhs)
		:x(rhs.x), y(rhs.y), radius(rhs.radius)
	{
	}

	Circle::~Circle()
	{
	}

	const Circle& Circle::operator =(const Circle& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->radius = rhs.radius;
		return *this;
	}

	bool Circle::IsCollide(const Point& rhs) const
	{
		return rhs.IsCollide(*this);
	}

	bool Circle::IsCollide(const Circle& rhs) const
	{
		return (
			(rhs.x - this->x) * (rhs.x - this->x) *
			(rhs.y - this->y) * (rhs.y - this->y) <=
			(rhs.radius + this->radius) * (rhs.radius + this->radius)
			);
	}

	bool Circle::IsCollide(const Rectangle& rhs) const
	{
		//円を矩形と見てラフチェック
		{
			Rectangle rough_rect(x - radius, y - radius, radius * 2, radius * 2);
			if (!rough_rect.IsCollide(rhs))
			{
				return false;
			}
		}

		//矩形の各頂点が円に含まれているか
		{
			Point vtx_points[4];
			vtx_points[0].SetX(rhs.x);
			vtx_points[0].SetY(rhs.y);
			vtx_points[1].SetX(rhs.x + rhs.width);
			vtx_points[1].SetY(rhs.y);
			vtx_points[2].SetX(rhs.x + rhs.width);
			vtx_points[2].SetY(rhs.y + rhs.height);
			vtx_points[3].SetX(rhs.x);
			vtx_points[3].SetY(rhs.y + rhs.height);

			for (int i = 0; i < 4; ++i)
			{
				if (vtx_points[i].IsCollide(*this))
				{
					return true;
				}
			}
		}

		//矩形の辺が円と重なっているか
		{
			if (this->x < rhs.x)
			{
				if ((this->y < rhs.y) || (this->y >= rhs.y + rhs.height))
				{
					//円の中心が矩形の左上/左下にある
					//頂点は判定済みなので、重なっていない
					return false;
				}
				else
				{
					//円の中心が矩形の左にある
					return (this->x + this->radius >= rhs.x);
				}
			}
			else if (this->x >= rhs.x + rhs.width)
			{
				if ((this->y < rhs.y) || (this->y >= rhs.y + rhs.height))
				{
					//円の中心が矩形の右上/右下にある
					//頂点は判定済みなので、重なっていない
					return false;
				}
				else
				{
					//円の中心が矩形の右にある
					return (this->x - this->radius < rhs.x + rhs.width);
				}
			}
			else
			{
				//円の中心が矩形の上/下/内側にある
				//ラフチェック済みなので、重なっている
				return true;
			}
		}

		//ここには来ない
		return false;
	}

	bool Circle::IsCollide(const Line& rhs) const
	{
		return false;
	}

	void Circle::Set(int x, int y, int radius)
	{
		this->x = x;
		this->y = y;
		this->radius = radius;
		adjustRadius();
	}

	void Circle::SetX(int value)
	{
		x = value;
	}

	void Circle::SetY(int value)
	{
		y = value;
	}

	void Circle::SetRadius(int value)
	{
		radius = value;
		adjustRadius();
	}

	int Circle::GetX() const
	{
		return x;
	}

	int Circle::GetY() const
	{
		return y;
	}

	int Circle::GetRadius() const
	{
		return radius;
	}

	void Circle::adjustRadius()
	{
		if (radius < 0)
		{
			radius = 0;
		}
	}
}
