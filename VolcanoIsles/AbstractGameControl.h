#ifndef AbstractGameControl_H
#define AbstractGameControl_H
#include "Player.h"
#include "VolcanoGameDirector.h"
#include "GamePlanGraphics.h"
#include "GameEngine/GameState.h"


class AbstractGameControl
{
public:
	AbstractGameControl(g::GameState* game_state): game_state_(game_state), game_plan_graphics_(nullptr), plan_(nullptr), player_(Player::NONE), director_(nullptr)
	{
	}

	virtual ~AbstractGameControl()
	{
	}


	virtual void initialize(GamePlanGraphics* game_plan_graphics, VolcanoGameDirector* director, Player player)
	{
		game_plan_graphics_ = game_plan_graphics;
		player_ = player;
		director_ = director;
		plan_ = game_plan_graphics->game_plan();
		initialized();
	}
	//Start of a turn of the player which is controlled by this class.
	virtual void turn_started() = 0;
	virtual void turn_ended() = 0;

	virtual void reset()
	{
	}

	//called regularly between turn_started and turn_ended() are called.
	virtual void proceed()
	{
	}

	//Called after all fields of AbstractGameControl are initialized. 
	virtual void initialized() = 0;

	g::GameState* game_state() const
	{
		return game_state_;
	}

	GamePlanGraphics* game_plan_graphics() const
	{
		return game_plan_graphics_;
	}

	GamePlan* plan() const
	{
		return plan_;
	}

	Player player() const
	{
		return player_;
	}

	VolcanoGameDirector* director() const
	{
		return director_;
	}

private:
	g::GameState* game_state_;
	GamePlanGraphics* game_plan_graphics_;
	GamePlan* plan_;
	Player player_;
	VolcanoGameDirector* director_;

};


#endif // AbstractGameControl_H
