#include "GameNodeGraphics.h"
#include "GameEngine/Image.h"
#include "GameNode.h"
GameNodeGraphics::GameNodeGraphics( GameNode* node): GraphicsContainer(node->x(), node->y()), node_(node), last_target_node_(nullptr)
{
	node_graphics_ = std::make_unique<IslandGraphics>(0,0);
	arrow_graphics_ = std::make_unique<g::Image>(0,0, "arrow");
	arrow_graphics_->set_alpha(120);
	add_child(arrow_graphics_.get());
	add_child(node_graphics_.get());
}


