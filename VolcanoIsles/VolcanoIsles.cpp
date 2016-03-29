// VolcanoIsles.cpp : Defines the entry point for the console application.
//

#include<SDL.h>
#include "Game.h"
#include "GameEngine/GameManager.h"
#include "VolcanoGameState.h"


namespace g {
	class GameManager;
}

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
int main(int argc, char * args[])
{
	//Game g;
	//g.init("VOLCANO ISLES", 100, 100, 480, 640, 0);
	//g.run();
	//SDL_Delay(5000);
	//SDL_Quit();
	g::GameManager volcano_game_manager("VOLCANO ISLES", 650, 850);
	volcano_game_manager.set_background_color(colors::white());
	auto volcanoGame = std::make_unique<VolcanoGameState>();
	volcanoGame->init();
	volcano_game_manager.start(std::move(volcanoGame));
	return 0;
}

