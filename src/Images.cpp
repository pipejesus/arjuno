//
// Created by greg on 02.02.2022.
//

#include "Images.h"

Images* Images::instance_ = nullptr;

void Images::Create() {
	if ( instance_ == nullptr ) {
		instance_ = new Images();
	}
}

Images *Images::Instance ( ) {
	return instance_;
}

Images::Images ( ): images{} {

}

void Images::Destroy ( ) {
	delete instance_;
	instance_ = nullptr;
}

Images::~Images ( ) {
	std::unordered_map< std::string, Image >:: iterator itr;
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
Image Images::LoadImageFromFile (std::string image_path ) {
	std::string assets_path = ASSETS_PATH;
	assets_path.append( image_path );
	return LoadImage( assets_path.c_str() );
}

void Images::LoadImages (std::vector<std::string> images_paths ) {
	for ( auto image_path:images_paths ) {
		images.insert( std::make_pair( image_path, LoadImageFromFile( image_path ) ));
	}
}

Image Images::GetImage (std::string image_path ) {
	return images.at( image_path );
}

Vector2 Images::CalculateScale (Image &image ) {
	Vector2 scale = { 1.0f, 1.0f };

	return scale;
}
