// VolcanoIsles.cpp : Defines the entry point for the console application.
//

#include<SDL.h>
#include "Game.h"
#include "GameEngine/GameManager.h"
#include "VolcanoGameState.h"
#include <ctime>
#include "GameConstants.h"
#include "PlayerAIControl.h"


SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
int main(int argc, char * args[])
{
	//Game g;
	//g.init("VOLCANO ISLES", 100, 100, 480, 640, 0);
	//g.run();
	//SDL_Delay(5000);
	//SDL_Quit();
	srand(static_cast<unsigned int>(time(nullptr)));

	g::GameManager volcano_game_manager("VOLCANO ISLES", gameconst::HEIGHT, gameconst::WIDTH);
	volcano_game_manager.set_background_color(colors::white());
	auto volcanoGame = std::make_unique<VolcanoGameState>();
	//std::unique_ptr<PlayerMouseControl> c1 = std::make_unique<PlayerMouseControl>(volcanoGame.get());
	//std::unique_ptr<PlayerMouseControl> c2 = std::make_unique<PlayerMouseControl>(volcanoGame.get());
	std::unique_ptr<AbstractGameControl> c1;
	std::unique_ptr<AbstractGameControl> c2;
	std::string map_name;
	if (argc >=3)
	{
		std::string p1 = args[1];
		std::string p2 = args[2];
		if (p1=="player")
		{
			c1 = std::make_unique<PlayerMouseControl>(volcanoGame.get());
		} else if (p1=="ai")
		{
			c1 = std::make_unique<PlayerAIControl>(volcanoGame.get());
		} else
		{
			std::cout << "Unrecognized argument number 1. Expected 'player' or 'ai'.";
		}
		if (p2 == "player")
		{
			c2 = std::make_unique<PlayerMouseControl>(volcanoGame.get());
		}
		else if (p2 == "ai")
		{
			c2 = std::make_unique<PlayerAIControl>(volcanoGame.get());
		}
		else
		{
			std::cout << "Unrecognized argument number 2. Expected 'player' or 'ai'.";
		}
		if (argc >=4)
		{
			map_name = args[3];
		}
	}

	if (!c1) c1 = std::make_unique<PlayerMouseControl>(volcanoGame.get());
	if (!c2) c2 = std::make_unique<PlayerAIControl>(volcanoGame.get());
	bool map_provided=true;
	if (map_name=="")
	{
		map_provided = false;
		map_name = "maps/standard.map";
	}
	volcanoGame->set_player_controllers(c1.get(), c2.get());
	if (volcanoGame->init(map_name))
	{
		volcano_game_manager.start(std::move(volcanoGame));
	} else
	{
		std::cout << "Sorry, we were unable to start the game!";
		if (map_provided)
		{
			std::cout << "Ensure that the 3rd argument you provided was a correct path to a map file relative to the game folder "
				<< "and the file content is a valid map description.";
		}
	}
	return 0;
}

