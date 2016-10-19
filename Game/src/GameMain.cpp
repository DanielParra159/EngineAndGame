#include "Types.h"
#include "Support/Vector3D.h"

#include "Core\Game.h"
#include "Core\GameDescription.h"
#include "Core\Log.h"


#include "IO\File.h"

#include "MenuState.h"

using namespace core;


int main(int argc, char* argv[])
{
	Game *game = Game::Instance();

	GameDescription *lGameDescription = new GameDescription();

	lGameDescription->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	lGameDescription->SetScreenSize(800, 600);
	lGameDescription->SetFullScreen(FALSE);
	lGameDescription->SetRootDir(".\\assets");
	lGameDescription->SetPhysicsGravity(Vector3D<float32>(0.0f, -9.8f, 0.0f));

	if (!game->Init("Game Screen", *lGameDescription))
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