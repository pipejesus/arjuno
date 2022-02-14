#include "Game.h"

int main() {
	Game::Create();
	Game::Instance()->Run();
    Game::Instance()->CleanupBeforeExit();
	Game::Destroy();
	return 0;
}