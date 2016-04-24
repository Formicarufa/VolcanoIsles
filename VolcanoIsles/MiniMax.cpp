#include "MiniMax.h"
#include "GameConstants.h"

std::clock_t MiniMax::start_time=0;
std::clock_t MiniMax::end_time = 0;
std::size_t MiniMax::leaves_count = 0;
std::size_t MiniMax::searched_states = 0;
std::size_t MiniMax::inner_nodes = 0;

void MiniMax::print_stats()
{
	std::cout << "Next command planning took: " << 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC << "ms. " << std::endl
		<< "States searched: " << searched_states << std::endl
		<< "Average branching factor: "
		<< static_cast<double>(searched_states) / inner_nodes << std::endl << std::endl;
}

bool MiniMax::get_viable_command(GameNode& node, Command& out_command, const VolcanoGameDirector& dir, Player player)
{
	if (node.owner() == player)
	{
		if (dir.can_create_volcano(node))
		{
			out_command = Command::create_volcano(node.index());
			return true;
		}
		if (dir.can_produce_fire(node))
		{
			out_command = Command::produce_fire(node.index());
			return true;
		}
	}
	else if (dir.can_occupy(node))
	{
		out_command = Command::occupy(node.index());
		return true;
	}
	return false;
}

std::pair<score_t, Command> MiniMax::max(VolcanoGameDirector& d, GamePlan& plan, Player player, int depth, score_t current_min, score_t current_max)
{
	score_t bestValue = WORST_POSSIBLE_SCORE;
	inner_nodes++;
	Command bestCommand = Command::skip();
	auto other_player = d.other_player(player);
	auto game_nodes =get_nodes_sorted(plan,other_player);
	Command c;
	for (auto& n : game_nodes)
	{
		auto node = n.second;
		if (get_viable_command(*node, c, d, player))
		{
			auto res = min(plan, c, other_player, depth + 1,current_min,current_max);
			update_max(bestValue, bestCommand, res.first, c);
			if (bestValue>current_min) return std::make_pair(bestValue, bestCommand);
			current_max = std::max(current_max, bestValue);
		}
	}
	for (auto& n : game_nodes)
	{
		auto node = n.second;
		auto visitable = visitable_nodes(plan);
		if (d.can_change_direction(*node) && visitable[node->index()])
		{
			auto neighbours = plan.get_neighbours_of_excluding(*node, node->pointing_to_node());
			for (auto& neighbour : neighbours)
			{
				c = Command::rotation(node->index(), neighbour->index());
				auto res = min(plan, c, other_player, depth + 1, current_min, current_max);
				update_max(bestValue, bestCommand, res.first, c);
				if (bestValue>current_min) return std::make_pair(bestValue, bestCommand);
				current_max = std::max(current_max, bestValue);
			}
		}
	}
	c = Command::skip();
	auto res = min(plan, c, other_player, depth + 1, current_min, current_max);
	update_max(bestValue, bestCommand, res.first, c);
	return std::make_pair(bestValue, bestCommand);
}

void MiniMax::update_max(score_t& currentMax, Command& currentBest, score_t value, Command& new_command)
{
	if (value > currentMax)
	{
		currentMax = value;
		currentBest = new_command;
	}
	else if (value == currentMax)
	{
		if (rand() % 256 <20) //randomness to prevent infinite games (looping in a cycle).
		{
			currentMax = value;
			currentBest = new_command;
		}
	}
}

void MiniMax::update_min(score_t& currentMin, Command& currentBest, score_t value, Command& new_command)
{
	if (value < currentMin)
	{
		currentMin = value;
		currentBest = new_command;
	} else if (value==currentMin)
	{
		if (rand()%256 <20)  //randomness to prevent infinite games (looping in a cycle).
		{
			currentMin = value;
			currentBest = new_command;
		}
	}
}

std::pair<score_t, Command> MiniMax::min(VolcanoGameDirector& d, GamePlan& plan, Player player, int depth, score_t current_min, score_t current_max)
{
	score_t bestValue = INFINITE_SCORE;
	inner_nodes++;
	Command bestCommand = Command::skip();
	auto other_player = d.other_player(player);
	auto game_nodes = get_nodes_sorted(plan, other_player);
	Command c;
	for (auto& n : game_nodes)
	{
		auto node = n.second;
		if (get_viable_command(*node, c, d, player))
		{
			auto res = max(plan, c, other_player, depth + 1, current_min,current_max);
			update_min(bestValue, bestCommand, res.first, c);
			if (bestValue < current_max) return std::make_pair(bestValue, bestCommand);
			current_min = std::min(current_min, bestValue);
		}
	}
	for (auto& n : game_nodes)
	{
		auto node = n.second;
		auto visitable = visitable_nodes(plan);
		if (d.can_change_direction(*node) && visitable[node->index()])
		{
			auto neighbours = plan.get_neighbours_of_excluding(*node, node->pointing_to_node());
			for (auto& neighbour : neighbours)
			{
				c = Command::rotation(node->index(), neighbour->index());
				auto res = max(plan, c, other_player, depth + 1,current_min,current_max);
				update_min(bestValue, bestCommand, res.first, c);
				if (bestValue<current_max) return std::make_pair(bestValue, bestCommand);
				current_min = std::min(current_min, bestValue);
			}
		}
	}
	c = Command::skip();
	auto res = max(plan, c, other_player, depth + 1,current_min,current_max);
	update_min(bestValue, bestCommand, res.first, c);
	return std::make_pair(bestValue, bestCommand);
}

std::pair<score_t, Command> MiniMax::min(GamePlan g, Command c, Player p, int depth, score_t current_min, score_t current_max)
{
	VolcanoGameDirector d(&g, VolcanoGameDirector::other_player(p));
	d.apply_command(c);
	searched_states++;
	if (depth == gameconst::MAX_DEPTH)
	{
		int_least32_t val = evaluate_game_plan(g, p);
		return std::make_pair(val, c);
	}
	return min(d, g, p, depth,current_min,current_max);
}

std::pair<score_t, Command> MiniMax::max(GamePlan g, Command c, Player p, int depth, score_t current_min, score_t current_max)
{
	VolcanoGameDirector d(&g, VolcanoGameDirector::other_player(p));
	d.apply_command(c);
	searched_states++;
	if (depth == gameconst::MAX_DEPTH)
	{
		int_least32_t val = evaluate_game_plan(g, p);
		return std::make_pair(val, c);
	}
	return max(d, g, p, depth,current_min,current_max);
}

score_t MiniMax::evaluate_game_plan(GamePlan& game_plan, Player p)
{
	leaves_count++;
	if (gameconst::MAX_DEPTH % 2 == 0) {
		p = VolcanoGameDirector::other_player(p);
	}
	std::int_least32_t score = 0;
	auto& nodes = game_plan.nodes();
	for (auto& node : nodes)
	{
		IslandType island_type = node.island_type();
		if (node.owner() == p)
		{
			score += 200;
			if (island_type == IslandType::VOLCANO)
			{
				score += VOLCANO_SCORE;
			} else if (island_type==IslandType::BASE)
			{
				score += BASE_SCORE;
			}
		}
		else if (node.owner() != Player::NONE)
		{
			score -= 200;
			if (island_type == IslandType::BASE)
			{
				score -= BASE_SCORE;
			}
			else if (island_type == IslandType::VOLCANO)
			{
				score -= VOLCANO_SCORE;
			}
		}
	}
	return score;
}
