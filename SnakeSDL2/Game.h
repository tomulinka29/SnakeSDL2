#pragma once
#include <SDL.h>
class Game
{
private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	bool isRunning = false;

public:
	Game();
	~Game();
	void init();
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();
};

