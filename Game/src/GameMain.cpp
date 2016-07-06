#include <stdio.h>

#include <Core\Game.h>
#include <Core\GameDescription.h>
#include <Core\Log.h>
#include "GameState.h"


using namespace core;

int main(int argc, char* argv[])
{
	Game *game = Game::Instance();

	GameDescription *lGameDescription = new GameDescription();

	lGameDescription->SetRenderDrawColor(0, 0, 0, 255);
	lGameDescription->SetScreenSize(576, 576);
	lGameDescription->SetFullScreen(FALSE);

	if (!game->Init("Titulo", *lGameDescription))
	{
		LogString("!game->Init(gameDescription)");
		return -1;
	}

	game::GameState *lGameState = new game::GameState();

	game->SetGameState(lGameState);

	delete lGameDescription;

	game->Run();

	return 0;

}