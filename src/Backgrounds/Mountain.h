//
// Created by greg on 11.02.2022.
//

#ifndef ARJUNO_MOUNTAIN_H
#define ARJUNO_MOUNTAIN_H


#include "raylib.h"
#include "raymath.h"

class Mountain {

public:
    Mountain();
    ~Mountain();
    void Draw();

private:
    Model model;
    Image image;
    Mesh mesh;
    Texture2D texture;

    Vector3 model_position;
    Vector3 mesh_size;
    Vector3 model_position_offset;

    void M_CreateModel();
    Vector3 M_CalcModelPosition();

    void M_GenerateImage(int img_w, int img_h);
};


#endif //ARJUNO_MOUNTAIN_H
