#pragma once
#include "GamePlan.h"
#include "GamePlanGraphics.h"
#include "VolcanoGameDirector.h"
#include "IslandMouseHandler.h"
#include "GameEngine/GameState.h"

class PlayerGameControl
{
public:

	explicit PlayerGameControl(g::GameState* game_state)
		: game_state_(game_state),
		island_graphics_(0,0),
		fireball_graphics_(0,0),
		selection_layer_(0,0)
	{
		island_graphics_.set_visible(false);
		fireball_graphics_.set_visible(false);
		
		selection_layer_.add_child(&island_graphics_);
		selection_layer_.add_child(&fireball_graphics_);
	}

	void activate(GamePlanGraphics* game_plan_graphics, VolcanoGameDirector* director, Player player)
	{
		game_plan_graphics->add_child(&selection_layer_);

		island_graphics_.set_owner(player);
		auto & game_nodes = game_plan_graphics->game_nodes();
		for (auto& node : game_nodes)
		{
			auto handler = std::make_unique<IslandMouseHandler>(node->node(), director, player, &fireball_graphics_, &island_graphics_);
			auto c = node->node_graphics().get();
			game_state_->addMouseClickHandler(c, handler.get());
			game_state_->addMouseMotionHandler(c, handler.get());
			island_mouse_handlers_.push_back(std::move(handler));
			
		}
	}
	void deactivate(GamePlanGraphics* game_plan_graphics)
	{
		game_plan_graphics->remove_child(&selection_layer_);
		for (auto& i : island_mouse_handlers_)	
		{
			game_state_->removeMouseClickHandler(i.get());
			game_state_->removeMouseMotionHandler(i.get());
		}
	}

private:
	g::GameState* game_state_;
	std::vector<std::unique_ptr<IslandMouseHandler>> island_mouse_handlers_;
	IslandGraphics island_graphics_;
	FireBallGraphics fireball_graphics_;
	g::GraphicsContainer  selection_layer_;
};
