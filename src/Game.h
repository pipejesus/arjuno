//
// Created by greg on 31.01.2022.
//

#ifndef ARJUNO_GAME_H
#define ARJUNO_GAME_H

#include <iostream>

class Game {
public:
	static Game* Instance();
	static void Create();
	static void Destroy();
	void Run();
private:
	static Game *instance;
	Game();
};


#endif //ARJUNO_GAME_H
