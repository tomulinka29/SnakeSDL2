#include "Game.h"
#include <iostream>
Game::Game()
{
	window = nullptr;
	renderer = nullptr;
}

Game::~Game()
{
	
}

void Game::update()
{
	std::cout << "A" << std::endl;
}


void Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << "Error on Initialization" << std::endl;

	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	if (window)
		std::cout << "Window created" << std::endl;

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer)
	{
		std::cout << "Renderer created" << std::endl;
		SDL_SetRenderDrawColor(renderer, 34, 47, 91, 255);
	}
	isRunning = true;
	
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
		break;

		default:
		break;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::running()
{
	return isRunning;
}