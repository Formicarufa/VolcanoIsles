#ifndef KeyHandler_H
#define KeyHandler_H
#include <SDL.h>
namespace g
{
	class KeyHandler
	{
	public:
		virtual ~KeyHandler()
		{
		}

		virtual void handle_key_event(SDL_Keysym& key) = 0;
	};

}




#endif // KeyHandler_H


