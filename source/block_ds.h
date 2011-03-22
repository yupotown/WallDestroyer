
#pragma once

#include "block.h"
#include "graphics.h"
#include "background.h"

namespace WallDestroyer
{
	class BlockDS : public Block
	{
	public:
		BlockDS();
		~BlockDS();

		virtual void Draw();

		void SetImage(Gfx::BitmapTransparent *img);

	private:
		BlockDS(const BlockDS& rhs);
		const BlockDS& operator =(const BlockDS& rhs);

		BackGround& bg;

		Gfx::BitmapTransparent *img;
		Gfx::Position draw_pos;
	};
}
