
#pragma once

#include "ball.h"
#include "graphics.h"
#include "background.h"

namespace WallDestroyer
{
	class BallDS : public Ball
	{
	public:
		BallDS();
		~BallDS();

		virtual void Draw();
		virtual void Update();

		//³•ûŒ`‚Ì‰æ‘œ‚Ì‚İ
		void SetImage(Gfx::BitmapTransparent *img);

	private:
		BallDS(const BallDS& rhs);
		const BallDS& operator =(const BallDS& rhs);

		BackGround& bg;

		Gfx::BitmapTransparent *img;
		Gfx::Position draw_pos;
	};
}
