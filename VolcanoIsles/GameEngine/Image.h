#ifndef Image_H
#define Image_H
#include "Graphics.h"
#include <SDL.h>
#include "CollisionComputable.h"

namespace g
{

	class Image : public g::CollisionComputable
	{
	public:

		Image(int x, int y, const std::string& texture_name)
			: x_(x),
			y_(y), width_(0), height_(0), alpha_(255), rotation_(0), texture_(nullptr),
			texture_name_(texture_name)
		{
		}

		bool point_collision(int x, int y) override
		{
			return x > x_ && x< x_ + width_ && y> y_ && y < y_ + height_;
		}

		void draw(TexturePainter& painter, int x0, int y0) override
		{
			if (texture_ == nullptr)
			{
				texture_ = painter.get_texture_(texture_name_);
				SDL_QueryTexture(texture_, nullptr, nullptr, &width_, &height_);
			}
			painter.draw_texture(x_+x0,y_+y0,width_,height_,alpha_,texture_,rotation_);
		}
		double rotation() const
		{
			return rotation_;
		}

		void set_rotation(double rotation)
		{
			rotation_ = rotation;
		}


		int x() override {
			return x_;
		}
		int y() override {
			return y_;
		}
		void set_alpha(int alpha) {
			alpha_ = alpha;
		}

		int width() const
		{
			return width_;
		}

		int height() const
		{
			return height_;
		}


		void set_x(int x)
		{
			x_ = x;
		}

		void set_y(int y)
		{
			y_ = y;
		}
		int x_, y_;
		int width_;
		int height_;
		int alpha_;
		double rotation_;
		SDL_Texture* texture_;
		std::string texture_name_;
	};
}

#endif // Image_H

