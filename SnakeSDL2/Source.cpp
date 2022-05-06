#include <iostream>
#include <ostream>

#include "Arena.h"
#include "Game.h"
#include "Snake.h"

int main(int args, char * argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window * window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	while (true)
	{
		SDL_Event e;

		bool running = true;
		std::shared_ptr<Snake> snake = std::make_shared<Snake>(250, 250, 10, 10);
		snake->add_part(1);


		Arena arena(500, 500);
		arena.create_wall(Arena::AROUND, 10);
		arena.create_food(10);
		bool menu = true;
		while (menu)
		{
			SDL_Rect button{ 150, 200, 200, 50 };
			SDL_SetRenderDrawColor(renderer, 34, 47, 91, 255);
			SDL_RenderFillRect(renderer, &button);

			int x, y;
			Uint32 buttons;
			SDL_PumpEvents();
			buttons = SDL_GetMouseState(&x, &y);

			if ((buttons & SDL_BUTTON_LMASK) != 0) {
				if (x >= button.x && y >= button.y && x <= button.x + button.w && y <= button.y + button.h)
				{
					SDL_Log("Game started");
					menu = false;
				}
			}

			SDL_RenderPresent(renderer);
			SDL_Delay(30);
		}

		SDL_Delay(200);

		while (running)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT) { running = false; }
				if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_DOWN) { snake->set_direction(Snake::DOWN); }
					if (e.key.keysym.sym == SDLK_UP) { snake->set_direction(Snake::UP); }
					if (e.key.keysym.sym == SDLK_LEFT) { snake->set_direction(Snake::LEFT); }
					if (e.key.keysym.sym == SDLK_RIGHT) { snake->set_direction(Snake::RIGHT); }
				}
			}
			//MOVE
			snake->move();
			if (snake->collision(arena))
			{
				running = false;
				SDL_Delay(300);
			}

			if (snake->food_collision(arena))
			{
				snake->add_part();
				arena.create_food(10);
			}

			//Clear
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);


			//Draw snake
			SDL_SetRenderDrawColor(renderer, 34, 47, 91, 255);
			for (const auto& part : snake->get_parts())
				SDL_RenderFillRect(renderer, new SDL_Rect{ part->posX, part->posY, 10, 10 });


			//Draw arena
			//walls
			SDL_SetRenderDrawColor(renderer, 148, 147, 45, 255);
			for (auto& wall : arena.get_walls())
				SDL_RenderFillRect(renderer, new SDL_Rect{ wall.get_posX() , wall.get_posY(), 10, 10 });
			//food
			SDL_SetRenderDrawColor(renderer, 140, 92, 40, 255);
			for (auto& food : arena.get_foods())
				SDL_RenderFillRect(renderer, new SDL_Rect{ food.get_posX() , food.get_posY(), 10, 10 });


			SDL_RenderPresent(renderer);
			SDL_Delay(30);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
	

	return 0;

}
