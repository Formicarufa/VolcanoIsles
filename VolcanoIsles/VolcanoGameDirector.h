#ifndef VolcanoGameDirector_H
#define VolcanoGameDirector_H
#include "Player.h"
#include "GamePlan.h"
#include "GameEngine/Common.h"
#include "Command.h"
#include <cassert>

class VolcanoGameDirector
{
public:
	explicit VolcanoGameDirector(GamePlan* game_plan)
		: player_on_turn_(Player::BLUE), winner_(Player::NONE), game_plan_(game_plan), turn_number_(1), game_ended_(false)
	{
	}

	VolcanoGameDirector(GamePlan* game_plan, Player player_on_turn)
		: player_on_turn_(player_on_turn),
		  winner_(Player::NONE), game_plan_(game_plan), turn_number_(1), game_ended_(false)
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
	void ocuppy_island(node_index node)
	{
		game_plan_->get_node_at(node)->set_owner(player_on_turn_);
		end_turn();
	}

	void change_direction(GameNode* island,GameNode* direction)
	{
		island->set_pointing_to_node(direction);
		end_turn();
	}
	void change_direction(GameNode* island, node_index direction)
	{
		island->set_pointing_to_node(direction);
		end_turn();
	}
	void change_direction(node_index island, node_index direction)
	{
		game_plan_->get_node_at(island)->set_pointing_to_node(direction);
		end_turn();
	}
	void produce_fire(GameNode* island)
	{
		game_plan_->fire_balls().emplace_back(island);
		end_turn();
	}
	void produce_fire(node_index island)
	{
		game_plan_->fire_balls().emplace_back(island);
		end_turn();
	}
	void create_volcano(GameNode* island)
	{
		island->set_island_type(IslandType::VOLCANO);
		auto nodes = game_plan_->get_neighbours_of(*island);
		for (auto n: nodes)
		{
			n->set_pointing_to_node(island);
		}
		end_turn();
	}
	void create_volcano(node_index index)
	{
		create_volcano(game_plan_->get_node_at(index));
	}
	///Can current player create volcano on the given island?
	bool can_create_volcano(const GameNode& island) const
	{
		if (island.island_type() != IslandType::EMPTY) return false;
		auto game_nodes = game_plan_->get_neighbours_of(island);
		for (auto n : game_nodes)
		{
			if (n->owner() != player_on_turn_)
			{
				return false;
			}
		}
		return island.owner() == player_on_turn_;
	}
	void apply_command(Command c)
	{
		switch (c.command_)
		{
		case CommandType::SkipTurn:skip_turn(); break;
		case CommandType::Occupy:ocuppy_island(c.target_); break;
		case CommandType::ProduceFire: produce_fire(c.target_);break;
		case CommandType::Rotate:assert(c.direction_ != NODE_UNDEF); change_direction(c.target_, c.direction_); break;
		case CommandType::CreateVolcano: create_volcano(c.target_); break;
		default: break;
		}
		
	}
	///The winning player or NONE if the game has not ended yet.
	Player get_winner() const
	{
		return winner_;
	}

	bool can_occupy(const GameNode& game_node) const
	{
		if (game_node.owner() != Player::NONE) return false;
		std::vector<GameNode*> neighbours = game_plan_->get_neighbours_of(game_node);
		for (auto n : neighbours)
		{
			if (n->owner() == player_on_turn_) return true;
		}
		return false;
	}
	bool can_change_direction(const GameNode& node) const
	{
		return player_on_turn() == node.owner();
	}
	bool fire_on_island(GameNode& node) const
	{
		auto & fire_balls = game_plan_->fire_balls();
		node_index index = node.index();
		for (auto& i : fire_balls)
		{
			if (i.node() == index) return true;
		}
		return false;
	}

	bool can_produce_fire(GameNode& node) const
	{
		auto type = node.island_type();
		return (type == IslandType::VOLCANO || type==IslandType::BASE)  && node.owner() == player_on_turn_ && !fire_on_island(node);
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
	static Player other_player(Player player)
	{
		if (player == Player::BLUE)
		{
			return Player::RED;
		}
		return Player::BLUE;
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



