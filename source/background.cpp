
#include "background.h"

BackGround& BackGround::Instance()
{
	static BackGround instance;
	return instance;
}

void BackGround::Update()
{
	dmaCopy(bg_top_buf, bg_top_ptr, 256 * 192 * 2);
	dmaCopy(bg_bottom_buf, bg_bottom_ptr, 256 * 192 * 2);
}

int BackGround::GetTop() const
{
	return bg_top;
}

int BackGround::GetBottom() const
{
	return bg_bottom;
}

u16 *BackGround::GetTopPtr() const
{
	return bg_top_buf;
}

u16 *BackGround::GetBottomPtr() const
{
	return bg_bottom_buf;
}

const Gfx::Bitmap& BackGround::GetTopBitmap() const
{
	return bmp_top;
}

const Gfx::Bitmap& BackGround::GetBottomBitmap() const
{
	return bmp_bottom;
}

const Gfx::Bitmap& BackGround::GetBothBitmap() const
{
	return bmp_both;
}

BackGround::BackGround()
{
	//backgrundの初期化
	bg_top = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	bg_bottom = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	//backgroundのアドレスを取得
	bg_top_ptr = bgGetGfxPtr(bg_top);
	bg_bottom_ptr = bgGetGfxPtr(bg_bottom);

	//バッファを用意
	//bg_top_buf = new u16[256 * 192];
	//bg_bottom_buf = new u16[256 * 192];
	bg_top_buf = new u16[256 * 192 * 2];
	bg_bottom_buf = bg_top_buf + (256 * 192);

	//Bitmap構造体を用意
	bmp_top.ptr = bg_top_buf;
	bmp_top.width = 256;
	bmp_top.height = 192;
	bmp_bottom.ptr = bg_bottom_buf;
	bmp_bottom.width = 256;
	bmp_bottom.height = 192;
	bmp_both.ptr = bg_top_buf;
	bmp_both.width = 256;
	bmp_both.height = 192 * 2;
}

BackGround::~BackGround()
{
	//delete[] bg_top_buf;
	//delete[] bg_bottom_buf;
	delete[] bg_top_buf;
}
