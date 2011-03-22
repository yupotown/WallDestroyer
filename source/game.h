
#pragma once

#include <nds.h>
#include "background.h"
#include "graphics.h"

#include <vector>
#include <cmath>

#include "racket_ds.h"
#include "ball_ds.h"
#include "block_ds.h"

#define N_BLOCKS (4)

namespace WallDestroyer
{
	class Game
	{
	public:
		Game();
		~Game();

		void Run();

	private:
		Game(const Game& rhs);
		const Game& operator =(const Game& rhs);

		class VramInitializer
		{
		public:
			VramInitializer(Game& parent);
		};
		friend class VramInitializer;

		VramInitializer vramInitializer;

		BackGround& bg;

		const Gfx::Bitmap& bmp_both;
		const Gfx::BoxRegion& rgn_both;

		RacketDS racket;
		BallDS ball;
		std::vector< BlockDS > blocks;
		Gfx::BitmapTransparent bmp_racket, bmp_ball, bmp_blocks[N_BLOCKS];

		void initVram();
		void clearScreen();
	};
}
