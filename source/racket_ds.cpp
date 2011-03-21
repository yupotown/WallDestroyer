
#include "racket_ds.h"

namespace WallDestroyer
{
	RacketDS::RacketDS()
		:bg(BackGround::Instance())
		,img(NULL)
	{
	}

	RacketDS::~RacketDS()
	{
	}

	void RacketDS::Update()
	{
	}

	void RacketDS::Draw()
	{
		if (img != NULL)
		{
			draw_pos.x = this->x;
			draw_pos.y = this->y;
			Gfx::CopyBox(bg.GetBothBitmap(), draw_pos, *img);
		}
	}

	void RacketDS::SetImage(Gfx::BitmapTransparent *img)
	{
		this->img = img;
		width = img->width;
		height = img->height;
	}
}
