
#include "ball_ds.h"

namespace WallDestroyer
{
	BallDS::BallDS()
		:bg(BackGround::Instance()),
		img(NULL)
	{
	}

	BallDS::~BallDS()
	{
	}

	void BallDS::Draw()
	{
		if (img != NULL)
		{
			draw_pos.x = static_cast<int>(x - radius);
			draw_pos.y = static_cast<int>(y - radius);
			Gfx::CopyBox(bg.GetBothBitmap(), draw_pos, *img);
		}
	}

	void BallDS::Update()
	{
		Ball::Update();
	}

	void BallDS::SetImage(Gfx::BitmapTransparent *img)
	{
		//³•ûŒ`‚Ì‰æ‘œ‚Ì‚Ý
		if (img->width == img->height)
		{
			this->img = img;
			radius = img->width / 2;
		}
	}
}
