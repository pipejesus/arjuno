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
	void Update( float dt, double et );
    void H_AccelerateRight( float dt, double et );
    void H_AccelerateLeft( float dt, double et );
    void H_ChangeDirectionRight();
    void H_ChangeDirectionLeft();
    void Decelerate( float dt, double et );
    void H_AddCar ( std::string image_name );
    void H_RemoveLastCar();

    Vector3 H_GetPosition();

private:
	std::vector<Hero_Car *> cars;
	Vector3 position;
    Vector2 direction;
	Vector3 velocity;
	Vector2 size;

	float timer;
    float max_velocity;
    float min_velocity;


};


#endif //ARJUNO_HERO_H
