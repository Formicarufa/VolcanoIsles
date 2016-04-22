#include "IslandGraphics.h"
SDL_Rect IslandGraphics::get_source_rect()
{
	int c = gameconst::island_size;
	int x = 0;
	switch (owner_)
	{

	case Player::NONE:
		x = 0;
		break;
	case Player::BLUE:
		x = 2 * c;
		break;
	case Player::RED:
		x = c;
		break;
	default:
		break;
	}
	int y = 0;
	switch (island_type_)
	{
	case IslandType::EMPTY:
		y = c;
		break;
	case IslandType::VOLCANO:
		y = 2 * c; 
		break;
	case IslandType::BASE:
		y = 0; 
		break;
	default: break;
	}
	return g::TexturePainter::rect(x, y, c, c);
}
