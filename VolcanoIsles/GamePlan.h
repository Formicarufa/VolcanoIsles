#ifndef GamePlan_H
#define GamePlan_H



#include <string>
#include <vector>
#include <memory>
#include "GameNode.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "GameEngine/StaticGraphicsContainer.h"
#include "GameEngine/Line.h"

class GamePlan :public g::GraphicsContainer
{
public:
	GamePlan() :GraphicsContainer(0, -30), lines_(0,0)
	{
		add_child(&lines_);
	}

	void load(std::string filename)
	{
		std::ifstream fstream;
		fstream.open(filename);
		std::string line;
		while (std::getline(fstream, line))
		{
			std::istringstream line_stream(line);
			std::size_t num;
			int x, y;
			if (!(line_stream >> x)) {
				err_msg();
				return;
			}
			if (!(line_stream >> y))
			{
				err_msg();
				return;
			}
			std::vector<std::size_t> vec;
			while (line_stream >> num)
			{
				vec.push_back(num-1); //1-based to 0-based
			}
			auto node = std::make_unique<GameNode>(x, y, std::move(vec));
			add_child(node.get());
			nodes_.push_back(std::move(node));
		}
		if (nodes_.size() <= 1)
		{
			err_msg();
			return;
		}
		auto & base1 = nodes_[0];
		auto & base2 = nodes_[nodes_.size() - 1];
		base1->set_owner(PLAYER);
		base1->set_island_type(BASE);
		base2->set_owner(COMPUTER);
		base2->set_island_type(BASE);
		draw_connecting_lines();
	}

	GameNode* get_node_at(std::size_t index) const
	{
		return nodes_[index].get();
	}
	std::vector<GameNode*> get_neighbours_of(GameNode* n)
	{
		auto & indices = n->neighbour_indices();
		std::vector<GameNode*> vec(indices.size());
		std::transform(indices.begin(), indices.end(), vec.begin(), [this](std::size_t x) {return get_node_at(x);});
		return std::move(vec);
	}
private:
	std::vector< std::unique_ptr<GameNode>> nodes_;
	g::StaticGraphicsContainer lines_;
	static void err_msg()
	{
		std::string err_msg = "Error. Unable to load map. Wrong input format.";
		std::cout << err_msg;
	}

	void connect_nodes(GameNode* m, GameNode* n)
	{
		int c = gameconst::island_size/2;
		std::unique_ptr<g::Line> line = std::make_unique<g::Line>(m->x() + c, n->x() + c, m->y() + c, n->y() + c);
		line->set_color(colors::color(200, 200, 200, 0));
		lines_.add_child(std::move(line));
	}

	void draw_connecting_lines()
	{
		std::size_t index = 0;
		for (auto & node : nodes_)
		{
			for (std::size_t n_index : node->neighbour_indices())
			{
				if (n_index>index)
				{
					connect_nodes(node.get(), get_node_at(n_index));
				}
			
			index++;
		}
	}
};


#endif // GamePlan_H
