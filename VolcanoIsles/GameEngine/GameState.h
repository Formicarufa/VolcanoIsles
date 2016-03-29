﻿#pragma once
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
	

class GameState
{
public:

	GameState(): root_container_(0,0)
	{
	}
	virtual ~GameState()
	{
		
	}
	void addGraphics(Graphics* g);
	void addAction(UpdateAction* a);
	void addKeyHandler(KeyHandler* k);
	void addMouseClickHandler(CollisionComputable* c, MouseHandler* h);
	//void addMouseOverHandler(CollisionComputable* c, MouseHandler* h);
	//void addMouseLeaveListener(CollisionComputable*c, MouseHandler* h);

	void removeGraphics(Graphics* g);
	void removeAction(UpdateAction* a);
	void removeKeyHandler(KeyHandler* k);
	void removeMouseClickHandler(CollisionComputable* c, MouseHandler* h);
	const g::GraphicsContainer & graphics_container() const;
	const std::vector<UpdateAction*> & actions_vector() const;
	const std::vector<g::KeyHandler*> & key_handlers() const;
	const std::vector<std::pair<g::CollisionComputable*, g::MouseHandler*>> & click_handlers() const;
	//void removeMouseOverHandler(CollisionComputable* c, MouseHandler* h);
	//void removeMouseLeaveListener(CollisionComputable*c, MouseHandler* h);
private:
	GraphicsContainer root_container_;
	std::vector<UpdateAction*> actions_vector_;
	std::vector<KeyHandler*> key_handlers_;
	std::vector<std::pair< CollisionComputable*,  MouseHandler*>> click_vector_;

};

}


#endif // GameState_H