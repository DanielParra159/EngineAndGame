#include <stdio.h>

#include "Core\Game.h"
#include "Core\GameDescription.h"
#include "Core\Log.h"
#include "GameState.h"
#include "MenuState.h"


using namespace core;

int main(int argc, char* argv[])
{
	Game *game = Game::Instance();

	GameDescription *lGameDescription = new GameDescription();

	lGameDescription->SetRenderDrawColor(102, 150, 23, 255);
	lGameDescription->SetScreenSize(576, 576);
	lGameDescription->SetFullScreen(FALSE);

	if (!game->Init("Titulo", *lGameDescription))
	{
		LogString("!game->Init(gameDescription)");
		return -1;
	}

	game::MenuState *lGameState = new game::MenuState();

	game->ChangeGameState(lGameState);

	delete lGameDescription;

	game->Run();

	return 0;

}