#ifndef IslandGraphics_H
#define IslandGraphics_H

#include "GameEngine/Sprite.h"
#include "IslandType.h"
#include "GameConstants.h"
#include "Player.h"

class IslandGraphics : public g::Sprite
{
public:

	IslandGraphics(int x, int y)
		: Sprite(x, y, "island_spritesheet"), owner_(Player::NONE), island_type_(IslandType::EMPTY)
	{
	}

	SDL_Rect get_source_rect() override;

	SDL_Rect get_destination_rect() override
	{
		return g::TexturePainter::rect(x(), y(), gameconst::island_size, gameconst::island_size);

	}

	void set_owner(Player owner)
	{
		owner_ = owner;
	}
	void set_island_type(IslandType island_type)
	{
		island_type_ = island_type;
	}
private:
	Player owner_;
	IslandType island_type_;
};


#endif // IslandGraphics_H
