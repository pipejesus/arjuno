//
// Created by greg on 02.02.2022.
//

#ifndef ARJUNO_HERO_H
#define ARJUNO_HERO_H


#include <vector>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Hero_Car.h"

class Hero {
public:
	Hero();
	~Hero();
	void Draw();
	void Draw2D();
	void Update( float dt, double et);
private:
	std::vector<Hero_Car *> cars;
	Vector3 position;
	Vector3 velocity;
	Vector2 size;

	float timer;
	void H_AddCar ( std::string image_name );
};


#endif //ARJUNO_HERO_H
