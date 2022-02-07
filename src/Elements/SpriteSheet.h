//
// Created by greg on 03.02.2022.
//

#ifndef ARJUNO_SPRITESHEET_H
#define ARJUNO_SPRITESHEET_H


#include <vector>
#include <string>
#include "raylib.h"
#include "../Textures.h"

class SpriteSheet {
public:
	explicit SpriteSheet( std::vector<std::string> fnames, int fps ); 	// a list of file names, each holding separate animation frame
	explicit SpriteSheet( std::string fn );						// single-frame sprite
	explicit SpriteSheet( std::string fn, int fps, int src_frame_width );			// single-file multiple-frames
	~SpriteSheet();

	Texture* GetCurrentFrameTexture();
	int GetCurrentFrame ( );
	void Update( float dt, double et );
	bool HasFrameChanged();

protected:
	int frames_count;
	int current_frame;
	int previous_frame;
	float time_passed;
	std::vector<Texture> texture_frames;
	float frame_width_f;
	float frame_height_f;
	int frame_width_i;
	int frame_height_i;
	float FPS;

	void SS_AddSingleTexture ( std::string fn );
	void SS_GetFrameSize ( );
};


#endif //ARJUNO_SPRITESHEET_H
