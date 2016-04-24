#ifndef GameNodeGraphics_H
#define GameNodeGraphics_H

#include "GameEngine/GraphicsContainer.h"
#include <memory>
#include "GameEngine/Image.h"
#include "GameEngine/Common.h"
#include "IslandGraphics.h"
#include "GameNode.h"
#include "GamePlan.h"

class GameNodeGraphics : public g::GraphicsContainer
{
public:
	GameNodeGraphics(GameNode* node, GamePlan* plan);

	//Returns: value in radians.
	double get_direction_to_node(node_index pointing_to_node)
	{
		auto n = plan_->get_node_at(pointing_to_node);
		return atan2(n->x() - x(), y() - n->y())-common::PI/2;
	}

	void draw(g::TexturePainter& painter, int x0, int y0) override
	{
		GameNode  n = *node_;
		auto pointing_to_node = n.pointing_to_node();
		if (pointing_to_node != last_target_node_)
		{
			last_target_node_ = pointing_to_node;
			double rot = get_direction_to_node(pointing_to_node);
			arrow_graphics_->set_rotation(common::rad_to_deg(rot));
			auto transl = gameconst::island_size/2;
			arrow_graphics_->set_x(static_cast<int>(cos(rot)*transl));
			arrow_graphics_->set_y(static_cast<int>(sin(rot)*transl));
		}
		node_graphics_->set_island_type(n.island_type());
		node_graphics_->set_owner(n.owner());
		GraphicsContainer::draw(painter, x0, y0);
	}

	GameNode* node() const
	{
		return node_;
	}

	std::unique_ptr<IslandGraphics> & node_graphics()
	{
		return node_graphics_;
	}
	void hide_arrow_graphics() const
	{
		arrow_graphics_->set_visible(false);
	}
	void show_arrow_graphics() const
	{
		arrow_graphics_->set_visible(true);
	}
private:

	std::unique_ptr<g::Image> arrow_graphics_;
	std::unique_ptr<IslandGraphics> node_graphics_;
	GameNode* node_;
	node_index last_target_node_;
	GamePlan* plan_;
};


#endif // GameNodeGraphics_H

