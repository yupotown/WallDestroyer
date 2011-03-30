
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

		void MoveTo(int x, int y);	//絶対位置
		void Move(int x, int y);		//相対位置
		void SetMovableRange(int left, int top, int right, int bottom);
		void SetAngle(float angle);
		void SetRadius(int radius);
		void SetSpeed(float speed);

		int GetX() const;
		int GetY() const;
		float GetAngle() const;	//-π～π
		float GetSpeed() const;
		int GetRadius() const;
		int GetVx() const;	//X方向の速度
		int GetVy() const;	//Y方向の速度

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
