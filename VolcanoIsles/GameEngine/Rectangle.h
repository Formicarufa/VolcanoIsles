#ifndef Rectangle_H
#define Rectangle_H
#include "Graphics.h"
#include <SDL.h>
#include "Common.h"
#include "CollisionComputable.h"

namespace g
{
class Rectangle :  public CollisionComputable
{
public:
	void draw(TexturePainter& painter, int x0, int y0) override
	{
		painter.draw_rectangle(x_ + x0, y_ + y0, width_, height_, color_);
	}

	bool point_collision(int x, int y) override
	{
		return x > x_ && x< x_ + width_ && y> y_ && y < y_ + height_;
	}

	Rectangle(int x, int y, int width, int height, const SDL_Color& color)
		: x_(x),
		  y_(y),
		  width_(width),
		  height_(height),
		  color_(color)
	{
	}

	Rectangle(int x, int y, int width, int height)
		: x_(x),
		  y_(y),
		  width_(width),
		  height_(height),
		color_(colors::white())
	{
	}
	int x() override {
		return x_;
	}
	int y() override {
		return y_;
	}

	int width() const;
	void set_width(int width);
	int height() const;
	void set_height(int height);
private:
	int x_, y_;
	int width_, height_;
	SDL_Color color_;
};
	

}

#endif // Rectangle_H



