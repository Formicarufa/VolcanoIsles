#ifndef PlayerAIControl_H
#define PlayerAIControl_H

#include "AbstractGameControl.h"
#include "MiniMax.h"
#include "GameEngine/DelayTimer.h"
#include <future>
#include <chrono>

class PlayerAIControl: public AbstractGameControl
{
public:
	explicit PlayerAIControl(g::GameState* game_state)
		: AbstractGameControl(game_state), command_planned_(false),block_time_(50)
	{
	}


	
	void turn_started() override
	{
		command_planned_ = false;
		timer.start(gameconst::THINKING_TIME);
		planning_ = std::async(MiniMax::get_next_action, *plan(), player());
		
	}

	void turn_ended() override
	{
	}

	void reset() override
	{
	}

	void proceed() override
	{
		if (!command_planned_)
		{
			if (planning_.wait_for(block_time_)==std::future_status::ready)
			{
				command_planned_ = true;
				command_ = planning_.get();
				MiniMax::print_stats();
			} else
			{
				return;
			}
		}

		if (timer.time_elapsed())
		{
			director()->apply_command(command_);
		}
	}

	void initialized() override
	{
	}
private:
	Command command_;
	bool command_planned_;
	g::DelayTimer timer;
	std::future<Command> planning_;
	std::chrono::milliseconds block_time_;
};


#endif // PlayerAIControl_H
