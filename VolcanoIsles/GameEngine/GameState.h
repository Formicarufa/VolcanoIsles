#pragma once
#ifndef GameState_H
#define GameState_H
#include "Graphics.h"
#include "UpdateAction.h"
#include "KeyHandler.h"
#include "CollisionComputable.h"
#include "MouseHandler.h"
#include<vector>
#include <algorithm>
#include "GraphicsContainer.h"

namespace g
{
	class MouseMotionHandler;


	class GameState
	{
	public:

		GameState() : root_container_(0, 0)
		{
		}
		virtual ~GameState()
		{

		}
		void add_graphics(Graphics* g);
		void add_action(UpdateAction* a);
		void add_key_handler(KeyHandler* k);
		void add_mouse_click_handler(CollisionComputable* c, MouseHandler* h);
		void add_mouse_motion_handler(CollisionComputable* c, MouseMotionHandler* h);

		void remove_graphics(Graphics* g);
		void remove_action(UpdateAction* a);
		void remove_key_handler(KeyHandler* k);
		void remove_mouse_click_handler(CollisionComputable* c, MouseHandler* h);
		void remove_mouse_click_handler(MouseHandler* h);
		const g::GraphicsContainer & graphics_container() const;
		const std::vector<UpdateAction*> & actions_vector() const;
		const std::vector<g::KeyHandler*> & key_handlers() const;
		const std::vector<std::pair<g::CollisionComputable*, g::MouseHandler*>> & click_handlers() const;
		void removeMouseMotionHandler(CollisionComputable* c, MouseMotionHandler* h);
		void removeMouseMotionHandler(MouseMotionHandler* h);
		const std::vector<std::pair<CollisionComputable*, MouseMotionHandler*>> & mouse_motion_handlers() const;
	private:
		GraphicsContainer root_container_;
		std::vector<UpdateAction*> actions_vector_;
		std::vector<KeyHandler*> key_handlers_;
		std::vector<std::pair< CollisionComputable*, MouseHandler*>> click_vector_;
		std::vector<std::pair<CollisionComputable*, MouseMotionHandler*>> mouse_move_vector_;

	};

}


#endif // GameState_H