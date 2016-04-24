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

	void handle_mouse_event(g::CollisionComputable*, int , int ) override
	{
		if (director_->player_on_turn() == player_)
		{
			if (my_node_->owner() == player_)
			{
				if (director_->can_create_volcano(*my_node_)) {
					director_->create_volcano(my_node_);
					mouse_out();
				}
				else if (director_->can_produce_fire(*my_node_))
				{
					director_->produce_fire(my_node_);
					mouse_out();
				}
			}
			else if (director_->can_occupy(*my_node_))
			{
				director_->ocuppy_island(my_node_);
				mouse_out();
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
				if (director_->can_create_volcano(*my_node_)) {
					island_graphics_->set_island_type(IslandType::VOLCANO);
					island_graphics_->set_x(x);
					island_graphics_->set_y(y);
					island_graphics_->set_visible(true);
				}
				else if (director_->can_produce_fire(*my_node_))
				{
					fireball_graphics_->set_x(x);
					fireball_graphics_->set_y(y);
					fireball_graphics_->set_visible(true);
				}
			}
			else if (director_->can_occupy(*my_node_))
			{
				island_graphics_->set_island_type(IslandType::EMPTY);
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
