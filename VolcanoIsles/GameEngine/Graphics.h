#ifndef Graphics_H
#define Graphics_H
#include "TexturePainter.h"

namespace g
{
	class Graphics
	{
	public:


		Graphics(): parent_(nullptr)
		{
		}

		virtual ~Graphics()
		{
		}

		virtual  void draw(TexturePainter & painter, int x0, int y0) = 0;
		virtual int x()=0;
		virtual int y()=0;

		Graphics* parent() const
		{
			return parent_;
		}

		///Called automatically by parent.
		void set_parent(Graphics* parent)
		{
			parent_ = parent;
		}

	private:
		Graphics* parent_;
	};


}




#endif // Graphics_H


