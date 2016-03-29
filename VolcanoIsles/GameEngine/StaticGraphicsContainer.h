#ifndef StaticGraphicsContainer_H
#define StaticGraphicsContainer_H
#include "Graphics.h"
#include <memory>

namespace g
{

	class StaticGraphicsContainer :public Graphics
	{
	public:
		virtual ~StaticGraphicsContainer()
		{

		}

		StaticGraphicsContainer(int x, int y)
			: x_(x),
			y_(y)
		{
		}

		void draw(TexturePainter& painter, int x0, int y0) override
		{
			for (auto & gr: graphics_list_)
			{
				gr->draw(painter, x0 + x_, y0 + y_);
			}
		}

		void add_child(std::unique_ptr<Graphics> g)
		{
			graphics_list_.push_back(move(g));
		}

		int x() override
		{
			return x_;
		}

		int y() override
		{
			return y_;
		}

	private:
		int x_, y_;
		std::vector<std::unique_ptr<Graphics>> graphics_list_;

	};

}

#endif // StaticGraphicsContainer_H



