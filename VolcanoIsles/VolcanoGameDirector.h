#ifndef VolcanoGameDirector_H
#define VolcanoGameDirector_H
#include "Player.h"
#include "GamePlan.h"
#include "GameEngine/Common.h"
#include <map>

class VolcanoGameDirector
{
public:
	explicit VolcanoGameDirector(GamePlan* game_plan)
		: player_on_turn_(Player::BLUE), winner_(Player::NONE), game_plan_(game_plan), turn_number_(1), game_ended_(false)
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
		game_plan_->fire_balls().emplace_back(island);
		end_turn();
	}

	void create_volcano(GameNode* island)
	{
		island->set_island_type(IslandType::VOLCANO);
		auto nodes = game_plan_->get_neighbours_of(island);
		for (auto n: nodes)
		{
			n->set_pointing_to_node(island);
		}
		end_turn();
	}
	///Can current player create volcano on the given island?
	bool can_create_volcano(GameNode* island) const
	{
		if (island->island_type() != IslandType::EMPTY) return false;
		auto game_nodes = game_plan_->get_neighbours_of(island);
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
		if (game_node->owner() != Player::NONE) return false;
		std::vector<GameNode*> neighbours = game_plan_->get_neighbours_of(game_node);
		for (auto n : neighbours)
		{
			if (n->owner() == player_on_turn_) return true;
		}
		return false;
	}

	bool fire_on_island(GameNode* node) const
	{
		auto & fire_balls = game_plan_->fire_balls();
		for (auto& i : fire_balls)
		{
			if (i.node() == node) return true;
		}
		return false;
	}

	bool can_produce_fire(GameNode* node) const
	{
		auto type = node->island_type();
		return (type == IslandType::VOLCANO || type==IslandType::BASE)  && node->owner() == player_on_turn_ && !fire_on_island(node);
	}

	std::size_t turn_number() const
	{
		return turn_number_;
	}

	bool game_ended() const
	{
		return game_ended_;
	}
	void restart_game()
	{
		player_on_turn_ = Player::BLUE;
		turn_number_ = 1;
		game_ended_ = false;
		winner_ = Player::NONE;
		game_plan_->reset();
	}
	void skip_turn()
	{
		end_turn();
	}
private:
	Player player_on_turn_;
	Player winner_;
	GamePlan* game_plan_;
	std::size_t turn_number_;
	bool game_ended_;

	void burn_island(GameNode* island)
	{
		if (island->island_type()==IslandType::BASE)
		{
			game_ended_ = true;
			if (winner_==Player::NONE)
			{
				winner_ = other_player(island->owner());
			} else
			{
				//It's going to be draw: both bases destroyed in the same turn.
				winner_ = Player::NONE;
			}
		}
		island->set_owner(Player::NONE);
		island->set_island_type(IslandType::EMPTY);
	}

	void simulate_nature();

	static Player other_player(Player player)
	{
		if (player== Player::BLUE)
		{
			return Player::RED;
		}
		return Player::BLUE;
	}

	void end_turn()
	{
		turn_number_++;
		simulate_nature();
		if (game_ended_)
		{
			player_on_turn_ = Player::NONE;
		}else
		{
			player_on_turn_ = other_player(player_on_turn_);	
		}
	}

};


#endif // VolcanoGameDirector_H



