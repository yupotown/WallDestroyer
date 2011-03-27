
#pragma once

#include "graphics.h"

namespace Collision
{
	//--- �}�` ---
	//�_
	///����
	//�~
	//�O�p�`
	//�l�p�`
	//��`

	//--- ������ ---
	//�_�Ɛ���
	//�_�ƎO�p�`
	//�_�Ǝl�p�`
	//�����Ɛ���
	//�����Ɖ~
	//�����ƎO�p�`
	//�����Ǝl�p�`
	//�����Ƌ�`
	//�~�ƎO�p�`
	//�~�Ǝl�p�`
	//�O�p�`�ƎO�p�`
	//�O�p�`�Ǝl�p�`
	//�O�p�`�Ƌ�`
	//�l�p�`�Ǝl�p�`
	//�l�p�`�Ƌ�`

	//--------------------------------------------------

	//�_
	struct Point
	{
		int x, y;
	};

	//����
	struct Line
	{
		Point p[2];
	};

	//�~
	struct Circle
	{
		int x, y;
		unsigned int radius;
	};

	//�O�p�`
	struct Triangle
	{
		Point p[3];
	};
	typedef Triangle Trigon;

	//�l�p�`
	struct Quadrileteral
	{
		Point p[4];
	};
	typedef Quadrileteral Tetragon;

	//��`
	struct Rectangle
	{
		int x, y;
		unsigned int width, height;
	};

	//--------------------------------------------------

	bool Check(const Rectangle& a, const Rectangle& b);

	//--------------------------------------------------

	//�_�Ɠ_
	inline bool Check(const Point& a, const Point& b)
	{
		return (a.x == b.x && a.y == b.y);
	}

	//�_�Ɛ����i�������j
	bool Check(const Point& point, const Line& line);
	inline bool Check(const Line& line, const Point& point)
	{
		return Check(point, line);
	}

	//�_�Ɖ~
	inline bool Check(const Point& point, const Circle& circle)
	{
		int temp_x = point.x - circle.x;
		int temp_y = point.y - circle.y;
		return (
			temp_x * temp_x + temp_y * temp_y <=
			static_cast<int>(circle.radius * circle.radius)
			);
	}
	inline bool Check(const Circle& circle, const Point& point)
	{
		return Check(point, circle);
	}

	//�_�ƎO�p�`�i�������j
	bool Check(const Point& point, const Triangle& tri);
	inline bool Check(const Triangle& tri, const Point& point)
	{
		return Check(point, tri);
	}

	//�_�Ǝl�p�`�i�������j
	bool Check(const Point& point, const Tetragon& tetra);
	inline bool Check(const Tetragon& tetra, const Point& point)
	{
		return Check(point, tetra);
	}

	//�_�Ƌ�`
	inline bool Check(const Point& point, const Rectangle& rect)
	{
		return (
			point.x >= rect.x &&
			point.y >= rect.y &&
			point.x < static_cast<int>(rect.x + rect.width) &&
			point.y < static_cast<int>(rect.y + rect.height)
			);
	}
	inline bool Check(const Rectangle& rect, const Point& point)
	{
		return Check(point, rect);
	}

	//�����Ɛ���
	bool Check(const Line& a, const Line& b)
	{
		//X���W���t�`�F�b�N
		if (a.p[0].x >= a.p[1].x)
		{
			if (
				(a.p[0].x < b.p[0].x && a.p[0].x < b.p[1].x) ||
				(a.p[1].x > b.p[0].x && a.p[1].x > b.p[1].x)
				)
			{
				return false;
			}
		}
		else
		{
			if (
				(a.p[0].x > b.p[0].x && a.p[0].x > b.p[1].x) ||
				(a.p[1].x < b.p[0].x && a.p[1].x < b.p[1].x)
				)
			{
				return false;
			}
		}

		//Y���W���t�`�F�b�N
		if (a.p[0].y >= a.p[1].y)
		{
			if (
				(a.p[0].y < b.p[0].y && a.p[0].y < b.p[1].y) ||
				(a.p[1].y > b.p[0].y && a.p[1].y > b.p[1].y)
				)
			{
				return false;
			}
		}
		else
		{
			if (
				(a.p[0].y > b.p[0].y && a.p[0].y > b.p[1].y) ||
				(a.p[1].y < b.p[0].y && a.p[1].y < b.p[1].y)
				)
			{
				return false;
			}
		}

		//
		if (
			(
				(a.p[0].x - a.p[1].x) * (b.p[0].y - a.p[0].y) +
				(a.p[0].y - a.p[1].y) * (a.p[0].x - b.p[0].x)
			) *
			(
				(a.p[0].x - a.p[1].x) * (b.p[1].y - a.p[0].y) +
				(a.p[0].y - a.p[1].y) * (a.p[0].x - b.p[1].x)
			) > 0
		)
		{
			return false;
		}
		if (
			(
				(b.p[0].x - b.p[1].x) * (a.p[0].y - b.p[0].y) +
				(b.p[0].y - b.p[1].y) * (b.p[0].x - a.p[0].x)
			) *
			(
				(b.p[0].x - b.p[1].x) * (a.p[1].y - b.p[0].y) +
				(b.p[0].y - b.p[1].y) * (b.p[0].x - a.p[1].x)
			) > 0
		)
		{
			return false;
		}
		return true;
	}

	//�����Ɖ~�i�������j
	bool Check(const Line& line, const Circle& circle);
	inline bool Check(const Circle& circle, const Line& line)
	{
		return Check(line, circle);
	}

	//�����ƎO�p�`�i�������j
	bool Check(const Line& line, const Triangle& tri);
	inline bool Check(const Triangle& tri, const Line& line)
	{
		return Check(line, tri);
	}

	//�����Ǝl�p�`�i�������j
	bool Check(const Line& line, const Tetragon& tetra);
	inline bool Check(const Tetragon& tetra, const Line& line)
	{
		return Check(line, tetra);
	}

	//�����Ƌ�`�i�������j
	bool Check(const Line& line, const Rectangle& rect);
	inline bool Check(const Rectangle& rect, const Line& line)
	{
		return Check(line, rect);
	}

	//�~�Ɖ~
	inline bool Check(const Circle& a, const Circle& b)
	{
		int temp_x = b.x - a.x;
		int temp_y = b.y - a.y;
		int temp_r = static_cast<int>(a.radius + b.radius);
		return (temp_x * temp_x + temp_y * temp_y <= temp_r * temp_r);
	}

	//�~�ƎO�p�`�i�������j
	bool Check(const Circle& circle, const Triangle& tri);
	inline bool Check(const Triangle& tri, const Circle& circle)
	{
		return Check(circle, tri);
	}

	//�~�Ǝl�p�`�i�������j
	bool Check(const Circle& circle, const Tetragon& tetra);
	inline bool Check(const Tetragon& tetra, const Circle& circle)
	{
		return Check(circle, tetra);
	}

	//�~�Ƌ�`
	bool Check(const Circle& circle, const Rectangle& rect)
	{
		//�~����`�Ƃ݂Ȃ��ă��t�`�F�b�N
		Rectangle rect_circle = {
			circle.x - circle.radius,
			circle.y - circle.radius,
			circle.x + circle.radius,
			circle.y + circle.radius
		};
		if (!Check(rect_circle, rect))
		{
			return false;
		}

		Point v[4];
		v[0].x = rect.x;
		v[0].y = rect.y;
		v[2].x = rect.x + static_cast<int>(rect.width);
		v[2].y = rect.y + static_cast<int>(rect.height);
		v[1].x = v[2].x;
		v[1].y = rect.y;
		v[3].x = rect.x;
		v[3].y = v[2].y;

		//�~�̒��ɒ��_�����邩
		for (int i = 0; i < 4; ++i)
		{
			if (Check(v[i], circle))
			{
				return true;
			}
		}

		//�~�������`�̊e�ӂɐG��Ă��邩
		int x = circle.x, y = circle.y, r = circle.radius;
		if (x >= v[0].x && x < v[1].x)
		{
			if (y < v[0].y)
			{
				//�~�̒��S����`�̏�ɂ���
				return (y + r >= v[0].y);
			}
			else if (y >= v[3].y)
			{
				//�~�̒��S����`�̉��ɂ���
				return (y - r < v[3].y);
			}
			else
			{
				//�~�̒��S����`�̒��ɂ���
				return true;
			}
		}
		else if (y >= v[0].y && y < v[3].y)
		{
			if (x < v[0].x)
			{
				//�~�̒��S����`�̍��ɂ���
				return (x + r >= v[0].x);
			}
			else
			{
				//�~�̒��S����`�̉E�ɂ���
				return (x - r < v[1].x);
			}
		}

		return false;
	}
	bool Check(const Rectangle& rect, const Circle& circle)
	{
		return Check(circle, rect);
	}

	//�O�p�`�ƎO�p�`�i�������j
	bool Check(const Triangle& a, const Triangle& b);

	//�O�p�`�Ǝl�p�`�i�������j
	bool Check(const Triangle& tri, const Tetragon& tetra);
	inline bool Check(const Tetragon& tetra, const Triangle& tri)
	{
		return Check(tri, tetra);
	}

	//�O�p�`�Ƌ�`�i�������j
	bool Check(const Triangle& tri, const Rectangle& rect);
	inline bool Check(const Rectangle& rect, const Triangle& tri)
	{
		return Check(tri, rect);
	}

	//�l�p�`�Ǝl�p�`�i�������j
	bool Check(const Tetragon& a, const Tetragon& b);

	//�l�p�`�Ƌ�`�i�������j
	bool Check(const Tetragon& tetra, const Rectangle& rect);
	inline bool Check(const Rectangle& rect, const Tetragon& tetra)
	{
		return Check(rect, tetra);
	}

	//��`�Ƌ�`
	inline bool Check(const Rectangle& a, const Rectangle& b)
	{
		return (
			a.x < b.x + static_cast<int>(b.width) &&
			b.x < a.x + static_cast<int>(a.width) &&
			a.y < b.y + static_cast<int>(b.height) &&
			b.y < a.y + static_cast<int>(a.height)
			);
	}
}
