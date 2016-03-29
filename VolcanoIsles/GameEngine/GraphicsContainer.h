#ifndef GraphicsContainer_H
#define GraphicsContainer_H



#include "Graphics.h"
#include <vector>
#include "TexturePainter.h"

namespace g
{
	
class GraphicsContainer :
	public Graphics
{
public:

	GraphicsContainer(int x, int y)
		: x_(x),
		  y_(y)
	{
	}

	virtual ~GraphicsContainer();
	void add_child(Graphics* g);
	void remove_child(Graphics* g);
	void draw(TexturePainter & painter, int x0, int y0) override;
	int x() override {
		return x_;
	}
	int y() override {
		return y_;
	}
private:
	std::vector<Graphics*> graphics_list_;
	int x_, y_;
	
};
}


#endif // GraphicsContainer_H

