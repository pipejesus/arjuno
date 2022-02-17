//
// Created by greg on 02.02.2022.
//

#include "Hero.h"
#include "../Images.h"

Hero::Hero ( ) {
	position = (Vector3){ 0.0f, 0.0f, 0.0f };
	size = (Vector2){ 1.0f, 0.431818182f };
	velocity = (Vector3){ 0.0f, 0.0f, 0.0f };
    max_velocity = 2.0f;
    min_velocity = -2.0f;
	timer = 0.0f;
    direction = (Vector2){ 1.0f, 0.0f };
	H_AddCar( "trucks/1_Bodies/13.png" );
}

Hero::~Hero ( ) {
	for (auto c:cars) {
		delete c;
	}
    cars.clear();
}

void Hero::Draw() {
	int i = 0;
	for ( auto car:cars ) {
		Vector3 current_car_pos = { position.x, position.y, position.z };
        current_car_pos.x = current_car_pos.x - ( i * size.x );
        car->Draw( current_car_pos );
        i++;
    }

    // debug circle
    DrawCircle3D( Vector3Add(H_GetPosition(), (Vector3){0, 0.0f, 0.3f} ), 0.25f, (Vector3){0, 0, 0}, 0.0f, (Color){255, 0, 0, 255});
}

void Hero::H_AddCar( std::string image_name ) {
	auto car = new Hero_Car( image_name, size );
	cars.push_back( car );
}

void Hero::H_AccelerateRight( float dt, double et ) {
    velocity.x = Lerp(velocity.x, max_velocity, dt * 5 );
}

void Hero::H_AccelerateLeft( float dt, double et ) {
    velocity.x = Lerp(velocity.x, min_velocity, dt * 5 );
}

void Hero::Decelerate( float dt, double et ) {
    velocity.x = Lerp(velocity.x, 0.0f, dt*10);
}

void Hero::H_ChangeDirectionLeft() {
    direction.x = -1;
}

void Hero::H_ChangeDirectionRight() {
    direction.x = 1;
}

void Hero::Update ( float dt, double et ) {
	timer += dt;
	position.x += dt * velocity.x;

	for (auto c: cars) {
		c->Update( dt, et );
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

void Hero::H_RemoveLastCar() {
    cars.pop_back();
}

Vector3 Hero::H_GetPosition() {
    if ( direction.x >= 0 ) {
        return position;
    }

    Vector3 subs {0, 0, 0 };
    subs.x = ( (float)cars.size() - 1 ) * size.x;
    return Vector3Subtract( position, subs );
}
