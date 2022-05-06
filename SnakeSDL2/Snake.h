#pragma once
#include <list>
#include <memory>

#include "Arena.h"

struct SnakePart
{
	int posX;
	int posY;

public:
	SnakePart(int x, int y) : posX(x), posY(y){}

	bool operator == (const SnakePart rhs)
	{
		return posX == rhs.posX && posY == rhs.posY;
	}
};

class Snake
{
	std::list< std::shared_ptr<SnakePart>> parts;
	std::pair<int, int> partSize;

public:
	std::pair<int, int> headPos;
	enum Direction
	{
		DOWN, LEFT, RIGHT, UP
	};

	Snake(int, int, int, int);
	~Snake();

	void move();
	void add_part();
	void add_part(int);


	std::list<std::shared_ptr<SnakePart>> get_parts()
	{
		return parts;
	}

	void set_direction(const Direction);

	bool collision(const Arena& arena) const;

	bool food_collision(Arena& arena) const;

private:
	Direction dir;
	void move_head(const std::shared_ptr<SnakePart>&, const Direction);
};

