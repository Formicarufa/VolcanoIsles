#pragma once
#ifndef VolcanoGameState_H
#define VolcanoGameState_H
#include "GameEngine/GameState.h"
#include <memory>
#include <iostream>
#include "GamePlan.h"

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
		addGraphics(plan_.get());
	}
	
	void handle_mouse_event(int x, int y) override
	{
		std::cout << "Mouse click on " << x << ", " << y;
	}
private:
	std::unique_ptr<GamePlan> plan_;
};


#endif // VolcanoGameState_H


