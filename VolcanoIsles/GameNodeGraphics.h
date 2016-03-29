#pragma once
#include "GameEngine/Sprite.h"
#include "Owner.h"
#include "IslandType.h"
#include "GameConstants.h"

class GameNodeGraphics : public g::Sprite
{
public:

	GameNodeGraphics(int x, int y)
		: Sprite(x, y, "island_spritesheet"), owner_(NONE), island_type_(EMPTY)
	{
	}

	SDL_Rect get_source_rect() override;

	SDL_Rect get_destination_rect() override
	{
		return g::TexturePainter::rect(x(), y(), gameconst::island_size, gameconst::island_size);

	}

	void set_owner(Owner owner)
	{
		owner_ = owner;
	}
	void set_island_type(IslandType island_type)
	{
		island_type_ = island_type;
	}
private:
	Owner owner_;
	IslandType island_type_;
};
