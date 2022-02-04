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
	explicit SpriteSheet( std::vector<std::string> fnames ); 	// a list of file names, each holding separate animation frame
	explicit SpriteSheet( std::string fn );						// single-frame sprite
	explicit SpriteSheet( std::string fn, int count );			// single-file multiple-frames
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

	void AddSingleTexture ( std::string fn );
};


#endif //ARJUNO_SPRITESHEET_H
