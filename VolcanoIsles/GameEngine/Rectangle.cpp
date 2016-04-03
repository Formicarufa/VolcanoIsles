#include "Rectangle.h"

int g::Rectangle::width() const
{
	return width_;
}

void g::Rectangle::set_width(int width)
{
	width_ = width;
}

int g::Rectangle::height() const
{
	return height_;
}

void g::Rectangle::set_height(int height)
{
	height_ = height;
}
