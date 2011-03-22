
#include "block.h"

namespace WallDestroyer
{
	Block::Block()
		:x(0), y(0),
		width(0), height(0),
		is_destroyed(false)
	{
	}

	Block::~Block()
	{
	}

	void Block::Update()
	{
	}

	void Block::OnBallHit(Ball& ball)
	{
		is_destroyed = true;
	}

	bool Block::WasDestroyed() const
	{
		return is_destroyed;
	}

	void Block::MoveTo(int x, int y)
	{
		this->x = x;
		this->y = y;
		adjustPosition();
	}

	void Block::Move(int x, int y)
	{
		this->x += x;
		this->y += y;
		adjustPosition();
	}

	void Block::SetSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		adjustSize();
	}

	void Block::adjustSize()
	{
		if (width < 0)
		{
			width = 0;
		}
		if (height < 0)
		{
			height = 0;
		}

		adjustPosition();
	}

	void Block::adjustPosition()
	{
		//ブロックの位置は制限なし
	}
}
