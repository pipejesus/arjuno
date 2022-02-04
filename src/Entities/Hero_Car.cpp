//
// Created by greg on 02.02.2022.
//

#include "Hero_Car.h"
#include "../Game.h"

Hero_Car::Hero_Car ( std::string main_sprite_fn, Vector2 hero_size ) {
	main_sprite_frame = 0;
	main_sprite_frame_count = 2;
	sprite_time_passed = 0.0f;
	rel_position = (Vector3){0.0f, 0.0f, 0.0f};
	wobble_start = (float)( rand() % 360 );
	spritesheet_main = {};

	model_main = HC_CreateModelMain( main_sprite_fn, hero_size );
}

Model Hero_Car::HC_CreateModelMain( std::string image_name, Vector2 hero_size ) {
	Image car_image = Textures::Instance()->GetImage( image_name );
	Image car_image_2 = Textures::Instance()->GetImage( DIR_TRUCK_BODIES"13_2.png" );

	spritesheet_main.push_back( LoadTextureFromImage( car_image ) );
	spritesheet_main.push_back( LoadTextureFromImage( car_image_2 ) );

	auto mesh = GenMeshPlane( hero_size.x, hero_size.y, 1, 1 );
	auto model = LoadModelFromMesh(mesh);
	model.transform = MatrixMultiply( model.transform, MatrixRotateX( DEG2RAD * -90.0f ) );
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = spritesheet_main[0];

	return model;
}

Hero_Car::~Hero_Car ( ) {
	UnloadModel( model_main );
}

void Hero_Car::Update ( float dt, double et ) {
	sprite_time_passed+= dt;
	if ( sprite_time_passed >= 1.0f ) {
		sprite_time_passed = 0.0f;
		main_sprite_frame++;
		main_sprite_frame = main_sprite_frame % main_sprite_frame_count;
		model_main.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = spritesheet_main[ main_sprite_frame ];
	}
	rel_position.y = sin( et * 6 + wobble_start ) / 32;

	std::cout << rel_position.y << std::endl;
}

void Hero_Car::Draw ( Vector3 position ) {
	auto calculated_position = Vector3Add( position, rel_position);
	DrawModel( model_main, calculated_position, 1.0f, WHITE );
}

void Hero_Car::Draw2D ( Vector3 position ) {
	std::string napisik = "Hello" + std::to_string(main_sprite_frame);
	auto pos = GetWorldToScreen( position, Game::display.cam );
	DrawText( napisik.c_str(), pos.x, pos.y - 35.0f, 14, BLACK);
}

Model Hero_Car::HC_CreateModelWheels ( ) {
	Image wheels_image = Textures::Instance()->GetImage( DIR_TRUCK_CHASSIS"5.png" );
	Texture2D texture = LoadTextureFromImage( wheels_image );
	auto scale = Textures::CalculateScale( wheels_image );

	auto mesh = GenMeshPlane( 1.0f, 2.0f, 1, 1 );
	auto model = LoadModelFromMesh(mesh);
	model.transform = MatrixMultiply( model.transform, MatrixRotateX( DEG2RAD * -90.0f ) );
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

	return model;
}
