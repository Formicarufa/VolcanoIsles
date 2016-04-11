#pragma once
#ifndef VolcanoGameState_H
#define VolcanoGameState_H
#include "GameEngine/GameState.h"
#include <memory>
#include <iostream>
#include "GamePlan.h"
#include "GamePlanGraphics.h"
#include "VolcanoGameDirector.h"
#include "PlayerGameControl.h"

class VolcanoGameState: public g::GameState, public g::UpdateAction, public g::MouseHandler
{
public:

	VolcanoGameState(): director_(nullptr), mouse_control_(this)
	{
	}

	void updateAction() override
	{
		planGraphics_->update_fireball_positions();
	}
	virtual ~VolcanoGameState()
	{
		
	}


	void init()
	{
		addAction(this);
		plan_ = std::make_unique<GamePlan>();
		plan_->load("maps/rectangle.map");
		plan_->add_fire_ball(plan_->get_node_at(0));
		director_ = VolcanoGameDirector(plan_.get());
		planGraphics_ = std::make_unique<GamePlanGraphics>(plan_.get());
		mouse_control_.activate(planGraphics_.get(), &director_, PLAYER);
		addGraphics(planGraphics_.get());
		

	}
	
	void handle_mouse_event(int x, int y) override
	{
		std::cout << "Mouse click on " << x << ", " << y;
	}
private:
	std::unique_ptr<GamePlan> plan_;
	std::unique_ptr<GamePlanGraphics> planGraphics_;
	VolcanoGameDirector director_;
	PlayerGameControl mouse_control_;
};


#endif // VolcanoGameState_H


