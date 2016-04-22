#ifndef MedalsManager_H
#define MedalsManager_H
#include "GameEngine/StaticGraphicsContainer.h"
#include "GameEngine/Image.h"
#include "GameConstants.h"
#include "Player.h"

class MedalsManager:public g::StaticGraphicsContainer 
{
public:
	MedalsManager(int x, int y)
		: StaticGraphicsContainer(x, y), medal_count(0)
	{

	}
	void add_blue_medal()
	{
		add_medal("medal_blue");
	}
	void add_red_medal()
	{
		add_medal("medal_red");
	}

	void add_black_medal()
	{
		add_medal("medal_black");
	}
	void add_medal(Player player)
	{
		switch (player)
		{
		case Player::NONE:
			add_black_medal();
			break;
		case Player::BLUE:
			add_blue_medal();
			break;
		case Player::RED:
			add_red_medal();
			break;
		default:
			break;
		}
	}

private:
	std::size_t medal_count;
	void add_medal(const std::string& name)
	{
		add_child(std::move(std::make_unique<g::Image>(gameconst::medal_size*medal_count, 0, name)));
		++medal_count;
	}
};


#endif // MedalsManager_H
