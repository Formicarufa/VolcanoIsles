#ifndef MouseHandler_H
#define MouseHandler_H

namespace g
{
	class MouseHandler
	{
	public:
		virtual ~MouseHandler()
		{
		}

		virtual void handle_mouse_event(int x, int y) = 0;
	};

}

#endif // MouseHandler_H



