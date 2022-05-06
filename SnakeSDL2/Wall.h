#pragma once
class Wall
{
	const int posX;
	const int posY;
public:
	Wall(int x, int y) : posX(x), posY(y)
	{
	}

	int get_posX() { return posX; }
	int get_posY() { return posY; }
};

