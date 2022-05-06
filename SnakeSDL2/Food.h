#pragma once
class Food
{
	int posX;
	int posY;
public:
	Food(int x, int y) : posX(x), posY(y)
	{
		
	}

	int get_posX() { return posX; }
	int get_posY() { return posY; }

	bool operator == (const Food& rhs)
	{
		return posX == rhs.posX && posY == rhs.posY;
	}

	Food& operator = (const Food& rhs)
	{
		posX = rhs.posX;
		posY = rhs.posY;
		return *this;
	}
};