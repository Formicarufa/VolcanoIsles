#ifndef FireBall_H
#define FireBall_H
#include "GameNode.h"


class FireBall
{
public:


	explicit FireBall(GameNode* node)
		: node_(node), last_node_(nullptr)
	{

	}

	GameNode* node() const;
	GameNode* last_node() const;
	void set_node(GameNode* node);
	void move()
	{
		last_node_ = node_;
		node_ = node_->pointing_to_node();
	}
private:
	GameNode* node_;
	GameNode* last_node_;
};


#endif // FireBall_H
