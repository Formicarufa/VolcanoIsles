#include "GameNode.h"

GameNode::GameNode(int x, int y, std::vector<std::size_t>&& neighbour_indices): GraphicsContainer(x, y), neighbour_indices_(std::move(neighbour_indices)), island_type_(EMPTY), owner_(NONE)
{
	node_graphics_ = std::make_unique<GameNodeGraphics>(0,0);
	add_child(node_graphics_.get());
}


