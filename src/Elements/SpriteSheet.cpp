//
// Created by greg on 03.02.2022.
//

#include "SpriteSheet.h"

SpriteSheet::~SpriteSheet ( ) {
	for ( auto texture: texture_frames ) {
		UnloadTexture( texture );
	}
    texture_frames.clear();
}

Texture* SpriteSheet::GetCurrentFrameTexture ( ) {
	return &(texture_frames[current_frame]);
}

int SpriteSheet::GetCurrentFrame() {
	return current_frame;
}

void SpriteSheet::Update ( float dt, double et ) {
	time_passed += dt;
	if ( time_passed >= FPS  ) {
		time_passed = 0.0f;
		previous_frame = current_frame;
		current_frame = ( ++current_frame ) % frames_count;
	}
}

/**
 * Constructor for creating an animation spritesheet made of
 * multiple, separate image files.
 */
SpriteSheet::SpriteSheet ( std::vector<std::string> fnames, int fps ) {
	for ( auto fn: fnames ) {
		SS_AddSingleTexture( fn );
	}

	frames_count = texture_frames.size();
	current_frame = previous_frame = 0;
	time_passed = 0.0f;
	FPS = 1.0f / (float)fps;

	SS_GetFrameSize();
}

/**
 * Constructor for creating a single-image spritesheet (no animation)
 */
SpriteSheet::SpriteSheet ( std::string fn ) {
	SS_AddSingleTexture( fn );

	frames_count = 1;
	current_frame = previous_frame = 0;
	time_passed = 0.0f;
	FPS = 0.0f;

	SS_GetFrameSize();
}

/**
 * Constructor for creating animated spritesheet made of images
 * placed in columns, in one image file.
 */
SpriteSheet::SpriteSheet ( std::string fn, int fps, int src_frame_width ) {
	Image src = Textures::Instance()->GetImage( fn );
	auto src_w = (float)src.width;
	auto src_h = (float)src.height;
	int src_frames_count = (int)(src_w / (float)src_frame_width);
	std::vector<Image> src_frames;

	float x = 0;
	float y = 0;

	for ( int i = 0; i < src_frames_count; ++i ) {
		auto rect = Rectangle{ x, y, (float)src_frame_width, src_h };
		Image single_image_frame = ImageFromImage( src, rect );
		Texture2D texture = LoadTextureFromImage( single_image_frame );
		texture_frames.push_back( texture );
		UnloadImage( single_image_frame );
		x += (float)src_frame_width;
	}

	frames_count = texture_frames.size();
	current_frame = previous_frame = 0;
	time_passed = 0.0f;
	FPS = 1.0f / (float)fps;

}

void SpriteSheet::SS_AddSingleTexture( std::string fn ) {
	Image img = Textures::Instance()->GetImage( fn );
	Texture2D texture = LoadTextureFromImage( img );
	texture_frames.push_back( texture );
}

bool SpriteSheet::HasFrameChanged ( ) {
	return current_frame != previous_frame;
}

void SpriteSheet::SS_GetFrameSize ( ) {
	if ( !texture_frames.empty() ) {
		frame_width_f = (float)texture_frames[0].width;
		frame_height_f = (float)texture_frames[0].height;
		frame_width_i = texture_frames[0].width;
		frame_height_i = texture_frames[0].height;
	}
}
