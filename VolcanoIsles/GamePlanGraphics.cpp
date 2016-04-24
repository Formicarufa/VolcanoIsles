#include "GamePlanGraphics.h"
#include "GamePlan.h"
#include "GameEngine/Line.h"

void GamePlanGraphics::connect_nodes(const GameNode& m, const GameNode& n)
{
	int c = gameconst::island_size / 2;
	std::unique_ptr<g::Line> line = std::make_unique<g::Line>(m.x() + c, n.x() + c, m.y() + c, n.y() + c);
	line->set_color(colors::color(200, 200, 200, 0));
	lines_.add_child(std::move(line));
}

void GamePlanGraphics::draw_connecting_lines()
{
	std::size_t index = 0;
	auto & nodes = gamePlan_->nodes();
	for (auto & node : nodes)
	{
		for (std::size_t n_index : node.neighbour_indices())
		{
			if (n_index > index)
			{
				connect_nodes(node, *gamePlan_->get_node_at(n_index));
			}

		}
		index++;
	}
}
