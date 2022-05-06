#pragma once
#include <vector>

#include "Food.h"
#include "Wall.h"

class Arena
{
	std::vector<Wall> walls;
	std::vector<Food> foods;

	int width;
	int height;

public:

	enum WallType
	{
		NO_WALL,
		AROUND,
		RANDOM,
		RANDOM_AND_AROUND
	};

	Arena(int, int);
	~Arena();

	void create_wall(WallType, int);
	void create_food(int);

	bool wall_at(int, int) const;
	bool food_at(int, int, bool);

	std::vector<Wall> get_walls() { return walls; }
	std::vector<Food> get_foods() { return foods; }

private:
	void random_wall(int);
	void around_wall(int);
};

