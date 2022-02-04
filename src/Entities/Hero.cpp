//
// Created by greg on 02.02.2022.
//

#include "Hero.h"
#include "../Textures.h"

Hero::Hero ( ) {
	position = (Vector3){ 0.0f, 0.0f, 0.0f };
	size = (Vector2){ 1.0f, 0.431818182f };
	velocity = (Vector3){ 0.4f, 0.0f, 0.0f };
	timer = 0.0f;
	H_AddCar( "trucks/1_Bodies/13.png" );
}

Hero::~Hero ( ) {
	for (auto c:cars) {
		delete c;
	}
}

void Hero::Draw() {
	int i = 0;
	for ( auto car:cars ) {
		Vector3 current_car_pos = { position.x, position.y, position.z };
		current_car_pos.x = current_car_pos.x - ( i * size.x );
		car->Draw( current_car_pos );
		i++;
	}
}

void Hero::H_AddCar( std::string image_name ) {
	auto car = new Hero_Car( image_name, size );
	cars.push_back( car );
}

void Hero::Update ( float dt, double et ) {
	timer += dt;
	position.x += dt * velocity.x;
	for (auto c: cars) {
		c->Update( dt, et );
	}
	if ( timer >= 1.5 && cars.size() < 4 ) {
		H_AddCar( "trucks/1_Bodies/13.png" );
		velocity.x += 0.05f;
		timer = 0.0f;
	}

	if ( velocity.x >= 1.0f ) {
		velocity.x = 0.4f;
	}
}

void Hero::Draw2D ( ) {
	int i = 0;
	for ( auto car:cars ) {
		Vector3 current_car_pos = { position.x, position.y, position.z };
		current_car_pos.x = current_car_pos.x - ( i * size.x );
		car->Draw2D( current_car_pos );
		i++;
	}
}
