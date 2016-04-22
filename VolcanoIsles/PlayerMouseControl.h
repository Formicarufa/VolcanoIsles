#ifndef PlayerMouseControl_h__
#define PlayerMouseControl_h__

#include "GamePlanGraphics.h"
#include "VolcanoGameDirector.h"
#include "IslandMouseHandler.h"
#include "GameEngine/GameState.h"
#include "GameEngine/Button.h"
#include "RotationControl.h"
#include "AbstractGameControl.h"

class PlayerMouseControl:public AbstractGameControl
{
public:

	explicit PlayerMouseControl(g::GameState* game_state)
		: AbstractGameControl(game_state), island_graphics_(0, 0),
		fireball_graphics_(0, 0),
		selection_layer_(0, 0),
		start_rotation_button_(0,0, "rotate_island", game_state),
		buttons_(gameconst::WIDTH / 2 - gameconst::button_size, gameconst::HEIGHT - gameconst::button_size), 
		skip_turn_button_(gameconst::button_size,0,"skip_turn",game_state),
		 is_active_(false), rotation_btn_handler_(this,game_state), skip_turn_handler_()

	{
		island_graphics_.set_visible(false);
		fireball_graphics_.set_visible(false);
		buttons_.set_visible(false);
		selection_layer_.add_child(&island_graphics_);
		selection_layer_.add_child(&fireball_graphics_);
		buttons_.add_child(&start_rotation_button_);
		buttons_.add_child(&skip_turn_button_);
		selection_layer_.add_child(&buttons_);
	}


	

	

	void turn_started() override
	{
		if (is_active_) return;
		is_active_ = true;
		selection_layer_.set_visible(true);
		display_buttons();
		auto & game_nodes = game_plan_graphics()->game_nodes();
		for (auto& node : game_nodes)
		{
			auto handler = std::make_unique<IslandMouseHandler>(node->node(), director(), player(), &fireball_graphics_, &island_graphics_);
			auto c = node->node_graphics().get();
			game_state()->add_mouse_click_handler(c, handler.get());
			game_state()->add_mouse_motion_handler(c, handler.get());
			island_mouse_handlers_.push_back(std::move(handler));
		}
	}

	void hide_buttons()
	{
		buttons_.set_visible(false);
		start_rotation_button_.remove_handler(&rotation_btn_handler_);
		skip_turn_button_.remove_handler(&skip_turn_handler_);
	}

	void turn_ended() override
	{
		if (!is_active_) return;
		selection_layer_.set_visible(false);
		hide_buttons();
		remove_island_actions_handlers();
		island_mouse_handlers_.clear();
		if (rotation_btn_handler_.rot_.is_active())
		{
			rotation_btn_handler_.rot_.deactivate();
		}
		is_active_ = false;
	}

	void initialized() override
	{
		island_graphics_.set_owner(player());
		game_plan_graphics()->add_child(&selection_layer_);
		rotation_btn_handler_.initialize(game_plan_graphics(), player());
		skip_turn_handler_.initialize(director());
	}

	void display_buttons()
	{
		buttons_.set_visible(true);
		start_rotation_button_.add_click_handler(&rotation_btn_handler_);
		skip_turn_button_.add_click_handler(&skip_turn_handler_);
	}

	void reactivate()
	{
		display_buttons();
		add_island_actions_handlers();
	}
	void rotate_island(GameNode* rotated, GameNode* new_direction) const
	{
		director()->change_direction(rotated, new_direction);
	}
	void pause()
	{
		hide_buttons();
		remove_island_actions_handlers();
	}
private:
	std::vector<std::unique_ptr<IslandMouseHandler>> island_mouse_handlers_;
	IslandGraphics island_graphics_;
	FireBallGraphics fireball_graphics_;
	g::GraphicsContainer  selection_layer_;
	g::Button start_rotation_button_;
	g::GraphicsContainer buttons_;
	g::Button skip_turn_button_;
	bool is_active_;
	class StartRotationHandler: public g::MouseHandler
	{
	public:
		StartRotationHandler(PlayerMouseControl* gc, g::GameState* state) : rot_(gc, state), gc_(gc)
		{	
		}
		void handle_mouse_event(g::CollisionComputable*, int , int ) override
		{
			if (gc_->player()!=gc_->director()->player_on_turn())
			{
				return;
			}
			gc_->pause();
			rot_.activate();
		}
		void initialize(GamePlanGraphics* graphics, Player player)
		{
			rot_.initialize(graphics, player);
		}
		RotationControl rot_;
	private:
		PlayerMouseControl* gc_;

	} rotation_btn_handler_;
	class SkipRotHandler: public g::MouseHandler
	{
	public:

		explicit SkipRotHandler()
			: dir_(nullptr)
		{
		}

		void handle_mouse_event(g::CollisionComputable* , int , int ) override
		{
			dir_->skip_turn();
		}
		void initialize(VolcanoGameDirector* dir)
		{
			dir_ = dir;
		}

	private:
		VolcanoGameDirector* dir_;
	} skip_turn_handler_;
	void remove_island_actions_handlers()
	{
		for (auto& i : island_mouse_handlers_)
		{
			game_state()->remove_mouse_click_handler(i.get());
			game_state()->removeMouseMotionHandler(i.get());
		}
	}

	///Warning: works only providing the game plan hasn't changed. (Only reassigns old handlers.)
	void add_island_actions_handlers()
	{
		auto & game_nodes = game_plan_graphics()->game_nodes();

		auto it1 = island_mouse_handlers_.begin();
		auto it2 = game_nodes.begin();
		for (; it1 != island_mouse_handlers_.end() && it2 != game_nodes.end(); ++it1, ++it2)
		{
			auto i = it1->get();
			auto n = (*it2)->node_graphics().get();
			game_state()->add_mouse_click_handler(n, i);
			game_state()->add_mouse_motion_handler(n, i);
		}
	}	
};
#endif // PlayerMouseControl_h__
