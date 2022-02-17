//
// Created by greg on 31.01.2022.
//
#include "Game.h"

Game* Game::instance = nullptr;

G_Display Game::display = (G_Display){{}, (Vector3){0.4f, 0.0f, 0.0f}, (int)SCR_W, (int)SCR_H, {}, {} };

Game::Game ( ) {
	G_InitDisplay();
	G_InitTextures();
    G_InitHero();
    G_InitHeroInput();
    mountain = new Mountain();
}

Game::~Game( ) {
}

void Game::CleanupBeforeExit() {
    G_DestroyHero();
    G_DestroyHeroInput();
    G_UnloadTextures();
    delete mountain;
    G_UnloadShaders();
    CloseWindow();
}

void Game::Create ( ) {
	instance = new Game();
}

void Game::Destroy ( ) {
	delete instance;
	instance = nullptr;
}

Game *Game::Instance ( ) {
	return instance;
}

void Game::Run ( ) {

//    RenderTexture2D target = LoadRenderTexture(display.scr_w, display.scr_h );

	while ( ! WindowShouldClose() ) {
		float dt = GetFrameTime();
		double et = GetTime();

        input_handler->HandleInput( dt, et );
		G_UpdateCamera(dt, et);
		hero->Update( dt, et );

        BeginDrawing();
		{
			ClearBackground(RAYWHITE );
			BeginMode3D( display.cam );
			{
                mountain->Draw();
                hero->Draw();
				DrawGrid(100, 0.5);
			}
			EndMode3D();
			hero->Draw2D();
			G_DrawCamInfo();
		}
        EndDrawing();

//        BeginDrawing();
//            ClearBackground(RAYWHITE);
//            BeginShaderMode( display.car_shader );
//                DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
//            EndShaderMode();
//        EndDrawing();
	}
}

void Game::G_InitDisplay() {
	InitWindow( SCR_W, SCR_H, "Arjuno" );
    G_LoadShaders();
	G_SetupCamera();
}

void Game::G_UpdateCamera( float dt, double et ) {
//    UpdateCamera( &display.cam );
//    display.cam.position.x += display.cam_velocity.x * dt;
    auto hero_position_x = hero->H_GetPosition().x;
    display.cam.position.x = Lerp( display.cam.position.x, hero_position_x , dt * 2 );
    display.cam.target.x = Lerp( display.cam.target.x, hero_position_x, dt * 2 );

}

void Game::G_DrawCamInfo() {
	auto pos = std::to_string(display.cam.position.x) + " : " + std::to_string(display.cam.position.y) + " : " + std::to_string(display.cam.position.z);
	auto tar = std::to_string(display.cam.target.x) + " : " + std::to_string(display.cam.target.y) + " : " + std::to_string(display.cam.target.z);
	DrawText(pos.c_str(), 10, 100, 14, RED );
	DrawText(tar.c_str(), 10, 140, 14, RED );
}

void Game::G_LoadShaders() {
    display.car_shader = LoadShader(SHADERS_PATH_330"base.vs", SHADERS_PATH_330"grayscale.fs" );
    display.transparent_shader = LoadShader(SHADERS_PATH_330"base.vs", SHADERS_PATH_330"alpha_discard.fs" );
}

void Game::G_SetupCamera() {
	display.cam.position = (Vector3){ 0.0f, 2.0f, 7.0f };
	display.cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	display.cam.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	display.cam.fovy = 45.0f;
	display.cam.projection = CAMERA_PERSPECTIVE;
//	SetCameraMode( display.cam, CAMERA_CUSTOM );
	SetCameraMode( display.cam, CAMERA_FREE );
	SetTargetFPS( 60 );
}

void Game::G_InitTextures() {
	Images::Create();
	Images::Instance()->LoadImages(Assets::trucks_bodies );
	Images::Instance()->LoadImages(Assets::trucks_chassis );
}

void Game::G_UnloadTextures() {
	Images::Destroy();
	std::cout << "GAME: Unloading textures" << std::endl;
}

void Game::G_DestroyHero() {
	delete hero;
}

void Game::G_UnloadShaders() {
    UnloadShader( display.car_shader );
    UnloadShader( display.transparent_shader );
}

void Game::G_InitHero() {
    hero = new Hero();
}

void Game::G_InitHeroInput() {
    input_handler = new InputHandler{ *hero };
}

void Game::G_DestroyHeroInput() {
    delete input_handler;
}
