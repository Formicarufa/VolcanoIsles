#pragma once
#include "GameEngine/Sprite.h"
#include "GameConstants.h"
#include "Player.h"

class PlayerIcon: public g::Sprite
{
public:
	PlayerIcon(int x, int y)
		: Sprite(x, y, "player_icon"), player_(Player::NONE)
	{
	}

	SDL_Rect get_source_rect() override
	{
		int x = 0;
		switch (player_)
		{
		case Player::NONE:
			x = 2;
			break;
		case Player::BLUE:
			x = 0;
			break;
		case Player::RED:
			x = 1;
			break;
		default:
			break;
		}
		auto size = gameconst::player_icon_size;
		return g::TexturePainter::rect(size*x, 0, size, size);
	}

	void set_player(Player player)
	{
		player_ = player;
	}

	SDL_Rect get_destination_rect() override
	{
		return g::TexturePainter::rect(x(), y(), gameconst::player_icon_size, gameconst::player_icon_size);
	}
private: 
	Player player_;
};
