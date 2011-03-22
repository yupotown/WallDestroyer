
#include "game.h"

#include "img_racket.h"
#include "img_ball.h"
#include "img_blocks.h"

#include "collision_check.h"

namespace WallDestroyer
{
	Game::Game()
		:vramInitializer(*this),
		bg(BackGround::Instance()),
		bmp_both(bg.GetBothBitmap()),
		rgn_both(bg.GetBothRegion())
	{
		initVram();

		bmp_racket.ptr = (u16 *)img_racketBitmap;
		bmp_racket.width = 60;
		bmp_racket.height = 15;
		bmp_racket.tr_col = RGB15(0, 0, 0) | BIT(15);
		racket.SetImage(&bmp_racket);
		racket.SetMovableRange(0, 192 * 2 - 30, 256, 192 * 2);

		bmp_ball.ptr = (u16 *)img_ballBitmap;
		bmp_ball.width = 16;
		bmp_ball.height = 16;
		bmp_ball.tr_col = RGB15(0, 0, 0) | BIT(15);
		ball.SetImage(&bmp_ball);
		ball.SetMovableRange(0, 0, 256, 192 * 2 + 30);
		ball.SetSpeed(2.0);
		ball.SetAngle(M_PI * 0.25);

		for (int i = 0; i < N_BLOCKS; ++i)
		{
			bmp_blocks[i].ptr = (u16 *)img_blocksBitmap + (40 * 12 * i);
			bmp_blocks[i].width = 40;
			bmp_blocks[i].height = 12;
			bmp_blocks[i].tr_col = RGB15(0, 0, 0) | BIT(15);
		}
	}

	Game::~Game()
	{
	}

	void Game::Run()
	{
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
							if (temp < -3)
							{
								temp = -3;
							}
						}
						else
						{
							++temp;
							if (temp > 3)
							{
								temp = 3;
							}
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

			//debug:hit check
			Gfx::BoxRegion rgn1 = {
				racket.GetX(), racket.GetY(),
				racket.GetWidth(), racket.GetHeight()
			};
			int temp_r = ball.GetRadius() - 2;
			Gfx::BoxRegion rgn2 = {
				ball.GetX() - temp_r, ball.GetY() - temp_r,
				temp_r * 2, temp_r * 2
			};
			if (CollisionCheck(rgn1, rgn2))
			{
				if (ball.GetX() < racket.GetX())
				{
					ball.SetAngle(M_PI * 7 / 6);
				}
				else if (ball.GetX() >= racket.GetX() + racket.GetWidth())
				{
					ball.SetAngle(0.0 - M_PI / 6);
				}
				else
				{
					ball.Bounce((ball.GetX() - (racket.GetX() + racket.GetWidth() / 2)) *
						(M_PI / 24) / (racket.GetWidth() / 2));
					if (ball.GetAngle() > 0.0 - M_PI / 6 && ball.GetAngle() < M_PI / 2)
					{
						ball.SetAngle(0.0 - M_PI / 6);
					}
					else if (ball.GetAngle() >= M_PI / 2 && ball.GetAngle() < M_PI * 7 / 6)
					{
						ball.SetAngle(M_PI * 7 / 6);
					}
				}
			}

			clearScreen();

			racket.Update();
			racket.Draw();

			ball.Update();
			ball.Draw();

			for (std::vector< BlockDS >::iterator it = blocks.begin(); it != blocks.end(); ++it)
			{
				(*it).Update();
				(*it).Draw();
			}

			bg.Update();
		}
	}

	void Game::initVram()
	{
		videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE |
			DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT);
		vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
		vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
		videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE|
			DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT);
		vramSetBankC(VRAM_C_SUB_BG_0x06200000);
		vramSetBankD(VRAM_D_SUB_SPRITE);
	}

	void Game::clearScreen()
	{
		Gfx::DrawBox(bmp_both, rgn_both, RGB15(0, 0, 0) | BIT(15));
	}

	Game::VramInitializer::VramInitializer(Game& parent)
	{
		parent.initVram();
	}
}
