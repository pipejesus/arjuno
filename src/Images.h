//
// Created by greg on 02.02.2022.
//

#ifndef ARJUNO_IMAGES_H
#define ARJUNO_IMAGES_H

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include "raylib.h"

class Images {
public:
	static void Create();
	static void Destroy();
	static Images* Instance();
	static Vector2 CalculateScale( Image &image );
	void LoadImages( std::vector<std::string> images_paths );
	Image GetImage( std::string image_path );

private:
	Images();
	~Images();
	static Images *instance_;
	static Image LoadImageFromFile( std::string image_path );
	std::unordered_map<std::string, Image> images;
};


#endif //ARJUNO_IMAGES_H
