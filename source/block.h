
#pragma once

#include "ball.h"

namespace WallDestroyer
{
	class Block
	{
	public:
		Block();
		~Block();

		virtual void Update();
		virtual void Draw() = 0;

		//�{�[�������������Ƃ��ɌĂяo�����
		virtual void OnBallHit(Ball& ball);
		virtual bool WasDestroyed() const;

		void MoveTo(int x, int y);	//��Έʒu
		void Move(int x, int y);	//���Έʒu
		void SetSize(int width, int height);

	protected:
		void adjustSize();
		void adjustPosition();

		int x, y;
		int width, height;

		bool is_destroyed;

	private:
		Block(const Block& rhs);
		const Block& operator =(const Block& rhs);
	};
}
