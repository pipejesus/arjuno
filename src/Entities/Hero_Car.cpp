//
// Created by greg on 02.02.2022.
//

#include "Hero_Car.h"
#include "../Game.h"

Hero_Car::Hero_Car ( std::string main_sprite_fn, Vector2 hero_size ) {
	model_main = HC_CreateModelMain( main_sprite_fn, hero_size );
	main_sprite_frame = 0;
	main_sprite_frame_count = 4;
	sprite_time_passed = 0.0f;
	rel_position = (Vector3){0.0f, 0.0f, 0.0f};
	wobble_start = (float)( rand() % 360 );
}

Model Hero_Car::HC_CreateModelMain( std::string image_name, Vector2 hero_size ) {
	Image car_image = Textures::Instance()->GetImage( image_name );
	Texture2D texture = LoadTextureFromImage( car_image );

	auto mesh = GenMeshPlane( hero_size.x, hero_size.y, 1, 1 );
	auto model = LoadModelFromMesh(mesh);
	model.transform = MatrixMultiply( model.transform, MatrixRotateX( DEG2RAD * -90.0f ) );
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

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
	DrawText( napisik.c_str(), pos.x, pos.y, 14, BLACK);
}
