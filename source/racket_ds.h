
#pragma once

#include <nds.h>
#include "racket.h"
#include "graphics.h"
#include "background.h"

namespace WallDestroyer
{
	class RacketDS : public Racket
	{
	public:
		RacketDS();
		virtual ~RacketDS();

		virtual void Update();
		virtual void Draw();

		void SetImage(Gfx::BitmapTransparent *img);

	private:
		RacketDS(const RacketDS& rhs);
		const RacketDS& operator =(const RacketDS& rhs);

		BackGround& bg;

		Gfx::BitmapTransparent *img;
		Gfx::Position draw_pos;
	};
}
