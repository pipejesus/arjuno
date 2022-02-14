//
// Created by greg on 31.01.2022.
//

#ifndef ARJUNO_GAME_H
#define ARJUNO_GAME_H


#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#define SCR_W 1024
#define SCR_H 768

#include <iostream>
#include <raylib.h>
#include "Assets.h"
#include "Entities/Hero.h"
#include "Backgrounds/Mountain.h"

struct G_Display {
	Camera cam;
	Vector3 cam_velocity;
	int scr_w;
	int scr_h;
    Shader car_shader;
    Shader transparent_shader;
};

class Game {
public:
	static Game* Instance();
	static void Create();
	static void Destroy();
	void Run();
    void CleanupBeforeExit();

	static G_Display display;

private:
	static Game *instance;
	Hero *hero = nullptr;
    Mountain *mountain = nullptr;

	Game();
	~Game();
	void G_InitDisplay( );
	void G_InitTextures( );
	static void G_UnloadTextures ( );
	void G_SetupCamera ( );
	void G_DestroyHero ( );
	void G_DrawCamInfo ( );
	void G_UpdateCamera ( float dt, double et );

    void G_LoadShaders();

    void G_UnloadShaders();
};


#endif //ARJUNO_GAME_H
