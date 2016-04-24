#ifndef GamePlan_H
#define GamePlan_H



#include <string>
#include <vector>
#include <memory>
#include "GameNode.h"
#include <algorithm>
#include <iostream>
#include "FireBall.h"
#include <cassert>

class GamePlan
{
public:
	GamePlan() 
	{
	}

	bool load(std::string filename);

	GameNode* get_node_at(std::size_t index)
	{
		return &nodes_[index];
	}


	std::vector<GameNode*> get_neighbours_of(const GameNode& n)
	{
		auto & indices = n.neighbour_indices();
		std::vector<GameNode*> vec(indices.size());
		std::transform(indices.begin(), indices.end(), vec.begin(), [this](std::size_t x) {return get_node_at(x);});
		return std::move(vec);
	}

	std::vector<GameNode*> get_neighbours_of_excluding(const GameNode& n, node_index index)
	{
		auto & indices = n.neighbour_indices();
		std::vector<GameNode*> vec(indices.size()-1);
		std::size_t x=0;
		for (auto i : indices)
		{
			if (i!=index)
			{
				GameNode* node = get_node_at(i);
				assert(node != nullptr);
				vec[x++] = node;
			}
		}
		return std::move(vec);
	}

	std::vector<GameNode*> get_neighbours_of_excluding(const GameNode& n,const GameNode& excluding)
	{
		auto index = excluding.index();
		return get_neighbours_of_excluding(n, index);
	}
	//The user can modify the elements in the vector but the vector itself should not be changed.
	std::vector<GameNode>& nodes()
	{
		return  nodes_;
	}

	std::vector<FireBall> & fire_balls()
	{
		return fire_balls_;
	}
	void add_fire_ball(GameNode* island)
	{
		fire_balls_.emplace_back(island);
	}
	void reset()
	{
		fire_balls_.clear();
		for (auto& i : nodes_)
		{
			i.set_owner(Player::NONE);
			i.set_island_type(IslandType::EMPTY);
			i.set_pointing_to_node(random_neighbor(&i));
		}
		nodes_[0].set_owner(Player::BLUE);
		nodes_[nodes_.size()-1].set_owner( Player::RED);
		nodes_[0].set_island_type(IslandType::BASE);
		nodes_[nodes_.size()-1].set_island_type(IslandType::BASE);
	}
private:
	std::vector< GameNode> nodes_;
	std::vector< FireBall> fire_balls_;
	
	static void err_msg()
	{
		std::string err_msg = "Error. Unable to load map. Wrong input format.";
		std::cout << err_msg;
	}


	GameNode* random_neighbor(GameNode* node)
	{
		const auto& indices = node->neighbour_indices();
		if (indices.empty()) return nullptr;
		size_t i = std::rand() % indices.size();
		auto index = indices[i];
		return get_node_at(index);	
	}
	void set_random_pointing_to_directions()
	{
		for( auto & g : nodes_)
		{
			g.set_pointing_to_node(random_neighbor(&g));
		}
	}

};


#endif // GamePlan_H
