#include "GameState.h"
#include "Common.h"
#include "MouseHandler.h"

void g::GameState::add_graphics(Graphics * g)
{
	root_container_.add_child(g);

}

void g::GameState::add_action(UpdateAction* a)
{
	actions_vector_.push_back(a);
}

void g::GameState::add_key_handler(KeyHandler* k)
{
	key_handlers_.push_back(k);
}

void g::GameState::add_mouse_click_handler(CollisionComputable* c, MouseHandler* h)
{
	click_vector_.push_back(std::make_pair(c, h));
}

void g::GameState::add_mouse_motion_handler(CollisionComputable* c, MouseMotionHandler* h)
{
	mouse_move_vector_.push_back(std::make_pair(c, h));
}

void g::GameState::remove_graphics(Graphics* g)
{	
	root_container_.remove_child(g);
}

void g::GameState::remove_action(UpdateAction* a)
{
	common::remove(actions_vector_, a);
}

void g::GameState::remove_key_handler(KeyHandler* k)
{
	common::remove(key_handlers_, k);
}

void g::GameState::remove_mouse_click_handler(CollisionComputable* c, MouseHandler* h)
{
	auto it = std::remove_if(click_vector_.begin(), click_vector_.end(), [&c,&h](std::pair<CollisionComputable*, MouseHandler*> &p) {return (p.first == c) && (p.second == h);});
	click_vector_.erase(it, click_vector_.end());	
}
void g::GameState::remove_mouse_click_handler(MouseHandler* h)
{
	auto it = std::remove_if(click_vector_.begin(), click_vector_.end(), [&h](std::pair<CollisionComputable*, MouseHandler*> &p) {return p.second == h;});
	click_vector_.erase(it, click_vector_.end());
}
const g::GraphicsContainer & g::GameState::graphics_container() const
{
	return root_container_;
}

const std::vector<g::UpdateAction*>& g::GameState::actions_vector() const
{
	return actions_vector_;
}

const std::vector<g::KeyHandler*> & g::GameState::key_handlers() const
{
	return key_handlers_;
}

const std::vector<std::pair<g::CollisionComputable*, g::MouseHandler*>> & g::GameState::click_handlers() const
{
	return click_vector_;
}

void g::GameState::removeMouseMotionHandler(CollisionComputable* c, MouseMotionHandler* h)
{
	auto it = std::remove_if(mouse_move_vector_.begin(), mouse_move_vector_.end(), [&c, &h](auto &p) {return p.first == c && p.second == h;});
	mouse_move_vector_.erase(it, mouse_move_vector_.end());
}
void g::GameState::removeMouseMotionHandler(MouseMotionHandler* h)
{
	auto it = std::remove_if(mouse_move_vector_.begin(), mouse_move_vector_.end(), [&h](auto &p) {return p.second == h;});
	mouse_move_vector_.erase(it, mouse_move_vector_.end());
}

const std::vector<std::pair<g::CollisionComputable*, g::MouseMotionHandler*>> & g::GameState::mouse_motion_handlers() const
{
	return mouse_move_vector_;
}
