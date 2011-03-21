
#pragma once

class Ball
{
public:
	Ball();
	~Ball();

private:
	Ball(const Ball& rhs);
	const Ball& operator =(const Ball& rhs);

	double x, y;
};
