
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

		void Bounce(double wall_angle);

		void MoveTo(double x, double y);	//��Έʒu
		void Move(double x, double y);		//���Έʒu
		void SetMovableRange(int left, int top, int right, int bottom);
		void SetAngle(double angle);
		void SetSpeed(double speed);

		double GetX() const;
		double GetY() const;
		double GetAngle() const;
		double GetSpeed() const;
		double GetRadius() const;
		double GetVx() const;	//X�����̑��x
		double GetVy() const;	//Y�����̑��x

	protected:
		void adjustSize();
		void adjustPosition();
		void adjustAngle();

		void calcSpeedXY();
		void calcAngle();
		void calcSpeed();
		void calcVector();

		double x, y;
		double angle;
		double speed;
		double radius;

		int range_left, range_right, range_top, range_bottom;

		double vx, vy;

	private:
		Ball(const Ball& rhs);
		const Ball& operator =(const Ball& rhs);
	};
}
