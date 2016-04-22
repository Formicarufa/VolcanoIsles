#ifndef RotationControl_H
#define RotationControl_H
#include "GamePlanGraphics.h"
#include "GameEngine/Button.h"
#include <set>

class PlayerMouseControl;

class RotationControl : g::MouseHandler
{
public:

	RotationControl(PlayerMouseControl* pgc, g::GameState* game_state)
		: pgc_(pgc),
		graphics_(nullptr), game_state_(game_state),
		accept_button_(-gameconst::island_size / 2, 0, "accept", game_state),
		abort_button_(gameconst::island_size / 2, 0, "cancel", game_state),
		group_(gameconst::WIDTH / 2 - gameconst::island_size / 2, gameconst::HEIGHT - gameconst::island_size),
		rotated_node_(nullptr),
		arrow_image_(0, 0, "arrow"), player_(Player::NONE), is_active_(false),
		accept_button_response_(this), abort_button_response_(this)
	{
		group_.add_child(&accept_button_);
		group_.add_child(&abort_button_);
		arrow_image_.set_visible(false);
		group_.set_visible(false);
	}



	void activate()
	{
		is_active_ = true;
		group_.set_visible(true);
		accept_button_.add_click_handler(&accept_button_response_);
		abort_button_.add_click_handler(&abort_button_response_);
		accept_button_.set_enabled(false);
		for (auto& n : graphics_->game_nodes())
		{
			game_state_->add_mouse_click_handler(n->node_graphics().get(), this);
		}
	}

	void deactivate();


	bool is_active() const
	{
		return is_active_;
	}

	void set_rotated_node(GameNodeGraphics* node)
	{
		rotated_node_ = node;
		generate_neighbours_list();
		arrow_image_.set_x(node->x());
		arrow_image_.set_y(node->y());
		node->hide_arrow_graphics();
	}

	void handle_mouse_event(g::CollisionComputable* c, int , int ) override
	{
		IslandGraphics* isl = dynamic_cast<IslandGraphics*>(c);
		auto& game_nodes = graphics_->game_nodes();
		GameNodeGraphics* node = std::find_if(game_nodes.begin(),game_nodes.end(), [isl](std::unique_ptr<GameNodeGraphics>& x){return isl ==x->node_graphics().get();})->get();
		if (node->node()->owner() != player_) return;
		if (rotated_node_ == nullptr)
		{
			arrow_image_.set_visible(true);
			accept_button_.set_enabled(true);
			set_rotated_node(node);
		}
		else if (rotated_node_ != node)
		{
			rotated_node_->show_arrow_graphics();
			set_rotated_node(node);

		}
		next_neighbour();

		arrow_image_.set_rotation(common::rad_to_deg(index->first));

	}
	void generate_neighbours_list()
	{
		ordered_neighbours_.clear();
		auto neighbours = graphics_->game_plan()->get_neighbours_of(rotated_node_->node());
		for (auto n: neighbours)
		{
			ordered_neighbours_.emplace(rotated_node_->get_direction_to_node(n), n);
		}
		auto pointed = rotated_node_->node()->pointing_to_node();
		index = std::find_if(ordered_neighbours_.begin(), ordered_neighbours_.end(), [pointed](auto & x) {return x.second == pointed;});
		
	}

	void initialize(GamePlanGraphics* graphics, Player player)
	{
		graphics_ = graphics;
		player_ = player;

		graphics_->add_child(&arrow_image_);
		graphics_->add_child(&group_);
	}

private:
	PlayerMouseControl* pgc_;
	GamePlanGraphics* graphics_;
	g::GameState* game_state_;
	g::Button accept_button_;	
	g::Button abort_button_;
	g::GraphicsContainer group_;
	GameNodeGraphics* rotated_node_;
	g::Image arrow_image_;
	std::set<std::pair<double, GameNode*>> ordered_neighbours_;
	std::set<std::pair<double, GameNode*>>::iterator index;
	Player player_;
	bool is_active_;
	void next_neighbour()
	{
		if (++index == ordered_neighbours_.end())
		{
			index = ordered_neighbours_.begin();
		}
	}

	void accept();
	void cancel();

	class AcceptButtonResponse:public g::MouseHandler
	{
	public: 
		explicit AcceptButtonResponse(RotationControl* c)
			: c_(c)
		{
		}

		void handle_mouse_event(g::CollisionComputable* , int, int ) override
		{
			if (c_->rotated_node_==nullptr)
			{
				return;
			}
			c_->accept();

		}

	private:
		RotationControl* c_;
	} accept_button_response_;
	class AbortButtonResponse: public g::MouseHandler
	{
	public:
		explicit AbortButtonResponse(RotationControl* c)
			: c_(c)
		{
		}

		void handle_mouse_event(g::CollisionComputable* , int, int ) override
		{
			c_->cancel();
		}

	private:
		RotationControl* c_;
	} abort_button_response_;
};


#endif // RotationControl_H
