#include "TexturePainter.h"
#include <SDL_image.h>

SDL_Texture* g::TexturePainter::get_texture_(const std::string& name)
{
	auto pair = textures_.find(name);
	if (pair != textures_.end())
	{
		return pair->second;
	}
	std::string filename ="assets/" +  name + ".png";
	SDL_Surface*	surface = IMG_Load(filename.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
	textures_[name] = texture;
	return texture;
}

void g::TexturePainter::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void g::TexturePainter::draw_rectangle(int x, int y, int width, int height, const SDL_Color color)
{
	set_color(color);
	SDL_Rect rec = rect(x, y, width, height);
	SDL_RenderDrawRect(renderer_, &rec);
}

void g::TexturePainter::draw_texture(int x, int y, int width, int height,int alpha, SDL_Texture* texture, double rotation)
{
	SDL_SetTextureAlphaMod(texture, alpha);
	SDL_Rect source = rect(0, 0, width, height);
	SDL_Rect r = rect(x, y, width, height);
	SDL_RenderCopyEx(renderer_, texture, &source, &r, rotation, nullptr, SDL_FLIP_NONE);
}
