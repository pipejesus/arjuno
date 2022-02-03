//
// Created by greg on 31.01.2022.
//
#include "Game.h"

Game* Game::instance = nullptr;

G_Display Game::display = (G_Display){
	{ 0 },
	(Vector3){0.4f, 0.0f, 0.0f},
	SCR_W,
	SCR_H
};

Game::Game ( ) {
	G_InitDisplay();
	G_InitTextures();
	hero = new Hero();
}

Game::~Game( ) {
	G_DestroyHero();
	G_UnloadTextures();
}

void Game::Create ( ) {
	instance = new Game();
}

void Game::Destroy ( ) {
	CloseWindow();
	delete instance;
	instance = nullptr;
}

Game *Game::Instance ( ) {
	return instance;
}

void Game::Run ( ) {
	while ( ! WindowShouldClose() ) {
		float dt = GetFrameTime();
		double et = GetTime();
		UpdateCamera( &(display.cam) );
		G_UpdateCamera(dt, et);

		hero->Update( dt, et );

		BeginDrawing();
		{
			ClearBackground(RAYWHITE);
			BeginMode3D( display.cam );
			{
				hero->Draw();
				DrawGrid(100, 0.5);
			}
			EndMode3D();
			hero->Draw2D();
			G_DrawCamInfo();
			DrawFPS(10, 10);
		}
		EndDrawing();
	}
}

void Game::G_InitDisplay() {
	InitWindow( SCR_W, SCR_H, "Arjuno" );
	G_SetupCamera();
}

void Game::G_UpdateCamera( float dt, double et ) {
	display.cam.position.x += display.cam_velocity.x * dt;
	display.cam.target.x += display.cam_velocity.x * dt;
}

void Game::G_DrawCamInfo() {
	auto pos = std::to_string(display.cam.position.x) + " : " + std::to_string(display.cam.position.y) + " : " + std::to_string(display.cam.position.z);
	auto tar = std::to_string(display.cam.target.x) + " : " + std::to_string(display.cam.target.y) + " : " + std::to_string(display.cam.target.z);
	DrawText(pos.c_str(), 10, 100, 14, RED );
	DrawText(tar.c_str(), 10, 140, 14, RED );
}
void Game::G_SetupCamera() {
	display.cam.position = (Vector3){ 0.0f, 2.0f, 5.0f };
	display.cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	display.cam.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	display.cam.fovy = 45.0f;
	display.cam.projection = CAMERA_PERSPECTIVE;
//	SetCameraMode( display.cam, CAMERA_CUSTOM );
	SetCameraMode( display.cam, CAMERA_FREE );
	SetTargetFPS( 60 );
}

void Game::G_InitTextures() {
	Textures::Create();
	Textures::Instance()->LoadImages( Assets::trucks_bodies );
	Textures::Instance()->LoadImages( Assets::trucks_chassis );
}

void Game::G_UnloadTextures() {
	Textures::Destroy();
	std::cout << "GAME: Unloading textures" << std::endl;
}

void Game::G_DestroyHero() {
	delete hero;
}