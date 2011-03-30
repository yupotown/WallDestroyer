
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
			draw_pos.x = static_cast<int>(this->GetX() - this->GetRadius());
			draw_pos.y = static_cast<int>(this->GetY() - this->GetRadius());
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
			this->SetRadius(img->width / 2);
		}
	}
}
