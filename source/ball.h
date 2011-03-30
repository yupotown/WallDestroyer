
#pragma once

namespace WallDestroyer
{
	class Ball
	{
	public:
		Ball();
		~Ball();

		virtual void Update();
		virtual void Draw() = 0;

		void Bounce(float wall_angle);

		void MoveTo(int x, int y);	//��Έʒu
		void Move(int x, int y);		//���Έʒu
		void SetMovableRange(int left, int top, int right, int bottom);
		void SetAngle(float angle);
		void SetRadius(int radius);
		void SetSpeed(float speed);

		int GetX() const;
		int GetY() const;
		float GetAngle() const;	//-�΁`��
		float GetSpeed() const;
		int GetRadius() const;
		int GetVx() const;	//X�����̑��x
		int GetVy() const;	//Y�����̑��x

	protected:
		void adjustSize();
		void adjustPosition();
		void adjustAngle();

		void calcSpeedXY();
		void calcAngle();
		void calcSpeed();
		void calcVector();

	private:
		const int unit;

		int x, y;
		float angle;
		int speed;
		int radius;

		int range_left, range_right, range_top, range_bottom;

		int vx, vy;

		Ball(const Ball& rhs);
		const Ball& operator =(const Ball& rhs);
	};
}
