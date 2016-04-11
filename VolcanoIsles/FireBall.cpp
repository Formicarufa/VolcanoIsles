#include "FireBall.h"

GameNode* FireBall::node() const
{
	return node_;
}

GameNode* FireBall::last_node() const
{
	return last_node_;
}

void FireBall::set_node(GameNode* node)
{
	node_ = node;
}
