#include "Arena.h"

#include <ctime>

Arena::Arena(int sizeX, int sizeY) : width(sizeX), height(sizeY)
{
	srand(time(nullptr));
}

Arena::~Arena()
{
	srand(time(nullptr));
}

void Arena::create_food(int thickness)
{
	int x = thickness * ( rand() % ( (width/thickness) - 2) )   + thickness * 2;
	int y = thickness * ( rand() % ( (height / thickness) - 2)) + thickness * 2;
	foods.emplace_back(Food(x, y));
}



void Arena::create_wall(const WallType wall_type, const int thickness)
{
	switch (wall_type)
	{
	case AROUND:
		around_wall(thickness);
		break;

	default:
		return;
	}
}

void Arena::around_wall(int thickness)
{
	for (int x = 0; x < width; x++)
	{
		walls.emplace_back(Wall(x, 0));
		walls.emplace_back(Wall(x, height - thickness));
	}

	for (int y = thickness; y < height-thickness; y++)
	{
		walls.emplace_back(Wall(0, y));
		walls.emplace_back(Wall(width-thickness, y));
	}
}

bool Arena::food_at(int x, int y, bool remove_on_collision)
{
	for (auto food : foods)
	{
		if (food.get_posX() == x && food.get_posY() == y)
		{
			if (remove_on_collision)
				foods.erase( std::remove(foods.begin(), foods.end(), food) );
			return true;
		}
	}
	return false;
}


bool Arena::wall_at(int x, int y) const
{
	for (auto wall : walls)
	{
		if (wall.get_posX() == x && wall.get_posY() == y)
			return true;
	}
	return false;
}



