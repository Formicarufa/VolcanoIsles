#pragma once
#include "GameEngine/MouseHandler.h"
#include "GameEngine/MouseMotionHandler.h"
#include "VolcanoGameDirector.h"
#include "IslandGraphics.h"
#include "FireBallGraphics.h"

class IslandMouseHandler : public g::MouseHandler, public g::MouseMotionHandler
{
public:

	IslandMouseHandler(GameNode* my_node, VolcanoGameDirector* director, Player player,
		FireBallGraphics* fireball_graphics, IslandGraphics* island_graphics)
		: my_node_(my_node),
		director_(director),
		player_(player),
		island_graphics_(island_graphics),
		fireball_graphics_(fireball_graphics)
	{

	}

	void handle_mouse_event(int x, int y) override
	{
		if (director_->player_on_turn() == player_)
		{
			if (my_node_->owner() == player_)
			{
				if (director_->can_create_volcano(my_node_)) {
					director_->create_volcano(my_node_);
				}
				else if (my_node_->island_type() == VOLCANO)
				{
					director_->produce_fire(my_node_);
				}
			}
			else if (director_->can_occupy(my_node_))
			{
				director_->ocuppy_island(my_node_);
			}
		}
	}

	void mouse_over() override
	{


		if (director_->player_on_turn() == player_)
		{
			int x = my_node_->x();
			int y = my_node_->y();
			if (my_node_->owner() == player_)
			{
				if (director_->can_create_volcano(my_node_)) {
					island_graphics_->set_island_type(VOLCANO);
					island_graphics_->set_x(x);
					island_graphics_->set_y(y);
					island_graphics_->set_visible(true);
				}
				else if (my_node_->island_type() == VOLCANO)
				{
					fireball_graphics_->set_x(x);
					fireball_graphics_->set_y(y);
					fireball_graphics_->set_visible(true);
				}
			}
			else if (director_->can_occupy(my_node_))
			{
				island_graphics_->set_island_type(EMPTY);
				island_graphics_->set_x(x);
				island_graphics_->set_y(y);
				island_graphics_->set_visible(true);
			}
		}
	}

	void mouse_out() override
	{
		island_graphics_->set_visible(false);
		fireball_graphics_->set_visible(false);
	}

private:
	GameNode* my_node_;
	VolcanoGameDirector* director_;
	Player player_;
	IslandGraphics* island_graphics_;
	FireBallGraphics* fireball_graphics_;
};
