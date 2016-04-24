#include "VolcanoGameDirector.h"
#include <map>

void VolcanoGameDirector::simulate_nature()
{
	auto& fireballs = game_plan_->fire_balls();
	for (std::ptrdiff_t i = fireballs.size() - 1; i >= 0; i--)
	{
		auto& f = fireballs[i];
		//auto nextNode = game_plan_->get_node_at(f.node())->pointing_to_node();
		//auto lastNode = f.last_node();
		//if (lastNode == nextNode)			//RULE RELAXED.
		//{
		//	//Explode.
		//	burn_island(game_plan_->get_node_at(f.node()));
		//	common::vector_remove(fireballs, i);
		//}
		//else
		//{
			f.move(*game_plan_);
		//}
	}
	std::map<std::pair<std::size_t, std::size_t>, std::size_t> indices;
	//Check for collisions on link:
	for (std::ptrdiff_t i = fireballs.size() - 1; i >= 0; i--)
	{
		auto f = fireballs[i];
		std::size_t n1 = f.node();
		std::size_t n2 = f.last_node();
		auto current_node = game_plan_->get_node_at(n1);
		auto last_node = game_plan_->get_node_at(n2);
		std::pair<std::size_t, std::size_t> p = n1 < n2 ? std::make_pair(n1, n2) : std::make_pair(n2, n1);
		if (indices.find(p) != indices.end())
		{
			burn_island(current_node);
			burn_island(last_node);
			auto removed = indices[p];
			common::vector_remove(fireballs, removed);
			common::vector_remove(fireballs, i);
			for (auto& ind : indices)
			{
				if (ind.second > removed) ind.second -= 2; else ind.second -= 1;
			}
		} else
		{
			indices.emplace(p, i);
		}
	}
	std::vector<bool> removed_fireball(fireballs.size(), false);
	for (size_t i = 0; i < fireballs.size(); i++)
	{
		auto& fireball = fireballs.at(i);
		auto node = game_plan_->get_node_at(fireball.node());
		for (size_t j = i + 1; j < fireballs.size(); j++)
		{
			auto& fireball2 = fireballs.at(j);
			if (node->index() == fireball2.node())
			{
				burn_island(node);
				removed_fireball[i] = true;
				removed_fireball[j] = true;
			}
		}
	}
	for (std::ptrdiff_t i = fireballs.size() - 1; i >= 0; i--)
	{
		if (removed_fireball[i])
		{
			common::vector_remove(fireballs, static_cast<std::size_t>(i));
		}
	}
}
