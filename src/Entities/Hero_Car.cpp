//
// Created by greg on 02.02.2022.
//

#include "Hero_Car.h"
#include "../Game.h"

Hero_Car::Hero_Car ( std::string main_sprite_fn, Vector2 hero_size ) {
	rel_position = (Vector3){0.0f, 0.0f, 0.0f};
	wobble_start = (float)( rand() % 360 );
	spritesheet_main = new SpriteSheet( (std::vector<std::string>){ DIR_TRUCK_BODIES"13.png", DIR_TRUCK_BODIES"13_2.png" } );
	model_main = HC_CreateModelMain( main_sprite_fn, hero_size );
}

Model Hero_Car::HC_CreateModelMain( std::string image_name, Vector2 hero_size ) {

	auto mesh = GenMeshPlane( hero_size.x, hero_size.y, 1, 1 );
	auto model = LoadModelFromMesh(mesh);
	model.transform = MatrixMultiply( model.transform, MatrixRotateX( DEG2RAD * -90.0f ) );
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(spritesheet_main->GetCurrentFrameTexture());

	return model;
}

Hero_Car::~Hero_Car ( ) {
	delete spritesheet_main;
	UnloadModel( model_main );
}

/**
 * @todo only change texture when sprite changed!
 */
void Hero_Car::Update ( float dt, double et ) {
	spritesheet_main->Update( dt, et );

	if ( spritesheet_main->HasFrameChanged() ) {
		model_main.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(spritesheet_main->GetCurrentFrameTexture());
	}

	rel_position.y = sin( et * 6 + wobble_start ) / 32;

	std::cout << rel_position.y << std::endl;
}

void Hero_Car::Draw ( Vector3 position ) {
	auto calculated_position = Vector3Add( position, rel_position);
	DrawModel( model_main, calculated_position, 1.0f, WHITE );
}

void Hero_Car::Draw2D ( Vector3 position ) {
	std::string napisik = "Hello" + std::to_string( spritesheet_main->GetCurrentFrame());
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
