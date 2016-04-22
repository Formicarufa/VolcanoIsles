#include "VolcanoGameDirector.h"

void VolcanoGameDirector::simulate_nature()
{
	auto& fireballs = game_plan_->fire_balls();
	for (std::ptrdiff_t i = fireballs.size() - 1; i >= 0; i--)
	{
		auto& f = fireballs[i];
		auto nextNode = f.node()->pointing_to_node();
		auto lastNode = f.last_node();
		//if (lastNode == nextNode)			RULE RELAXED.
		//{
		//	//Explode.
		//	burn_island(f.node());
		//	common::vector_remove(fireballs, i);
		//}
		//else
		//{
			f.set_node(nextNode);
		// }
	}
	std::map<std::pair<std::size_t, std::size_t>, std::size_t> indices;
	//Check for collisions on link:
	for (std::ptrdiff_t i = fireballs.size() - 1; i >= 0; i--)
	{
		auto f = fireballs[i];
		auto current_node = f.node();
		std::size_t n1 = current_node->index();
		auto last_node = f.last_node();
		std::size_t n2 = last_node->index();
		std::pair<std::size_t, std::size_t> p = n1 < n2 ? std::make_pair(n1, n2) : std::make_pair(n2, n1);
		if (indices.find(p) != indices.end())
		{
			burn_island(current_node);
			burn_island(last_node);
			common::vector_remove(fireballs, indices[p]);
			common::vector_remove(fireballs, i);
		} else
		{
			indices.emplace(p, i);
		}
	}
	std::vector<bool> removed_fireball(fireballs.size(), false);
	for (size_t i = 0; i < fireballs.size(); i++)
	{
		auto& fireball = fireballs.at(i);
		auto node = fireball.node();
		for (size_t j = i + 1; j < fireballs.size(); j++)
		{
			auto& fireball2 = fireballs.at(j);
			if (node == fireball2.node())
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
