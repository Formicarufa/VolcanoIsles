#ifndef  DEF_GAME_H
#define DEF_GAME_H
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
class Game {
public:
	Game() : renderer_(nullptr), pWindow_(nullptr), running_(false) {}
	~Game() {

	}



	bool init(const char* title, int xpos, int ypos, int height,
		int width, int flags) {
		if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		{

			pWindow_ = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			if (pWindow_ != 0)
			{
				renderer_ = SDL_CreateRenderer(pWindow_, -1, SDL_RENDERER_PRESENTVSYNC );
			}
		}
		else
		{
			return false;
		}

		SDL_Surface* s = IMG_Load("assets/animate-alpha.png");
		texture_ = SDL_CreateTextureFromSurface(renderer_, s);
		SDL_FreeSurface(s);
		//SDL_QueryTexture(texture_, nullptr, nullptr, &rect_.w, &rect_.h);
		rect_.w = 128;
		rect_.h = 82;
		rect_.x = dest_rect_.x = rect_.y = dest_rect_.y = 0;
		dest_rect_.w = rect_.w*2;
		dest_rect_.h = rect_.h*2;
		return true;
	}

	void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		SDL_SetRenderDrawColor(renderer_, r, g, b, a);
	}

	void render() 
	{
		Uint8 r = 0;

		Uint8 g = 0;
		Uint8 b = 0;
		Uint8 a = 255;
		set_color(r, g, b, a);
		SDL_RenderClear(renderer_);
		SDL_RenderCopyEx(renderer_, texture_, &rect_, &dest_rect_,0,nullptr,SDL_FLIP_NONE);
		dest_rect_.x+=2;
		SDL_RenderPresent(renderer_);
	}
	void update()
	{
		rect_.x = 128 * static_cast<int>(SDL_GetTicks() /80 % 6);
	}
	void handleEvents()
	{

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running_ = false;
				break;
			default:
				break;
			}
		}
	}
	void clean() const
	{
		SDL_DestroyWindow(pWindow_);
		SDL_DestroyRenderer(renderer_);
		SDL_Quit();
		std::cout << "Exitting.";

	}
	bool is_running() const
	{
		return running_;
	}
	void run()
	{
		running_ = true;
		while (running_)
		{
			handleEvents();
			update();
			render();
		}
		clean();
	}
private:
	SDL_Renderer* renderer_;
	SDL_Window* pWindow_;
	bool running_;
	SDL_Texture* texture_;
	SDL_Rect rect_;
	SDL_Rect dest_rect_;



};
#endif // ! DEF_GAME_H

