//
// Created by greg on 02.02.2022.
//

#include "Hero_Car.h"
#include "../Game.h"

/**
 * Hero Car Constructor.
 */
Hero_Car::Hero_Car ( std::string main_sprite_fn, Vector2 hero_size ) {
	rel_position = (Vector3){0.0f, 0.0f, 0.0f};
	wobble_start = (float)( rand() % 360 );
	spritesheet_main = new SpriteSheet( (std::vector<std::string>){ DIR_TRUCK_BODIES"13.png", DIR_TRUCK_BODIES"13_2.png" }, 2 );
	spritesheet_wheels = new SpriteSheet( DIR_TRUCK_CHASSIS"5.png", 14, 48 );
	HC_CreateModelMain( main_sprite_fn, hero_size );
	model_wheels = HC_CreateModelWheels();
}

/**
 * Hero Car Destructor.
 */
Hero_Car::~Hero_Car ( ) {
    UnloadModel( model_main );
    UnloadModel( model_wheels );
    delete spritesheet_main;
    delete spritesheet_wheels;
}

/**
 * Creates the model for the current car.
 * Sets the texture and initial transform ( to rotate the plane to face the camera )
 */
void Hero_Car::HC_CreateModelMain( std::string image_name, Vector2 hero_size ) {
	mesh_main = GenMeshPlane( hero_size.x, hero_size.y, 1, 1 );
	model_main = LoadModelFromMesh(mesh_main);
	model_main.transform = MatrixMultiply( model_main.transform, MatrixRotateX( DEG2RAD * -90.0f ) );
	model_main.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *( spritesheet_main->GetCurrentFrameTexture() );
    model_main.materials[0].shader = Game::display.car_shader;
}

/**
 * Creates the model for car's wheels.
 */
Model Hero_Car::HC_CreateModelWheels ( ) {

	auto mesh = GenMeshPlane( 0.5f, 0.5f, 1, 1 );
	auto model = LoadModelFromMesh(mesh);
	model.transform = MatrixMultiply( model.transform, MatrixRotateX( DEG2RAD * -90.0f ) );
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *( spritesheet_wheels->GetCurrentFrameTexture() );

	return model;
}

/**
 * @todo only change texture when sprite changed!
 */
void Hero_Car::Update ( float dt, double et ) {
	spritesheet_main->Update( dt, et );
	spritesheet_wheels->Update( dt, et );

	if ( spritesheet_main->HasFrameChanged() ) {
		model_main.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(spritesheet_main->GetCurrentFrameTexture());
	}

	if ( spritesheet_wheels->HasFrameChanged() ) {
		model_wheels.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(spritesheet_wheels->GetCurrentFrameTexture());
	}

	rel_position.y = sin( et * 6 + wobble_start ) / 64;
}

void Hero_Car::Draw ( Vector3 position ) {
	auto calculated_position = Vector3Add( position, rel_position);

	auto calculated_position_wheels_back = Vector3{ calculated_position.x, calculated_position.y, calculated_position.z };
	auto calculated_position_wheels_front = Vector3{ calculated_position.x, calculated_position.y, calculated_position.z };
	calculated_position_wheels_back.y -= 0.08f;
	calculated_position_wheels_back.x -= 0.25f;
	calculated_position_wheels_back.z += 0.05f;

	calculated_position_wheels_front.y -= 0.08f;
	calculated_position_wheels_front.x += 0.25f;
	calculated_position_wheels_front.z += 0.05f;

	DrawModel( model_main, calculated_position, 1.0f, WHITE );
	DrawModel( model_wheels, calculated_position_wheels_back, 1.0f, WHITE );
	DrawModel( model_wheels, calculated_position_wheels_front, 1.0f, WHITE );
}

void Hero_Car::Draw2D ( Vector3 position ) {
	std::string napisik {};
	switch ( spritesheet_main->GetCurrentFrame() ) {
		case 0:
			napisik = "CHOCO";
			break;
		case 1:
			napisik = "LOCO";
			break;
	}
	auto pos = GetWorldToScreen( position, Game::display.cam );
	DrawText( napisik.c_str(), pos.x, pos.y - 49.0f, 15, BLUE );
}
