//
// Created by greg on 11.02.2022.
//

#include "Mountain.h"
#include "../Game.h"

Mountain::Mountain() {
    M_CreateModel();
}

void Mountain::M_GenerateImage( int img_w, int img_h ) {
    Color img_bg_color{ 254, 245, 245, 0 };
    Color img_fill_color{ 255,255,255, 255 };
    image = GenImageColor(img_w, img_h, img_bg_color );
//    ImageDrawRectangle( &image, 0, 0, img_w / 4, img_h / 4, img_fill_color );
    float a = 0.0f;
    float step = 360.0f / (float)img_w;

    for ( int x = 0; x < img_w; ++x ) {
        float yf = ( (sin(a * 20) * 140 ) + 140 ) * ( (sin(a * 20) * 10 ) + 10 );
        a+= DEG2RAD * step;
        for ( int y = (int)yf; y < img_h / 2; ++y ) {

            ImageDrawPixel( &image, x, y, img_fill_color );
        }
    }
}

void Mountain::M_CreateModel() {

    mesh_size = (Vector3){ 100, 1, 1 };
    model_position = (Vector3){0.0f, 0.0f, 0.0f };
    model_position_offset = (Vector3){ -1 * mesh_size.x / 2, mesh_size.z, -10 };

    M_GenerateImage( 1024, 1024 );
    texture = LoadTextureFromImage( image );
    mesh = GenMeshHeightmap(image, mesh_size);
    model = LoadModelFromMesh(mesh);

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    model.materials[0].shader = Game::display.transparent_shader;
    model.transform = MatrixMultiply( model.transform, MatrixRotateX( DEG2RAD * -90.0f ) );
}

Vector3 Mountain::M_CalcModelPosition() {
    return Vector3Add(model_position, model_position_offset);
}

void Mountain::Draw() {
    auto mountain_position = M_CalcModelPosition();
    DrawModel( model, mountain_position, 1.0f, (Color){0,120,0,255} );
}

Mountain::~Mountain() {
    UnloadImage( image );
    UnloadModel( model );
    UnloadTexture( texture );
}
