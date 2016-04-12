#ifndef PlayerGameControl_h__
#define PlayerGameControl_h__

#include "GamePlan.h"
#include "GamePlanGraphics.h"
#include "VolcanoGameDirector.h"
#include "IslandMouseHandler.h"
#include "GameEngine/GameState.h"
#include "GameEngine/Button.h"

class PlayerGameControl
{
public:

	explicit PlayerGameControl(g::GameState* game_state)
		: game_state_(game_state),
		island_graphics_(0, 0),
		fireball_graphics_(0, 0),
		selection_layer_(0, 0),
		game_plan_graphics_(nullptr),
		start_rotation_button_(gameconst::WIDTH / 2 - gameconst::island_size / 2, gameconst::HEIGHT - gameconst::island_size, "rotate_island", game_state_)
		
	{
		island_graphics_.set_visible(false);
		fireball_graphics_.set_visible(false);

		selection_layer_.add_child(&island_graphics_);
		selection_layer_.add_child(&fireball_graphics_);
		selection_layer_.add_child(&start_rotation_button_);
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
	void deactivate()
	{
		game_plan_graphics_->remove_child(&selection_layer_);
		remove_island_actions_handlers();
		island_mouse_handlers_.clear();
	}

private:
	g::GameState* game_state_;
	std::vector<std::unique_ptr<IslandMouseHandler>> island_mouse_handlers_;
	IslandGraphics island_graphics_;
	FireBallGraphics fireball_graphics_;
	g::GraphicsContainer  selection_layer_;
	GamePlanGraphics* game_plan_graphics_;
	g::Button start_rotation_button_;
	void remove_island_actions_handlers()
	{
		for (auto& i : island_mouse_handlers_)
		{
			game_state_->removeMouseClickHandler(i.get());
			game_state_->removeMouseMotionHandler(i.get());
		}
	}

	///Warning: works only providing the game plan hasn't changed. (Only reassigns old handlers.)
	void add_island_actions_handlers()
	{
		auto & game_nodes = game_plan_graphics_->game_nodes();

		auto it1 = island_mouse_handlers_.begin();
		auto it2 = game_nodes.begin();
		for (; it1 != island_mouse_handlers_.end() && it2 != game_nodes.end(); it1++, it2++)
		{
			auto i = it1->get();
			auto n = (*it2)->node_graphics().get();
			game_state_->addMouseClickHandler(n, i);
			game_state_->addMouseMotionHandler(n, i);
		}
	}
};
#endif // PlayerGameControl_h__
