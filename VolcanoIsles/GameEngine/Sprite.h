#ifndef Sprite_H
#define Sprite_H
#include "Graphics.h"
#include <SDL.h>
namespace g
{
	class Sprite : public Graphics
	{


	public:
		void draw(TexturePainter& painter, int x0, int y0) override
		{
			if (texture_ == nullptr)
			{
				texture_=painter.get_texture_(texture_name);
			}
			auto source_rect = get_source_rect();
			auto destination_rect = get_destination_rect();
			destination_rect.x += x0;
			destination_rect.y += y0;
			painter.draw_sprite(&source_rect, &destination_rect, texture_, rotation_);
		}

		int x() override
		{
			return x_;
		}

		int y() override
		{
			return y_;
		}
		virtual SDL_Rect get_source_rect() = 0;
		virtual SDL_Rect get_destination_rect() = 0;
		double rotation() const
		{
			return rotation_;
		}

		void set_rotation(double rotation)
		{
			rotation_ = rotation;
		}
		virtual ~Sprite()
		{

		}
	protected:
		Sprite(int x, int y, const std::string& texture_name)
			: x_(x),
			y_(y), rotation_(0), texture_(nullptr),
			texture_name(texture_name)
		{
		}
	private:
		int x_, y_;
		double rotation_;
		SDL_Texture* texture_;
		std::string texture_name;
	
	};

}

#endif // Sprite_H


