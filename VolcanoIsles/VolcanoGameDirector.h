#ifndef VolcanoGameDirector_H
#define VolcanoGameDirector_H
#include "Player.h"
#include "GamePlan.h"

class VolcanoGameDirector
{
public:
	explicit VolcanoGameDirector(GamePlan* game_plan)
		: player_on_turn_(PLAYER), winner_(NONE), gamePlan(game_plan), turn_number(1)
	{
	}

	Player player_on_turn() const
	{
		return player_on_turn_;
	}


	void ocuppy_island(GameNode* node)
	{
		node->set_owner(player_on_turn_);
		end_turn();
	}

	void change_direction(GameNode* island, GameNode* direction)
	{
		island->set_pointing_to_node(direction);
		end_turn();
	}

	void produce_fire(GameNode* island)
	{
		gamePlan->fire_balls().emplace_back(island);
		end_turn();
	}

	void create_volcano(GameNode* island)
	{
		island->set_island_type(VOLCANO);
		auto nodes = gamePlan->get_neighbours_of(island);
		for (auto n: nodes)
		{
			n->set_owner(NONE);
			n->set_pointing_to_node(island);
		}
		end_turn();
	}
	///Can current player create volcano on the given island?
	bool can_create_volcano(GameNode* island) const
	{
		if (island->island_type() != EMPTY) return false;
		auto game_nodes = gamePlan->get_neighbours_of(island);
		for (auto n : game_nodes)
		{
			if (n->owner() != player_on_turn_)
			{
				return false;
			}
		}
		return island->owner() == player_on_turn_;
	}
	///The winning player or NONE if the game has not ended yet.
	Player get_winner() const
	{
		return winner_;
	}

	bool can_occupy(GameNode* game_node) const
	{
		if (game_node->owner() != NONE) return false;
		std::vector<GameNode*> neighbours = gamePlan->get_neighbours_of(game_node);
		for (auto n : neighbours)
		{
			if (n->owner() == player_on_turn_) return true;
		}
		return false;
	}
private:
	Player player_on_turn_;
	Player winner_;
	GamePlan* gamePlan;
	std::size_t turn_number;

	void simulate_nature()
	{
	}

	Player next_player() const
	{
		if (player_on_turn_ == PLAYER)
		{
			return COMPUTER;
		}
		return PLAYER;
	}

	void end_turn()
	{
		turn_number++;
		simulate_nature();
		player_on_turn_ = next_player();
	}
};


#endif // VolcanoGameDirector_H



