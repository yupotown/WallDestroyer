
//http://bit.ly/hJH5qS PDF NDSソフトウェアの開発環境と Mac OS X

#include "graphics.h"
#include <cmath>

namespace Gfx
{
	void DrawPixel(const Bitmap& bmp, const Point& p, u16 col)
	{
		if (
			p.x >= 0 && p.y >= 0 &&
			p.x < static_cast<int>(bmp.width) && p.y < static_cast<int>(bmp.height)
			)
		{
			*(bmp.ptr + p.y * bmp.width + p.x) = col;
		}
	}
	void DrawPixel(const Bitmap& bmp, int x, int y, u16 col)
	{
		const Point temp = {x, y};
		DrawPixel(bmp, temp, col);
	}

	void DrawLine(const Bitmap& bmp, const Point& start, const Point& end, u16 col)
	{
		const Point *s, *e;

		if (std::abs(end.x - start.x) > std::abs(end.y - start.y))
		{
			//横長
			if (end.x > start.x)
			{
				s = &start;
				e = &end;
			}
			else
			{
				s = &end;
				e = &start;
			}
			int temp_x = e->x - s->x;
			int temp_y = e->y - s->y;
			Point temp_p;
			for (int i = s->x, j = 0; i <= e->x; ++i, ++j)
			{
				temp_p.x = i;
				temp_p.y = j * temp_y / temp_x + s->y;
				DrawPixel(bmp, temp_p, col);
			}
		}
		else
		{
			//縦長
			if (end.y > start.y)
			{
				s = &start;
				e = &end;
			}
			else
			{
				s = &end;
				e = &start;
			}
			int temp_x = e->x - s->x;
			int temp_y = e->y - s->y;
			Point temp_p;
			for (int i = s->y, j = 0; i <= e->y; ++i, ++j)
			{
				temp_p.x = j * temp_x / temp_y + s->x;
				temp_p.y = i;
				DrawPixel(bmp, temp_p, col);
			}
		}
	}
	void DrawLine(const Bitmap& bmp, int start_x, int start_y, int end_x, int end_y, u16 col)
	{
		const Point temp1 = {start_x, start_y}, temp2 = {end_x, end_y};
		DrawLine(bmp, temp1, temp2, col);
	}

	//これ進研ゼミでやったところだ！
	void DrawBox(const Bitmap& bmp, const BoxRegion& rgn, u16 col)
	{
		//---範囲チェック---//
		if (
			rgn.x >= static_cast<int>(bmp.width) ||
			rgn.y >= static_cast<int>(bmp.height) ||
			rgn.x + static_cast<int>(rgn.width) < 0 ||
			rgn.y + static_cast<int>(rgn.height) < 0
			)
		{
			return;
		}
		int
			x = rgn.x,
			y = rgn.y;
		std::size_t
			w = rgn.width,
			h = rgn.height;
		if (x < 0)
		{
			w += x;
			x = 0;
		}
		if (y < 0)
		{
			h += y;
			y = 0;
		}
		if (x + w >= bmp.width)
		{
			w = bmp.width - x;
		}
		if (y + h >= bmp.height)
		{
			h = bmp.height - y;
		}

		//---描画---//
		u16 *pdest = (bmp.ptr + (y * (bmp.width + 7) / 8 * 8 + x));
		for(std::size_t i = 0; i < h; ++i)
		{
			for(std::size_t j = 0; j < w; ++j)
			{
				(*pdest) = col;
				++pdest;
			}
			pdest += bmp.width - w;
		}
	}

	void CopyBox(
		const Bitmap& bmp_dest, const Position& pos_dest,
		const Bitmap& bmp_src, const BoxRegion& rgn_src
		)
	{
		if (
			pos_dest.x + static_cast<int>(rgn_src.width) <= 0 ||
			pos_dest.y + static_cast<int>(rgn_src.height) <= 0 ||
			pos_dest.x >= static_cast<int>(bmp_dest.width) ||
			pos_dest.y >= static_cast<int>(bmp_dest.height)
			)
		{
			return;
		}
		int xd = pos_dest.x,
			yd = pos_dest.y,
			xs = rgn_src.x,
			ys = rgn_src.y;
		std::size_t
			w = rgn_src.width,
			h = rgn_src.height,
			sw = (bmp_src.width + 7) / 8 * 8,
			dw = (bmp_dest.width + 7) / 8 * 8,
			dh = bmp_dest.height;
		if (pos_dest.x < 0)
		{
			w += xd;
			xs = -xd;
			xd = 0;
		}
		if (pos_dest.y < 0)
		{
			h += yd;
			ys = -yd;
			yd = 0;
		}
		if (xd + w >= dw)
		{
			w = dw - xd;
		}
		if (yd + h >= dh)
		{
			h = dh - yd;
		}
		const u16 *psrc = bmp_src.ptr + (ys * sw + xs);
		u16 *pdest = bmp_dest.ptr + (yd * dw + xd);
		for(std::size_t i = 0; i < h; ++i)
		{
			dmaCopy(psrc, pdest, w * 2);
			psrc += sw;
			pdest += dw;
		}
	}

	void CopyBox(
		const Bitmap& bmp_dest, const Position& pos_dest,
		const BitmapTransparent& bmp_src, const BoxRegion& rgn_src
		)
	{
		if (
			pos_dest.x + static_cast<int>(rgn_src.width) <= 0 ||
			pos_dest.y + static_cast<int>(rgn_src.height) <= 0 ||
			pos_dest.x >= static_cast<int>(bmp_dest.width) ||
			pos_dest.y >= static_cast<int>(bmp_dest.height)
			)
		{
			return;
		}
		int xd = pos_dest.x,
			yd = pos_dest.y,
			xs = rgn_src.x,
			ys = rgn_src.y;
		std::size_t
			w = rgn_src.width,
			h = rgn_src.height,
			sw = (bmp_src.width + 7) / 8 * 8,
			dw = (bmp_dest.width + 7) / 8 * 8,
			dh = bmp_dest.height;
		if (pos_dest.x < 0)
		{
			w += xd;
			xs = -xd;
			xd = 0;
		}
		if (pos_dest.y < 0)
		{
			h += yd;
			ys = -yd;
			yd = 0;
		}
		if (xd + w >= dw)
		{
			w = dw - xd;
		}
		if (yd + h >= dh)
		{
			h = dh - yd;
		}
		const u16 *psrc = bmp_src.ptr + (ys * sw + xs);
		u16 *pdest = bmp_dest.ptr + (yd * dw + xd);
		u16 tr_col = bmp_src.tr_col;
		for (std::size_t i = 0; i < h; ++i)
		{
			for (std::size_t j = 0; j < w; ++j)
			{
				if ((*psrc) != tr_col)
				{
					(*pdest) = (*psrc);
				}
				++pdest;
				++psrc;
			}
			psrc += sw - w;
			pdest += dw - w;
		}
	}

	void CopyBox(
		const Bitmap& bmp_dest, const Position& pos_dest,
		const Bitmap& bmp_src
		)
	{
		BoxRegion region = {0, 0, bmp_src.width, bmp_src.height};
		CopyBox(bmp_dest, pos_dest, bmp_src, region);
	}

	void CopyBox(
		const Bitmap& bmp_dest, const Position& pos_dest,
		const BitmapTransparent& bmp_src
		)
	{
		BoxRegion region = {0, 0, bmp_src.width, bmp_src.height};
		CopyBox(bmp_dest, pos_dest, bmp_src, region);
	}

	void CopyBox(const Bitmap& bmp_dest, int x, int y, const Bitmap& bmp_src)
	{
		Position pos = {x, y};
		BoxRegion region = {0, 0, bmp_src.width, bmp_src.height};
		CopyBox(bmp_dest, pos, bmp_src, region);
	}

	void CopyBox(const Bitmap& bmp_dest, int x, int y, const BitmapTransparent& bmp_src)
	{
		Position pos = {x, y};
		BoxRegion region = {0, 0, bmp_src.width, bmp_src.height};
		CopyBox(bmp_dest, pos, bmp_src, region);
	}
}
