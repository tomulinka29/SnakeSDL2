#include "Snake.h"

#include <iostream>

Snake::Snake(int posX, int posY, int width, int height) : dir(UP)
{
	headPos = std::pair<int, int>(posX, posY);
	partSize = std::pair<int, int>(width, height);
	parts.push_back(std::make_shared<SnakePart>(headPos.first, headPos.second));
}

Snake::~Snake() = default;

void Snake::move()
{
	for (auto current = parts.rbegin(); current != parts.rend(); ++current)
	{
		if (current != parts.rbegin())
		{
			auto previous = prev(current, 1);
			(*previous)->posX = (*current)->posX;
			(*previous)->posY = (*current)->posY;
		}
	}

	move_head(*parts.begin(), dir);

}

bool Snake::collision( const Arena& arena) const
{
	for (auto current = parts.begin(); current != parts.end(); ++current)
	{
		if (current != parts.begin())
			if (*(*current) == *(*parts.begin()))
				return true;

		if (arena.wall_at((*current)->posX, (*current)->posY))
			return true;
	}
	return false;
}

bool Snake::food_collision(Arena& arena) const
{
	if (arena.food_at(headPos.first, headPos.second, true))
		return true;
	return false;
}



void Snake::move_head(const std::shared_ptr<SnakePart>& part, const Direction dir)
{
	switch(dir)
	{
	case DOWN:
		part->posY += partSize.second; break;
	case UP:
		part->posY -= partSize.second; break;
	case LEFT:
		part->posX -= partSize.first; break;
	case RIGHT:
		part->posX += partSize.first; break;
	}
	headPos = std::pair<int, int>(part->posX, part->posY);
}

void Snake::add_part(int count)
{
	for (int i = 0; i < count; i++)
		add_part();
}

void Snake::add_part()
{
	auto lastIT = parts.end();
	--lastIT;
	parts.push_back(std::make_shared<SnakePart>((*lastIT)->posX, (*lastIT)->posY));
}


void Snake::set_direction(const Direction new_dir)
{
	if ((new_dir == UP && dir == DOWN) || (new_dir == DOWN && dir == UP)) return;
	if ((new_dir == LEFT && dir == RIGHT) || (new_dir == RIGHT && dir == LEFT)) return;
	dir = new_dir;
}


