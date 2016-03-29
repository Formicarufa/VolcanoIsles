#include "GraphicsContainer.h"
#include "Common.h"
#include "TexturePainter.h"




g::GraphicsContainer::~GraphicsContainer()
{
}

void g::GraphicsContainer::add_child(Graphics* g)
{
	graphics_list_.push_back(g);
	g->set_parent(this);
}

void g::GraphicsContainer::remove_child(Graphics* g)
{
	common::remove(graphics_list_, g);
	g->set_parent(nullptr);
}

 void g::GraphicsContainer::draw(TexturePainter & painter, int x0, int y0) 
{
	for (auto gr : graphics_list_)
	{
		gr->draw(painter,x0+x_,y0+y_);
	}
}
