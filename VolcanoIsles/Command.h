#ifndef Command_H
#define Command_H
#include "GameNode.h"
#include "CommandType.h"


struct Command
{
	Command(): command_(CommandType::SkipTurn), target_(NODE_UNDEF), direction_(NODE_UNDEF)
	{
	}

	CommandType command_;
	node_index target_; // set unless the command is "skip turn"
	node_index direction_; //only set if the command is rotation.
	static Command rotation(node_index target, node_index direction)
	{
		return Command(CommandType::Rotate, target, direction);
	}
	static Command skip()
	{
		return Command();
	}
	static Command occupy(node_index target)
	{
		return Command(CommandType::Occupy, target);
	}
	static Command produce_fire(node_index target)
	{
		return Command(CommandType::ProduceFire, target);
	}
	static Command create_volcano(node_index target)
	{
		return Command(CommandType::CreateVolcano, target);
	}
private:

	Command(CommandType command, node_index target, node_index direction)
		: command_(command),
		  target_(target),
		  direction_(direction)
	{
	}

	Command(CommandType command, node_index target)
		: command_(command),
		  target_(target), direction_(NODE_UNDEF)
	{
	}
};


#endif // Command_H
