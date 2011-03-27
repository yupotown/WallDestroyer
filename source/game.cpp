
#include "game.h"

#include <cstdlib>
#include <ctime>

#include "img_racket.h"
#include "img_ball.h"
#include "img_blocks.h"

#include "collision_check.hpp"

namespace WallDestroyer
{
	Game::Game()
		:vramInitializer(*this),
		bg(BackGround::Instance()),
		bmp_both(bg.GetBothBitmap()),
		rgn_both(bg.GetBothRegion())
	{
		initVram();

		std::srand(std::time(NULL));

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

		for (int i = 0; i < N_IMG_BLOCKS; ++i)
		{
			bmp_blocks[i].ptr = (u16 *)img_blocksBitmap + (40 * 12 * i);
			bmp_blocks[i].width = 40;
			bmp_blocks[i].height = 12;
			//bmp_blocks[i].tr_col = RGB15(0, 0, 0) | BIT(15);
		}

		//debug:set blocks
		for (int i = 0; i < 50; ++i)
		{
			BlockDS *temp = new BlockDS();
			temp->SetImage(&bmp_blocks[std::rand() % N_IMG_BLOCKS]);
			temp->MoveTo(std::rand() % (256 - 40), std::rand() % (192 - 12));
			blocks.push_back(temp);
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

			//debug:collision check
			Collision::Rectangle c_block = {
				racket.GetX(), racket.GetY(),
				racket.GetWidth(), racket.GetHeight()
			};
			Collision::Circle c_ball = {
				ball.GetX(), ball.GetY(),
				ball.GetRadius()
			};
			if (Collision::Check(c_block, c_ball))
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
			bool temp_bounce_flag = false;
			double temp_angle = 0.0;
			for (
				std::list< BlockDS * >::iterator it = blocks.begin();
				it != blocks.end();
				++it
				)
			{
				c_block.x = (*it)->GetX();
				c_block.y = (*it)->GetY();
				c_block.width = (*it)->GetWidth();
				c_block.height = (*it)->GetHeight();
				if (Check(c_block, c_ball))
				{
					int ball_x = ball.GetX();
					int ball_y = ball.GetY();
					int ball_radius = ball.GetRadius();
					int ball_speed = ball.GetSpeed();
					double s = std::sin(ball.GetAngle()),
						c = std::cos(ball.GetAngle());
					Collision::Circle temp_ball;
					temp_ball.radius = ball_radius;
					for (int i = 0; i < ball_speed; ++i)
					{
						temp_ball.x = ball_x + c * i;
						temp_ball.y = ball_y + s * i;
						if (Collision::Check(temp_ball, c_block))
						{
							break;
						}
					}
					temp_bounce_flag = true;
					if (temp_ball.x < c_block.x)
					{
						if (temp_ball.y < c_block.y)
						{
							//¶ã
							temp_angle = std::atan2(
								c_block.y - temp_ball.y,
								c_block.x - temp_ball.x
								) + M_PI / 2;
						}
						else if (temp_ball.y >= c_block.y + static_cast<int>(c_block.height))
						{
							//¶‰º
							temp_angle = std::atan2(
								c_block.y - temp_ball.y,
								c_block.x - temp_ball.x
								) + M_PI / 2;
						}
						else
						{
							//¶
							temp_angle = M_PI / 2;
						}
					}
					else if (temp_ball.x >= c_block.x + static_cast<int>(c_block.width))
					{
						if (temp_ball.y < c_block.y)
						{
							//‰Eã
							temp_angle = std::atan2(
								c_block.y - temp_ball.y,
								c_block.x - temp_ball.x
								) + M_PI / 2;
						}
						else if (temp_ball.y >= c_block.y + static_cast<int>(c_block.height))
						{
							//‰E‰º
							temp_angle = std::atan2(
								c_block.y - temp_ball.y,
								c_block.x - temp_ball.x
								) + M_PI / 2;
						}
						else
						{
							//‰E
							temp_angle = M_PI / 2;
						}
					}
					else
					{
						//ã‰º or ’†‚É‚¢‚½
						temp_angle = 0.0;
					}
					(*it)->OnBallHit(ball);
					//ball.SetSpeed(ball.GetSpeed() + 0.1);
				}
			}
			if (temp_bounce_flag)
			{
				ball.Bounce(temp_angle);
			}

			clearScreen();

			racket.Update();
			racket.Draw();

			ball.Update();
			ball.Draw();

			{
				for (
					std::list< BlockDS * >::iterator it = blocks.begin();
					it != blocks.end();
					)
				{
					(*it)->Update();
					if ((*it)->WasDestroyed())
					{
						delete (*it);
						it = blocks.erase(it);
						continue;
					}
					(*it)->Draw();
					++it;
				}
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
