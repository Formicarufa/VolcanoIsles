#ifndef PlayerAIControl_H
#define PlayerAIControl_H

#include "AbstractGameControl.h"

class PlayerAIControl: public AbstractGameControl
{
	explicit PlayerAIControl(g::GameState* game_state)
		: AbstractGameControl(game_state)
	{
	}


public:
	~PlayerAIControl() override;
	void turn_started() override;
	void turn_ended() override;
	void reset() override;
	void proceed() override;
	void initialized() override;
};


#endif // PlayerAIControl_H
