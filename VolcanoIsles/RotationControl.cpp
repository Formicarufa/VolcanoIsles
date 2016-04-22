#include "RotationControl.h"
#include "PlayerMouseControl.h"

void RotationControl::deactivate()
{
	group_.set_visible(false);
	accept_button_.remove_handler(&accept_button_response_);
	abort_button_.remove_handler(&abort_button_response_);
	if (rotated_node_!=nullptr) rotated_node_->show_arrow_graphics();
	arrow_image_.set_visible(false);
	rotated_node_ = nullptr;
	ordered_neighbours_.clear();
	game_state_->remove_mouse_click_handler(this);
	is_active_ = false;
}

void RotationControl::accept()
{
	GameNode* rotated = rotated_node_->node();
	GameNode* direction = index->second;
	deactivate();
	pgc_->rotate_island(rotated, direction);
	pgc_->reactivate();
}

void RotationControl::cancel()
{
	deactivate();
	pgc_->reactivate();
}
