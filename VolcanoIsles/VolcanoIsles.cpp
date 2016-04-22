// VolcanoIsles.cpp : Defines the entry point for the console application.
//

#include<SDL.h>
#include "Game.h"
#include "GameEngine/GameManager.h"
#include "VolcanoGameState.h"
#include <ctime>
#include "GameConstants.h"


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
	std::unique_ptr<PlayerMouseControl> c1 = std::make_unique<PlayerMouseControl>(volcanoGame.get());
	std::unique_ptr<PlayerMouseControl> c2 = std::make_unique<PlayerMouseControl>(volcanoGame.get());
	volcanoGame->set_player_controllers(c1.get(), c2.get());
	volcanoGame->init();
	volcano_game_manager.start(std::move(volcanoGame));
	return 0;
}

