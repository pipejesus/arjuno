//
// Created by greg on 02.02.2022.
//

#include "Textures.h"

Textures* Textures::instance_ = nullptr;

void Textures::Create() {
	if ( instance_ == nullptr ) {
		instance_ = new Textures();
	}
}

Textures *Textures::Instance ( ) {
	return instance_;
}

Textures::Textures ( ): images{} {

}

void Textures::Destroy ( ) {
	delete instance_;
	instance_ = nullptr;
}

Textures::~Textures ( ) {
	std::unordered_map< std::string, Image>:: iterator itr;
	for ( itr = images.begin(); itr != images.end(); itr++) {
		UnloadImage( itr->second );
	}
	images.clear();
}

/**
* Loads a single image from disk.
*
* @since 2022.02.02
*/
Image Textures::LoadImageFromFile ( std::string image_path ) {
	std::string assets_path = ASSETS_PATH;
	assets_path.append( image_path );
	return LoadImage( assets_path.c_str() );
}

void Textures::LoadImages ( std::vector<std::string> images_paths ) {
	for ( auto image_path:images_paths ) {
		images.insert( std::make_pair( image_path, LoadImageFromFile( image_path ) ));
	}
}

Image Textures::GetImage ( std::string image_path ) {
	return images.at( image_path );
}

Vector2 Textures::CalculateScale ( Image &image ) {
	Vector2 scale = { 1.0f, 1.0f };

	return scale;
}
