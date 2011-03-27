
#pragma once

#include "graphics.h"

namespace Collision
{
	//--- 図形 ---
	//点
	///線分
	//円
	//三角形
	//四角形
	//矩形

	//--- 未実装 ---
	//点と線分
	//点と三角形
	//点と四角形
	//線分と線分
	//線分と円
	//線分と三角形
	//線分と四角形
	//線分と矩形
	//円と三角形
	//円と四角形
	//三角形と三角形
	//三角形と四角形
	//三角形と矩形
	//四角形と四角形
	//四角形と矩形

	//--------------------------------------------------

	//点
	struct Point
	{
		int x, y;
	};

	//線分
	struct Line
	{
		Point p[2];
	};

	//円
	struct Circle
	{
		int x, y;
		unsigned int radius;
	};

	//三角形
	struct Triangle
	{
		Point p[3];
	};
	typedef Triangle Trigon;

	//四角形
	struct Quadrileteral
	{
		Point p[4];
	};
	typedef Quadrileteral Tetragon;

	//矩形
	struct Rectangle
	{
		int x, y;
		unsigned int width, height;
	};

	//--------------------------------------------------

	bool Check(const Rectangle& a, const Rectangle& b);

	//--------------------------------------------------

	//点と点
	inline bool Check(const Point& a, const Point& b)
	{
		return (a.x == b.x && a.y == b.y);
	}

	//点と線分（未実装）
	bool Check(const Point& point, const Line& line);
	inline bool Check(const Line& line, const Point& point)
	{
		return Check(point, line);
	}

	//点と円
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

	//点と三角形（未実装）
	bool Check(const Point& point, const Triangle& tri);
	inline bool Check(const Triangle& tri, const Point& point)
	{
		return Check(point, tri);
	}

	//点と四角形（未実装）
	bool Check(const Point& point, const Tetragon& tetra);
	inline bool Check(const Tetragon& tetra, const Point& point)
	{
		return Check(point, tetra);
	}

	//点と矩形
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

	//線分と線分
	bool Check(const Line& a, const Line& b)
	{
		//X座標ラフチェック
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

		//Y座標ラフチェック
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

	//線分と円（未実装）
	bool Check(const Line& line, const Circle& circle);
	inline bool Check(const Circle& circle, const Line& line)
	{
		return Check(line, circle);
	}

	//線分と三角形（未実装）
	bool Check(const Line& line, const Triangle& tri);
	inline bool Check(const Triangle& tri, const Line& line)
	{
		return Check(line, tri);
	}

	//線分と四角形（未実装）
	bool Check(const Line& line, const Tetragon& tetra);
	inline bool Check(const Tetragon& tetra, const Line& line)
	{
		return Check(line, tetra);
	}

	//線分と矩形（未実装）
	bool Check(const Line& line, const Rectangle& rect);
	inline bool Check(const Rectangle& rect, const Line& line)
	{
		return Check(line, rect);
	}

	//円と円
	inline bool Check(const Circle& a, const Circle& b)
	{
		int temp_x = b.x - a.x;
		int temp_y = b.y - a.y;
		int temp_r = static_cast<int>(a.radius + b.radius);
		return (temp_x * temp_x + temp_y * temp_y <= temp_r * temp_r);
	}

	//円と三角形（未実装）
	bool Check(const Circle& circle, const Triangle& tri);
	inline bool Check(const Triangle& tri, const Circle& circle)
	{
		return Check(circle, tri);
	}

	//円と四角形（未実装）
	bool Check(const Circle& circle, const Tetragon& tetra);
	inline bool Check(const Tetragon& tetra, const Circle& circle)
	{
		return Check(circle, tetra);
	}

	//円と矩形
	bool Check(const Circle& circle, const Rectangle& rect)
	{
		//円を矩形とみなしてラフチェック
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

		//円の中に頂点があるか
		for (int i = 0; i < 4; ++i)
		{
			if (Check(v[i], circle))
			{
				return true;
			}
		}

		//円が長方形の各辺に触れているか
		int x = circle.x, y = circle.y, r = circle.radius;
		if (x >= v[0].x && x < v[1].x)
		{
			if (y < v[0].y)
			{
				//円の中心が矩形の上にある
				return (y + r >= v[0].y);
			}
			else if (y >= v[3].y)
			{
				//円の中心が矩形の下にある
				return (y - r < v[3].y);
			}
			else
			{
				//円の中心が矩形の中にある
				return true;
			}
		}
		else if (y >= v[0].y && y < v[3].y)
		{
			if (x < v[0].x)
			{
				//円の中心が矩形の左にある
				return (x + r >= v[0].x);
			}
			else
			{
				//円の中心が矩形の右にある
				return (x - r < v[1].x);
			}
		}

		return false;
	}
	bool Check(const Rectangle& rect, const Circle& circle)
	{
		return Check(circle, rect);
	}

	//三角形と三角形（未実装）
	bool Check(const Triangle& a, const Triangle& b);

	//三角形と四角形（未実装）
	bool Check(const Triangle& tri, const Tetragon& tetra);
	inline bool Check(const Tetragon& tetra, const Triangle& tri)
	{
		return Check(tri, tetra);
	}

	//三角形と矩形（未実装）
	bool Check(const Triangle& tri, const Rectangle& rect);
	inline bool Check(const Rectangle& rect, const Triangle& tri)
	{
		return Check(tri, rect);
	}

	//四角形と四角形（未実装）
	bool Check(const Tetragon& a, const Tetragon& b);

	//四角形と矩形（未実装）
	bool Check(const Tetragon& tetra, const Rectangle& rect);
	inline bool Check(const Rectangle& rect, const Tetragon& tetra)
	{
		return Check(rect, tetra);
	}

	//矩形と矩形
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
