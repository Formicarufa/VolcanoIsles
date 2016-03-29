#include "GameManager.h"
#include "TexturePainter.h"

void g::GameManager::start(GameStatePtr initial_state)
{
	current_state_ = std::move(initial_state);
	init();
	run();
}

void g::GameManager::stop()
{
	running_ = false;
}

g::GameStatePtr g::GameManager::change_state(GameStatePtr new_state)
{
	GameStatePtr ret = std::move(current_state_);
	current_state_ = std::move(new_state);
	return std::move(ret);
}

bool g::GameManager::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		window_ = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, 0);
		if (window_ != nullptr)
		{
			renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);
		}
		if (renderer_ != nullptr) {
			painter_.set_renderer(renderer_);
			return true;
		}
	}
	return false;
}

void g::GameManager::clean()
{
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	window_ = nullptr;
	renderer_ = nullptr;
			SDL_Quit();
}

void g::GameManager::run()
{
	running_ = true;
	while(running_)
	{
		handle_events();
		update();
		render();
	}
	clean();
}
