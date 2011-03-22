/*
*	Wall Destroyer
*	‚ä‚Û
*/

#include <nds.h>
#include "background.h"
#include <cmath>
//debug
#include "racket_ds.h"
#include "ball_ds.h"
#include "block_ds.h"
#include "img_racket.h"
#include "img_ball.h"
#include "img_blocks.h"

int main()
{
	videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE |
		DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT);
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
	videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE|
		DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	BackGround& bg(BackGround::Instance());
	const Gfx::Bitmap& bmp_both(bg.GetBothBitmap());
	const Gfx::BoxRegion rgn_both = {
		0, 0, 256, 192 * 2
	};

	//debug:racket
	WallDestroyer::RacketDS racket;
	Gfx::BitmapTransparent bmp_racket = {
		(u16 *)img_racketBitmap,
		60, 15, RGB15(0, 0, 0) | BIT(15)
	};
	racket.SetImage(&bmp_racket);
	racket.SetMovableRange(0, 192 * 2 - 30, 256, 192 * 2);

	//debug:ball
	WallDestroyer::BallDS ball;
	Gfx::BitmapTransparent bmp_ball = {
		(u16 *)img_ballBitmap,
		16, 16, RGB15(0, 0, 0) | BIT(15)
	};
	ball.SetImage(&bmp_ball);
	ball.SetMovableRange(0, 0, 256, 192 * 2 + 30);
	ball.SetSpeed(2.0);
	ball.SetAngle(M_PI * 0.25);
	ball.MoveTo(10, 10);

	//debug:block
	WallDestroyer::BlockDS block;
	Gfx::BitmapTransparent bmp_block_red = {
		(u16 *)img_blocksBitmap,
		40, 12, RGB15(0, 0, 0) | BIT(15)
	};
	block.SetImage(&bmp_block_red);
	block.MoveTo(20, 20);

	for (;;)
	{
		swiWaitForVBlank();
		scanKeys();

		//debug:racket operation
		if (keysHeld() & KEY_LEFT)
		{
			racket.Move(-3, 0);
		}
		if (keysHeld() & KEY_RIGHT)
		{
			racket.Move(3, 0);
		}
		if (keysHeld() & KEY_TOUCH)
		{
			touchPosition touch;
			touchRead(&touch);
			int temp = touch.px - (racket.GetX() + racket.GetWidth() / 2);
			if (temp != 0)
			{
				if (temp >= 10 || temp <= -10)
				{
					temp /= 10;
					if (temp < 0)
					{
						--temp;
					}
					else
					{
						++temp;
					}
				}
				else if (temp > 0)
				{
					temp = 1;
				}
				else if (temp < 0)
				{
					temp = -1;
				}
			}
			racket.Move(temp, 0);
		}

		//clear screen
		Gfx::DrawBox(bmp_both, rgn_both, RGB15(0, 0, 0) | BIT(15));

		//debug:update racket
		racket.Update();
		racket.Draw();

		//debug:update ball
		ball.Update();
		ball.Draw();

		//debug:update block
		block.Update();
		block.Draw();

		bg.Update();
	}

	return 0;
}
