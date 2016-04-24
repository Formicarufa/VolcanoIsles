#include "FireBall.h"
#include "GamePlan.h"

node_index FireBall::node() const
{
	return node_;
}

node_index FireBall::last_node() const
{
	return last_node_;
}

void FireBall::set_node(node_index node)
{
	last_node_ = node_;
	node_ = node;
}

void FireBall::move(GamePlan& plan)
{
	last_node_ = node_;
	node_ = plan.get_node_at(node_)->pointing_to_node();
}
