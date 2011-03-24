
#include "block_ds.h"

namespace WallDestroyer
{
	BlockDS::BlockDS()
		:bg(BackGround::Instance())
		,img(NULL)
	{
	}

	BlockDS::~BlockDS()
	{
	}

	void BlockDS::Draw()
	{
		if (img != NULL)
		{
			draw_pos.x = this->x;
			draw_pos.y = this->y;
			Gfx::CopyBox(bg.GetBothBitmap(), draw_pos, *img);
		}
	}

	//void BlockDS::SetImage(Gfx::BitmapTransparent *img)
	//{
	//	this->img = img;
	//	width = img->width;
	//	height = img->height;
	//	adjustSize();
	//}

	void BlockDS::SetImage(Gfx::Bitmap *img)
	{
		this->img = img;
		width = img->width;
		height = img->height;
		adjustSize();
	}
}
