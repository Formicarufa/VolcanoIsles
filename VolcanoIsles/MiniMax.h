#ifndef MiniMax_H
#define MiniMax_H
#include "Command.h"
#include "GamePlan.h"
#include "VolcanoGameDirector.h"
#include <ctime>
using score_t = std::int_least32_t;



class MiniMax
{
public:
	static std::clock_t start_time;
	static std::clock_t end_time;
	static std::size_t leaves_count;
	static std::size_t searched_states;
	static std::size_t inner_nodes;
	static const score_t INFINITE_SCORE = INT_LEAST32_MAX;
	static const score_t WORST_POSSIBLE_SCORE = INT_LEAST32_MIN;

	static const score_t VOLCANO_SCORE = 190;
	static const score_t ISLAND_SCORE = 200;
	static const score_t BASE_SCORE = 500;
	static void reset_stats()
	{
		leaves_count = 0;
		searched_states = 0;
		inner_nodes = 0;
	}

	static Command get_next_action(GamePlan plan, Player player)
	{
		start_time = std::clock();
		reset_stats();
		VolcanoGameDirector d(&plan, player);
		Command command = max(d, plan, player, 1, INFINITE_SCORE, WORST_POSSIBLE_SCORE).second;
		end_time = std::clock();
		return command;

	}

	static void print_stats();

private:
	//Fills the out_command paramter with the action that can be performed with the given node. Returns false if there is no such action.
	static bool get_viable_command(GameNode& node, Command& out_command, const VolcanoGameDirector& dir, Player player);

	static std::pair<score_t, Command> max(VolcanoGameDirector& d, GamePlan& plan, Player player, int depth, score_t current_min, score_t current_max);

	static void update_max(score_t& currentMax, Command& currentBest, score_t value, Command& new_command);

	static void update_min(score_t& currentMin, Command& currentBest, score_t value, Command& new_command);

	static std::pair<score_t, Command> min(VolcanoGameDirector& d, GamePlan& plan, Player player, int depth, score_t current_min, score_t current_max);


	static std::pair<score_t, Command> min(GamePlan g, Command c, Player p, int depth, score_t current_min, score_t current_max);

	static std::pair<score_t, Command> max(GamePlan g, Command c, Player p, int depth, score_t current_min, score_t current_max);

	static score_t evaluate_game_plan(GamePlan& game_plan, Player p);
	//Optimization: allow rotation only of those nodes, which are on a path of a fireball (or a possible fireball path from  a volcano/ base)
	static std::vector<bool> visitable_nodes(GamePlan& game_plan)
	{
		auto &game_nodes = game_plan.nodes();
		std::vector<bool> vec(game_nodes.size(), false);
		for (auto& n : game_nodes)
		{
			auto index = n.index();
			if (!vec[index])
			{
				auto island_type = n.island_type();
				if (island_type == IslandType::BASE || island_type == IslandType::VOLCANO)
				{
					auto i = index;
					while (!vec[i])
					{
						vec[i] = true;
						i = game_plan.get_node_at(i)->pointing_to_node();
					}
				}
			}
		}
		auto& fire_balls = game_plan.fire_balls();
		for (auto& f : fire_balls)
		{
			auto index = f.node();
			while (!vec[index])
			{
				vec[index] = true;
				index = game_plan.get_node_at(index)->pointing_to_node();
			}
		}
		return std::move(vec);
	}
	using value_node = std::pair<score_t, GameNode*>;
	//prefer the nodes that are	1/ unoccupied	2/ close to enemy	3/ can produce fire
	static std::vector<value_node> get_nodes_sorted(GamePlan& plan, Player other_player)
	{
		auto & game_nodes = plan.nodes();
		std::vector<value_node> vec;
		for (auto& n : game_nodes)
		{
			score_t score = 0;
			auto owner = n.owner();
			if (owner != other_player)
			{
				if (owner == Player::NONE)
				{
					score += 15;
				}
				else
				{
					auto type = n.island_type();
					if (type == IslandType::BASE || type == IslandType::VOLCANO)
					{
						score += 10;
					}
				}
				auto indices = n.neighbour_indices();
				for (auto& i : indices)
				{
					auto neigh = plan.get_node_at(i);
					auto neigh_owner = neigh->owner();
					if (neigh_owner == other_player)
					{
						score++;
					}
				}
				vec.emplace_back(score, &n);
			}
		}
		std::sort(vec.begin(), vec.end(), [](const value_node& a, const value_node& b) {return a.first > b.first;});
		return std::move(vec);
	}
};


#endif // MiniMax_H
