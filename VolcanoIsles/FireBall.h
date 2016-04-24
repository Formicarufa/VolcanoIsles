#ifndef FireBall_H
#define FireBall_H
#include "GameNode.h"


class GamePlan;

class FireBall
{
public:


	explicit FireBall(GameNode* node)
		: node_(node->index()), last_node_(NODE_UNDEF)
	{

	}

	explicit FireBall(node_index node)
		: node_(node), last_node_(NODE_UNDEF)
	{

	}

	node_index node() const;
	node_index last_node() const;
	void set_node(node_index node);
	void move(GamePlan& plan);
private:
	node_index node_;
	node_index last_node_;
};


#endif // FireBall_H
