#pragma once

#ifndef TexturePainter_H
#define TexturePainter_H
#include <string>
#include <unordered_map>
#include <SDL.h>

namespace g {
	class TexturePainter
	{
	public:

		TexturePainter(): renderer_(nullptr)
		{
		}

		TexturePainter(SDL_Renderer*  renderer) : renderer_(renderer)
		{

		}
		void set_renderer(SDL_Renderer* renderer)
		{
			renderer_ = renderer;
		}
		SDL_Texture* get_texture_(const std::string& name);
		void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

		void set_color(SDL_Color c)
		{
			set_color(c.r, c.g, c.b, c.a);
		}

		void draw_rectangle(int x, int y, int width, int height, const SDL_Color color);
		void draw_texture(int x, int y, int width, int height, Uint8 alpha, SDL_Texture* texture, double rotation) const;

		void draw_line(int x1, int y1, int x2, int y2, SDL_Color color)
		{
			set_color(color);
			SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
		}
		void draw_sprite(const SDL_Rect* source_rect, const SDL_Rect* destination_rect, SDL_Texture* texture, double rotation) const
		{
			SDL_RenderCopyEx(renderer_, texture, source_rect, destination_rect, rotation,nullptr,SDL_FLIP_NONE);
		}

		static SDL_Rect rect(int x, int y, int width, int height)
		{
			SDL_Rect rect;
			rect.x = x;
			rect.y = y;
			rect.w = width;
			rect.h = height;
			return rect;

		}
	private:
		SDL_Renderer* renderer_;
		std::unordered_map<std::string, SDL_Texture*> textures_;


	};
}
#endif // TexturePainter_H

