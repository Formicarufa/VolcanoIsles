﻿#ifndef GamePlanGraphics_H
#define GamePlanGraphics_H

#include "GameEngine/StaticGraphicsContainer.h"
#include "GameEngine/GraphicsContainer.h"
#include "GameNodeGraphics.h"
#include "GamePlan.h"
#include "FireBallGraphics.h"

class GamePlanGraphics: public g::GraphicsContainer
{
public:


	explicit GamePlanGraphics(GamePlan* gamePlan):GraphicsContainer(0,0),lines_(0, 0),fire_balls_graphics_(0,0),gamePlan_(gamePlan)
	{
		add_child(&lines_);
		draw_islands();
		add_child(&fire_balls_graphics_);
		draw_connecting_lines();
		update_fireball_positions();
	}

	void update_fireball_positions()
	{
		fire_balls_graphics_.clear();
		auto & fire_balls = gamePlan_->fire_balls();
		auto c = gameconst::island_size / 2;
		auto d = gameconst::fire_size / 2;
		for(auto & x : fire_balls)
		{
			auto node = x.node();
			std::unique_ptr<FireBallGraphics> gr = std::make_unique<FireBallGraphics>(node->x()+c-d, node->y()+c-d);
			fire_balls_graphics_.add_child(std::move(gr));
			;
		}
	}

	std::vector<std::unique_ptr<GameNodeGraphics>>& game_nodes()
	{
		return game_nodes_;
	}

private:
	void draw_islands()
	{
		const std::vector<std::unique_ptr<GameNode>>* game_nodes = gamePlan_->nodes();
		for (auto & x : *game_nodes)
		{
			auto g = std::make_unique<GameNodeGraphics>(x.get());
			add_child(g.get());
			game_nodes_.push_back(move(g));
		}
	}

	g::StaticGraphicsContainer lines_;
	std::vector<std::unique_ptr<GameNodeGraphics>> game_nodes_;
	g::StaticGraphicsContainer fire_balls_graphics_;
	GamePlan* gamePlan_;
	void connect_nodes(const GameNode& m, const GameNode& n);
	void draw_connecting_lines();

};


#endif // GamePlanGraphics_H