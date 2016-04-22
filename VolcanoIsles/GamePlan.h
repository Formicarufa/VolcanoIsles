#ifndef GamePlan_H
#define GamePlan_H



#include <string>
#include <vector>
#include <memory>
#include "GameNode.h"
#include <algorithm>
#include <iostream>
#include "GameEngine/StaticGraphicsContainer.h"
#include "FireBall.h"

class GamePlan
{
public:
	GamePlan() 
	{
	}

	void load(std::string filename);

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

	const std::vector<std::unique_ptr<GameNode>>* nodes() const
	{
		return  &nodes_;
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
			i->set_owner(Player::NONE);
			i->set_island_type(IslandType::EMPTY);
			i->set_pointing_to_node(random_neighbor(i.get()));
		}
		nodes_[0]->set_owner(Player::BLUE);
		nodes_[nodes_.size()-1]->set_owner( Player::RED);
		nodes_[0]->set_island_type(IslandType::BASE);
		nodes_[nodes_.size()-1]->set_island_type(IslandType::BASE);
	}
private:
	std::vector< std::unique_ptr<GameNode>> nodes_;
	std::vector< FireBall> fire_balls_;
	
	static void err_msg()
	{
		std::string err_msg = "Error. Unable to load map. Wrong input format.";
		std::cout << err_msg;
	}


	GameNode* random_neighbor(GameNode* node) const
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
			g->set_pointing_to_node(random_neighbor(g.get()));
		}
	}

};


#endif // GamePlan_H
