#pragma once
#ifndef VolcanoGameState_H
#define VolcanoGameState_H
#include "GameEngine/GameState.h"
#include <memory>
#include "GamePlan.h"
#include "GamePlanGraphics.h"
#include "VolcanoGameDirector.h"
#include "PlayerMouseControl.h"
#include "MedalsManager.h"
#include "PlayerIcon.h"

class VolcanoGameState : public g::GameState, public g::UpdateAction, public g::MouseHandler
{
public:
	//map name: path to the map relative to the game directory.
	VolcanoGameState() : planGraphics_(&plan_), director_(&plan_), blue_control_(nullptr), red_control_(nullptr),
	                     believed_turn_(0), believed_player_(Player::NONE),
		restart_button_(gameconst::WIDTH - gameconst::island_size - 30, gameconst::HEIGHT - gameconst::island_size - 30, "restart_game", this),
		medals_(10, 10)
		, icon_(gameconst::WIDTH / 2 - gameconst::player_icon_size / 2, 10)
	{
	}
	//controllers need to be set before start
	void set_player_controllers(AbstractGameControl* blue, AbstractGameControl* red)
	{
		red_control_ = red;
		blue_control_ = blue;
		blue->initialize(&planGraphics_, &director_, Player::BLUE);
		red->initialize(&planGraphics_, &director_, Player::RED);
	}

	void updateAction() override
	{
		planGraphics_.update_fireball_positions();
		if (believed_turn_ != director_.turn_number())
		{
			believed_turn_ = director_.turn_number();
			auto new_player = director_.player_on_turn();
			if (director_.game_ended())
			{
				medals_.add_medal(director_.get_winner());
				deactivate_control_of(believed_player_);
				believed_player_ = new_player;
				icon_.set_player(believed_player_);
				return;
			}
			start_turn(new_player);
			icon_.set_player(new_player);
			believed_player_ = new_player;
		} else
		{
			continue_playing(believed_player_);
		}

	}
	virtual ~VolcanoGameState()
	{
		restart_button_.remove_handler(this);
	}


	bool init(std::string map_name)
	{
		add_action(this);
		if (!plan_.load(map_name))
		{
			return false;
		}
		planGraphics_.draw();
		add_graphics(&planGraphics_);
		restart_button_.add_click_handler(this);
		add_graphics(&restart_button_);
		add_graphics(&medals_);
		add_graphics(&icon_);
		return true;

	}

	//Mouse click on the restart button:
	void handle_mouse_event(g::CollisionComputable*, int, int) override
	{
		director_.restart_game();
	}
private:
	GamePlan plan_;
	GamePlanGraphics planGraphics_;
	VolcanoGameDirector director_;
	AbstractGameControl* blue_control_;
	AbstractGameControl* red_control_;
	std::size_t believed_turn_;
	Player believed_player_;
	g::Button restart_button_;
	MedalsManager medals_;
	PlayerIcon icon_;

	void deactivate_control_of(Player player) const
	{
		switch (player)
		{
		case Player::NONE:
			break;
		case Player::BLUE:
			blue_control_->turn_ended();
			break;
		case Player::RED:
			red_control_->turn_ended();
			break;
		default:
			break;
		}
	}
	void continue_playing(Player player) const
	{
		switch (player)
		{
		case Player::NONE:
			break;
		case Player::BLUE:
			blue_control_->proceed();
			break;
		case Player::RED:
			red_control_->proceed();
			break;
		default:
			break;
		}
	}
	void start_turn(Player player) const
	{
		deactivate_control_of(believed_player_);
		switch (player)
		{
		case Player::NONE:
			break;
		case Player::BLUE:
			blue_control_->turn_started();
			break;
		case Player::RED:
			red_control_->turn_started();
			break;
		default:
			break;
		}
	}


};


#endif // VolcanoGameState_H


