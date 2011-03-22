
#pragma once

#include <nds.h>
#include "graphics.h"

class BackGround
{
public:
	static BackGround& Instance();

	void Update();

	int GetTop() const;
	int GetBottom() const;
	u16 *GetTopPtr() const;
	u16 *GetBottomPtr() const;
	const Gfx::Bitmap& GetTopBitmap() const;
	const Gfx::Bitmap& GetBottomBitmap() const;
	const Gfx::Bitmap& GetBothBitmap() const;
	const Gfx::BoxRegion& GetSingleRegion() const;
	const Gfx::BoxRegion& GetBothRegion() const;
private:
	BackGround();
	~BackGround();

	int bg_top, bg_bottom;

	u16 *bg_top_ptr, *bg_bottom_ptr;
	u16 *bg_top_buf, *bg_bottom_buf;

	Gfx::Bitmap bmp_top, bmp_bottom, bmp_both;
	Gfx::BoxRegion rgn_single, rgn_both;
};
