//
// Created by greg on 31.01.2022.
//
#include "Game.h"

Game* Game::instance = nullptr;

Game::Game ( ) = default;

void Game::Create ( ) {
	instance = new Game();
}

void Game::Destroy ( ) {
	delete instance;
	instance = nullptr;
}

Game *Game::Instance ( ) {
	return instance;
}

void Game::Run ( ) {
	std::cout << "Game runing!";
}
