//
// Created by greg on 03.02.2022.
//

#ifndef ARJUNO_ASSETS_H
#define ARJUNO_ASSETS_H

#define DIR_TRUCK_BODIES "trucks/1_Bodies/"
#define DIR_TRUCK_CHASSIS "trucks/2_Chassis/"

#include <vector>
#include <string>

struct Assets {
	static std::vector<std::string> trucks_bodies;
	static std::vector<std::string> trucks_chassis;
};


#endif //ARJUNO_ASSETS_H
