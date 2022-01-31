#include "Game.h"

int main() {
	Game::Create();
	Game::Instance()->Run();
	Game::Destroy();
	return 0;
}