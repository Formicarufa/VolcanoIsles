#ifndef Line_H
#define Line_H
#include "Graphics.h"
#include "Common.h"

namespace g
{


	class Line : public Graphics 
	{
	public:

		Line(int x1, int x2, int y1, int y2)
			: x1_(x1),
			  x2_(x2),
			  y1_(y1),
			  y2_(y2),
				color_(colors::white())
		{
		}

		Line(int x1, int x2, int y1, int y2, const SDL_Color& color)
			: x1_(x1),
			  x2_(x2),
			  y1_(y1),
			  y2_(y2),
			  color_(color)
		{
		}

		void draw(TexturePainter& painter, int x0, int y0) override
		{
			painter.draw_line(x0+x1_, y0+y1_, x0+x2_, y0+y2_,color_);
		}
		SDL_Color color() const
		{
			return color_;
		}

		void set_color(const SDL_Color color)
		{
			color_ = color;
		}
		int x() override {
			return x1_;
		}
		int y() override {
			return y1_;
		}
	private:
		int x1_, x2_, y1_, y2_;
		SDL_Color color_;
	};


}

#endif // Line_H
