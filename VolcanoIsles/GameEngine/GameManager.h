#ifndef GameManager_H
#define GameManager_H
#include <memory>
#include "GameState.h"
#include <SDL.h>
#include "TexturePainter.h"
#include "Common.h"
#include "Graphics.h"

namespace g
{

	using GameStatePtr = std::unique_ptr<GameState>;
	class GameManager
	{
	public:

		GameManager(std::string game_name, int height, int width)
			: current_state_(), name_(game_name), height_(height), window_(nullptr), renderer_(nullptr), running_(true), width_(width), painter_(nullptr),background_color_(colors::black())
		{

		}

		void start(GameStatePtr  initial_state);

		void stop();

		GameStatePtr change_state(GameStatePtr new_state);

		void set_background_color(const SDL_Color background_color)
		{
			background_color_ = background_color;
		}

	private:
		GameStatePtr current_state_;
		int width_;
		std::string name_;
		int height_;
		SDL_Window* window_;
		SDL_Renderer* renderer_;
		bool running_;
		TexturePainter painter_;
		SDL_Color background_color_;
		bool init();

		void handle_mouse_click(SDL_MouseButtonEvent& button)
		{
			auto & handlers = current_state_->click_handlers();
			auto copy(handlers);
			for (auto h: copy)
			{
				CollisionComputable* testedObject = h.first;
				auto x = button.x;
				auto y = button.y;
				Graphics* parent = testedObject->parent();
				while (parent!= nullptr)
				{
					x -= parent->x();
					y -= parent->y();
					parent = parent->parent();
				}
				if (testedObject->point_collision(x,y))
				{
					h.second->handle_mouse_event(x, y);
				}
			}
		}

		void handle_key_down(SDL_Keysym& key)
		{
			auto & handlers = current_state_->key_handlers();
			auto copy(handlers);
			for (auto h : copy)
			{
				h->handle_key_event(key);
			}
		}

		void handle_events()
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					running_ = false;
					break;
				case SDL_MOUSEBUTTONUP:
					handle_mouse_click(event.button);
					break;
				case SDL_KEYDOWN:
					handle_key_down(event.key.keysym);
					break;
				}
			}
		}

		void update()
		{
			painter_.set_color(background_color_);
			auto & actions = current_state_->actions_vector();
			std::vector<UpdateAction*> copy(actions);
			for (auto action : copy)
			{
				action->updateAction();
			}
		}

		void render()
		{
			SDL_RenderClear(renderer_);
			auto container = current_state_->graphics_container();
			container.draw(painter_,0,0);
			SDL_RenderPresent(renderer_);
		}

		void clean();

		void run();
	};

}

#endif // GameManager_H

