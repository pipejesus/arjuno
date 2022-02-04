//
// Created by greg on 02.02.2022.
//

#ifndef ARJUNO_HERO_CAR_H
#define ARJUNO_HERO_CAR_H


#include <string>
#include <map>
#include "raylib.h"
#include "raymath.h"
#include "../Textures.h"

enum class Hero_Car_Type {
	MAIN,
	PASSENGER,
};

class Hero_Car {
public:
	Hero_Car( std::string main_sprite_fn, Vector2 hero_size );
	~Hero_Car();
	void Update( float dt, double et );
	void Draw( Vector3 position );
	void Draw2D( Vector3 position );
private:
	Model model_main;
	Model model_wheels;

	Vector3 rel_position;
	std::map<std::string, int> animations;
	float wobble_start;
	int main_sprite_frame;
	int main_sprite_frame_count;
	float sprite_time_passed;

	std::vector<Texture> spritesheet_main;
	Model HC_CreateModelMain ( std::string image_name, Vector2 hero_size );
	static Model HC_CreateModelWheels();
};


#endif //ARJUNO_HERO_CAR_H
