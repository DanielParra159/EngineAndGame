//#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <SOIL.h>

#include <stdio.h>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Types.h"

#include "Core\Game.h"
#include "Core\GameDescription.h"
#include "Core\Log.h"

#include "IO\File.h"

#include "TestState.h"

using namespace core;

// Shader sources
const GLchar* vertexSource =
"#version 150 core\n"
""
"in vec3 position;"
"in vec3 color;"
"in vec2 texcoord;"
""
"out vec3 Color;"
"out vec2 Texcoord;"
""
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 proj;"
"uniform vec3 overrideColor;"
""
"void main()"
"{"
"    Color = color * vec3(1.0, 1.0, 1.0);"
"    Texcoord = texcoord;"
"    gl_Position = proj * view * model * vec4(position, 1.0);"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
""
"in vec3 Color;"
"in vec2 Texcoord;"
""
"out vec4 outColor;"
""
"uniform sampler2D texKitten;"
"uniform sampler2D texPuppy;"
""
"void main()"
"{"
"    outColor = vec4(Color, 1.0);"
"}";
//"    outColor = vec4(triangleColor, 1.0);"


int main(int argc, char* argv[])
{

	auto t_start = std::chrono::high_resolution_clock::now();

	Game *game = Game::Instance();

	GameDescription *lGameDescription = new GameDescription();

	lGameDescription->SetRenderDrawColor(102, 150, 23, 255);
	lGameDescription->SetScreenSize(800, 600);
	lGameDescription->SetFullScreen(FALSE);
	lGameDescription->SetRootDir(".\\assets");

	if (!game->Init("Titulo", *lGameDescription))
	{
		LogString("!game->Init(gameDescription)");
		return -1;
	}

	game::TestState *lGameState = new game::TestState();

	game->ChangeGameState(lGameState);

	delete lGameDescription;

	game->Run();
	return 0;
}