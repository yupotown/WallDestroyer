
#pragma once

#include <nds.h>
#include <iostream>

namespace Gfx
{
	struct Position
	{
		int x, y;
	};

	struct Bitmap
	{
		u16 *ptr;
		std::size_t width, height;
	};

	struct BitmapTransparent
	{
		u16 *ptr;
		std::size_t width, height;
		u16 tr_col;
	};

	struct BoxRegion
	{
		int x, y;
		std::size_t width, height;
	};

	//class HogeBitmap
	//{
	//public:
	//	class PtrProxy
	//	{
	//	public:
	//		PtrProxy(HogeBitmap& parent)
	//			:parent(parent)
	//		{
	//		}

	//		const PtrProxy& operator =(u16 *rhs)
	//		{
	//			parent.ptr = rhs;
	//			return *this;
	//		}

	//		operator u16 *()
	//		{
	//			return parent.ptr;
	//		}

	//	private:
	//		HogeBitmap& parent;
	//	}Ptr;

	//	friend class PtrProxy;

	//	HogeBitmap()
	//		:Ptr(*this)
	//	{
	//		ptr = NULL;
	//	}

	//private:
	//	u16 *ptr;
	//	std::size_t width, height;
	//	u16 tr_col;
	//	bool tr_flag;
	//};

	void DrawBox(const Bitmap& bmp, const BoxRegion& rgn, u16 col);

	void CopyBox(
		const Bitmap& bmp_dest, const Position& pos_dest,
		const Bitmap& bmp_src, const BoxRegion& rgn_src
		);
	void CopyBox(
		const Bitmap& bmp_dest, const Position& pos_dest,
		const BitmapTransparent& bmp_src, const BoxRegion& rgn_src
		);
	void CopyBox(
		const Bitmap& bmp_dest, const Position& pos_dest,
		const Bitmap& bmp_src
		);
	void CopyBox(
		const Bitmap& bmp_dest, const Position& pos_dest,
		const BitmapTransparent& bmp_src
		);
	void CopyBox(const Bitmap& bmp_dest, int x, int y, const Bitmap& bmp_src);
	void CopyBox(const Bitmap& bmp_dest, int x, int y, const BitmapTransparent& bmp_src);
}
