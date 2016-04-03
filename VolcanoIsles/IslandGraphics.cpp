#include "IslandGraphics.h"
SDL_Rect IslandGraphics::get_source_rect()
{
	int c = gameconst::island_size;
	int x = 0;
	switch (owner_)
	{
	case NONE:
		x = 0;
		break;
	case PLAYER:
		x = 2 * c;
		break;
	case COMPUTER:
		x = c;
		break;
	default:
		break;
	}
	int y = 0;
	switch (island_type_)
	{
	case EMPTY:
		y = c;
		break;
	case VOLCANO:
		y = 2 * c; 
		break;
	case BASE:
		y = 0; 
		break;
	default: break;
	}
	return g::TexturePainter::rect(x, y, c, c);
}
