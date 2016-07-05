#include <stdio.h>

#include <Core\Game.h>
#include <Core\GameDescription.h>
#include <Core\Log.h>


using namespace core;

int main(int argc, char* argv[])
{
	Game *game = Game::Instance();

	GameDescription *gameDescription = new GameDescription();

	gameDescription->SetRenderDrawColor(255, 250, 0, 255);
	gameDescription->SetScreenSize(600, 600);
	gameDescription->SetFullScreen(FALSE);

	if (!game->Init("Titulo", *gameDescription))
	{
		LogString("!game->Init(gameDescription)");
		return -1;
	}

	delete gameDescription;

	game->Run();

	return 0;

}