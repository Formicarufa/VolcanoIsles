﻿#ifndef GameNode_H
#define GameNode_H

#include "GameEngine/GraphicsContainer.h"
#include <vector>
#include <memory>
#include "GameNodeGraphics.h"
#include "IslandType.h"

class GameNode : public g::GraphicsContainer
{
public:
	GameNode(int x, int y, std::vector<std::size_t>&& neighbour_indices);


	const std::vector<std::size_t> & neighbour_indices() const
	{
		return neighbour_indices_;
	}
	void set_island_type(IslandType island_type)
	{
		island_type_ = island_type;
		node_graphics_->set_island_type(island_type);
	}

	void set_owner(Owner owner)
	{
		owner_ = owner;
		node_graphics_->set_owner(owner);
	}
private:
	std::vector<std::size_t> neighbour_indices_;
	std::unique_ptr<GameNodeGraphics> node_graphics_;
	IslandType island_type_;
	Owner owner_;

};


#endif // GameNode_H

