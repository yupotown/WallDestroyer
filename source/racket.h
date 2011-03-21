
#pragma once

namespace WallDestroyer
{
	class Racket
	{
	public:
		Racket();
		virtual ~Racket();

		virtual void Update() = 0;
		virtual void Draw() = 0;

		void SetMovableRange(int left, int top, int right, int bottom);
		void SetSize(int width, int height);
		void MoveTo(int x, int y);	//â‘ÎˆÊ’u
		void Move(int x, int y);	//‘Š‘ÎˆÊ’u

		int GetX() const;
		int GetY() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetMovableRangeLeft() const;
		int GetMovableRangeRight() const;
		int GetMovableRangeTop() const;
		int GetMovableRangeBottom() const;

	protected:
		void adjustPosition();
		void adjustSize();

		int x, y;
		int width, height;
		int range_left, range_right, range_top, range_bottom;

	private:
		Racket(const Racket& rhs);
		const Racket& operator =(const Racket& rhs);
	};
}
