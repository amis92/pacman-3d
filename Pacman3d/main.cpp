#include "Game.h"


int main(int argc, char** argv)
{
	Game::Init(&argc, argv);
	Game::RunMainLoop();
	return 0;
}
