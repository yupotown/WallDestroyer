
#include "game.h"

#include <cstdlib>
#include <ctime>

#include "img_racket.h"
#include "img_ball.h"
#include "img_blocks.h"

#include "shape/shape_all.h"

namespace WallDestroyer
{
	Game::Game()
		:vramInitializer(*this),
		bg(BackGround::Instance()),
		bmp_both(bg.GetBothBitmap()),
		rgn_both(bg.GetBothRegion()),
		is_started(false), is_cleared(false)
	{
		initVram();

		std::srand(std::time(NULL));

		bmp_racket.ptr = (u16 *)img_racketBitmap;
		bmp_racket.width = 60;
		bmp_racket.height = 15;
		bmp_racket.tr_col = RGB15(0, 0, 0) | BIT(15);
		racket.SetImage(&bmp_racket);
		racket.SetMovableRange(0, 192 * 2 - 30, 256, 192 * 2);
		racket.MoveTo((256 - racket.GetWidth()) / 2, 0);

		bmp_ball.ptr = (u16 *)img_ballBitmap;
		bmp_ball.width = 16;
		bmp_ball.height = 16;
		bmp_ball.tr_col = RGB15(0, 0, 0) | BIT(15);
		ball.SetImage(&bmp_ball);
		ball.SetMovableRange(0, 0, 256, 192 * 2 + 30);

		for (int i = 0; i < N_IMG_BLOCKS; ++i)
		{
			bmp_blocks[i].ptr = (u16 *)img_blocksBitmap + (40 * 12 * i);
			bmp_blocks[i].width = 40;
			bmp_blocks[i].height = 12;
			//bmp_blocks[i].tr_col = RGB15(0, 0, 0) | BIT(15);
		}

		//debug:set blocks
		for (int i = 0; i < 30; ++i)
		{
			BlockDS *temp = new BlockDS();
			temp->SetImage(&bmp_blocks[i % 2]);
			//temp->MoveTo(std::rand() % (256 - 40), std::rand() % (192 - 12));
			temp->MoveTo(
				((1 + 2 * (i % 5)) * 256 - 6 * 40) / (2 * 5),
				((1 + 2 * (i / 5)) * 192 - 6 * 12) / (2 * 5)// + (std::rand() % 3 - 1)
				);
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

			//ëÄçÏ
			operate();

			//debug:collision check
			Shape::Rectangle s_block(
				racket.GetX(), racket.GetY(),
				racket.GetWidth(), racket.GetHeight()
				);
			Shape::Circle s_ball(ball.GetX(), ball.GetY(), ball.GetRadius());
			if (s_ball.IsCollide(s_block))
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
			BlockDS *hit_block = NULL;
			int temp_distance =ball.GetSpeed() + 1;
			Shape::Circle temp_ball;
			for (
				std::list< BlockDS * >::iterator it = blocks.begin();
				it != blocks.end();
				++it
				)
			{
				s_block.SetX((*it)->GetX());
				s_block.SetY((*it)->GetY());
				s_block.SetWidth((*it)->GetWidth());
				s_block.SetHeight((*it)->GetHeight());
				if (s_block.IsCollide(s_ball))
				{
					int ball_x = ball.GetX();
					int ball_y = ball.GetY();
					int ball_radius = ball.GetRadius();
					int ball_speed = ball.GetSpeed();
					double s = std::sin(ball.GetAngle()),
						c = std::cos(ball.GetAngle());
					temp_ball.SetRadius(ball_radius);
					int i;
					//É{Å[ÉãÇÃà»ëOÇÃà íuÇ©ÇÁÉuÉçÉbÉNÇ…ìñÇΩÇÈÇ‹Ç≈ÇÃà⁄ìÆó Çí≤Ç◊ÇÈ
					for (i = 0; i < ball_speed; ++i)
					{
						temp_ball.SetX(ball_x + c * i);
						temp_ball.SetY(ball_y + s * i);
						if (temp_ball.IsCollide(s_block))
						{
							break;
						}
					}
					if (i < temp_distance)
					{
						hit_block = (*it);
					}
					temp_distance = i;
				}
			}
			//for (
			//	std::list< BlockDS * >::iterator it = list_hit_blocks.begin();
			//	it != list_hit_blocks.end();
			//	++it
			//	)
			if (hit_block != NULL)
			{
				//bounce
				s_block.SetX(hit_block->GetX());
				s_block.SetY(hit_block->GetY());
				s_block.SetWidth(hit_block->GetWidth());
				s_block.SetHeight(hit_block->GetHeight());
				temp_bounce_flag = true;
				if (temp_ball.GetX() < s_block.GetX())
				{
					if (
						(temp_ball.GetY() < s_block.GetY()) ||
						(temp_ball.GetY() >= s_block.GetY() + s_block.GetHeight())
						)
					{
						//ç∂è„orç∂â∫
						temp_angle = std::atan2(
							s_block.GetY() - temp_ball.GetY(),
							s_block.GetX() - temp_ball.GetX()
							) + M_PI / 2;
					}
					else
					{
						//ç∂
						temp_angle = M_PI / 2;
					}
				}
				else if (temp_ball.GetX() >= s_block.GetX() + s_block.GetWidth())
				{
					if (
						(temp_ball.GetY() < s_block.GetY()) ||
						(temp_ball.GetY() >= s_block.GetY() + s_block.GetHeight())
						)
					{
						//âEè„orâEâ∫
						temp_angle = std::atan2(
							s_block.GetY() - temp_ball.GetY(),
							s_block.GetX() - temp_ball.GetX()
							) + M_PI / 2;
					}
					else
					{
						//âE
						temp_angle = M_PI / 2;
					}
				}
				else
				{
					//è„â∫ or íÜÇ…Ç¢ÇΩ
					temp_angle = 0.0;
				}
				hit_block->OnBallHit(ball);
				ball.SetSpeed(ball.GetSpeed() + 0.1);
			}
			if (temp_bounce_flag)
			{
				ball.Bounce(temp_angle);
				if (ball.GetAngle() >= 0 && ball.GetAngle() < M_PI / 6)
				{
					ball.SetAngle(M_PI / 6);
				}
				else if (ball.GetAngle() < 0 && ball.GetAngle() > -M_PI / 6)
				{
					ball.SetAngle(-M_PI / 6);
				}
				else if (ball.GetAngle() > M_PI * 3 / 4)
				{
					ball.SetAngle(M_PI * 3 / 4);
				}
				else if (ball.GetAngle() < -M_PI * 3 / 4)
				{
					ball.SetAngle(-M_PI * 3 / 4);
				}
			}

			update();
			draw();

			bg.Update();
		}
	}

	void Game::operate()
	{
		if (is_started)
		{
			//debug:racket operation
			if (keysHeld() & KEY_LEFT)
			{
				racket.Move(-3, 0);
			}
			else if (keysHeld() & KEY_RIGHT)
			{
				racket.Move(3, 0);
			}
			else if (keysHeld() & KEY_TOUCH)
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
		}
		else
		{
			if ((keysDown() & KEY_TOUCH) == 0 && (keysHeld() & KEY_TOUCH))
			{
				touchPosition touch;
				touchRead(&touch);
				ball.SetAngle(std::atan2(
					static_cast<int>(touch.py) + 192 - ball.GetY(),
					static_cast<int>(touch.px) - ball.GetX()
					));
			}
			else if (keysHeld() & KEY_LEFT)
			{
				ball.SetAngle(ball.GetAngle() - M_PI / 90);
			}
			else if (keysHeld() & KEY_RIGHT)
			{
				ball.SetAngle(ball.GetAngle() + M_PI / 90);
			}
			if (ball.GetAngle() > 0.0)
			{
				ball.SetAngle(-ball.GetAngle());
			}
			//30ìxêßå¿
			if (ball.GetAngle() > -M_PI / 6)
			{
				ball.SetAngle(-M_PI / 6);
			}
			else if (ball.GetAngle() < -M_PI * 5 / 6)
			{
				ball.SetAngle(-M_PI * 5 / 6);
			}
			ball.SetSpeed(0.0);
			ball.MoveTo(
				racket.GetX() + racket.GetWidth() / 2,
				racket.GetY() - racket.GetHeight() / 2 - ball.GetRadius()
				);
			if (keysDown() & (KEY_A | KEY_UP))
			{
				is_started = true;
				ball.SetSpeed(2.0);
			}
			else if (keysDown() & KEY_TOUCH)
			{
				touchPosition touch;
				touchRead(&touch);
				Shape::Point p_touch(
					static_cast<int>(touch.px),
					static_cast<int>(touch.py + 192)
					);
				Shape::Circle c_ball(
					ball.GetX(), ball.GetY(), ball.GetRadius()
					);
				if (p_touch.IsCollide(c_ball))
				{
					is_started = true;
					ball.SetSpeed(2.0);
				}
			}
		}
	}

	void Game::update()
	{
		racket.Update();
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
			++it;
		}
		ball.Update();

		if (!is_cleared && ball.GetY() - ball.GetRadius() >= 192 * 2)
		{
			//failed
			//debug
			is_started = false;
			ball.SetSpeed(0.0);
			//for(;;);//(ÅLÅGÉ÷ÅGÅM)
		}

		if (blocks.empty())
		{
			//game clear
			//debug
			is_cleared = true;
			//for(;;);//(ÅLÅGÉ÷ÅGÅM)
		}
	}

	void Game::draw()
	{
		clearScreen();

		racket.Draw();
		for (
			std::list< BlockDS * >::iterator it = blocks.begin();
			it != blocks.end();
			++it
			)
		{
			(*it)->Draw();
		}
		if (!is_started)
		{
			Gfx::Point p1, p2;
			p1.x = ball.GetX();
			p1.y = ball.GetY();
			p2.x = p1.x + 30 * std::cos(ball.GetAngle());
			p2.y = p1.y + 30 * std::sin(ball.GetAngle());
			Gfx::DrawLine(bmp_both, p1, p2, RGB15(31, 31, 31) | BIT(15));
		}
		ball.Draw();
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
