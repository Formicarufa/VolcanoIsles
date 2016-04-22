#ifndef GameNode_H
#define GameNode_H
#include <vector>
#include "IslandType.h"
#include "Player.h"


class GameNode
{
public:
	GameNode(std::vector<std::size_t>&& neighbour_indices, int x, int y, std::size_t index): neighbour_indices_(std::move(neighbour_indices)), island_type_(IslandType::EMPTY), owner_(Player::NONE), pointing_to_node_(nullptr), x_(x),y_(y), index_(index)
	{
		
	}
	const std::vector<std::size_t> & neighbour_indices() const
	{
		return neighbour_indices_;
	}
	void set_island_type(IslandType island_type)
	{
		island_type_ = island_type;
	}

	void set_owner(Player owner)
	{
		owner_ = owner;
	}
	void set_pointing_to_node(GameNode* node) {
		pointing_to_node_ = node;

	}
	GameNode* pointing_to_node() const
	{
		return pointing_to_node_;
	}

	Player owner() const
	{
		return owner_;
	}

	int x() const
	{
		return x_;
	}

	int y() const
	{
		return y_;
	}

	IslandType island_type() const
	{
		return island_type_;
	}


	std::size_t index() const
	{
		return index_;
	}

private:
	std::vector<std::size_t> neighbour_indices_;
	IslandType island_type_;
	Player owner_;
	GameNode* pointing_to_node_;
	int x_, y_;
	std::size_t index_;
};


#endif // GameNode_H
