//
// Created by greg on 03.02.2022.
//

#include "SpriteSheet.h"

SpriteSheet::~SpriteSheet ( ) {
	for ( auto texture: texture_frames ) {
		UnloadTexture( texture );
	}
}

Texture* SpriteSheet::GetCurrentFrameTexture ( ) {
	return &(texture_frames[current_frame]);
}

void SpriteSheet::Update ( float dt, double et ) {
	time_passed += dt;
	if ( time_passed >= 1.0f ) {
		time_passed = 0.0f;
		current_frame = ( ++current_frame ) % frames_count;
	}
}

SpriteSheet::SpriteSheet ( std::vector<std::string> fnames ) {
	for ( auto fn: fnames ) {
		AddSingleTexture( fn );
	}

	frames_count = texture_frames.size();
	current_frame = 0;
	time_passed = 0.0f;
}

SpriteSheet::SpriteSheet ( std::string fn ) {
	AddSingleTexture( fn );

	frames_count = 1;
	current_frame = 0;
	time_passed = 0.0f;
}

void SpriteSheet::AddSingleTexture( std::string fn ) {
	Image img = Textures::Instance()->GetImage( fn );
	Texture2D texture = LoadTextureFromImage( img );
	texture_frames.push_back( texture );
}

SpriteSheet::SpriteSheet ( std::string fn, int frames_count ) {

}
