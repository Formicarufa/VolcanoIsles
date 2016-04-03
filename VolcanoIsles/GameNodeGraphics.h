#ifndef GameNodeGraphics_H
#define GameNodeGraphics_H

#include "GameEngine/GraphicsContainer.h"
#include <memory>
#include "GameEngine/Image.h"
#include "GameEngine/Common.h"
#include "IslandGraphics.h"
#include "GameNode.h"

class GameNodeGraphics : public g::GraphicsContainer
{
public:
	explicit GameNodeGraphics(GameNode* node);


	void draw(g::TexturePainter& painter, int x0, int y0) override
	{
		GameNode  n = *node_;
		auto pointing_to_node = n.pointing_to_node();
		if (pointing_to_node != last_target_node_)
		{
			last_target_node_ = pointing_to_node;
			double rot = atan2(pointing_to_node->x() - x(), y() - pointing_to_node->y());
			arrow_graphics_->set_rotation(common::rad_to_deg(rot));
		}
		node_graphics_->set_island_type(n.island_type());
		node_graphics_->set_owner(n.owner());
		GraphicsContainer::draw(painter, x0, y0);
	}

private:

	std::unique_ptr<g::Image> arrow_graphics_;
	std::unique_ptr<IslandGraphics> node_graphics_;
	GameNode* node_;
	GameNode* last_target_node_;

};


#endif // GameNodeGraphics_H

