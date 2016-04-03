#pragma once
#ifndef VolcanoGameState_H
#define VolcanoGameState_H
#include "GameEngine/GameState.h"
#include <memory>
#include <iostream>
#include "GamePlan.h"
#include "GamePlanGraphics.h"

class VolcanoGameState: public g::GameState, public g::UpdateAction, public g::MouseHandler
{
public:

	void updateAction() override
	{
		
	}
	virtual ~VolcanoGameState()
	{
		
	}


	void init()
	{
		addAction(this);
		plan_ = std::make_unique<GamePlan>();
		plan_->load("maps/rectangle.map");
		planGraphics_ = std::make_unique<GamePlanGraphics>(plan_.get());
		addGraphics(planGraphics_.get());
	}
	
	void handle_mouse_event(int x, int y) override
	{
		std::cout << "Mouse click on " << x << ", " << y;
	}
private:
	std::unique_ptr<GamePlan> plan_;
	std::unique_ptr<GamePlanGraphics> planGraphics_;
};


#endif // VolcanoGameState_H


