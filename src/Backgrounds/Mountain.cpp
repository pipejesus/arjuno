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
        float yf = (sin(a * 8) * 80 ) + 80;
        a+= DEG2RAD * step;
        for ( int y = (int)yf; y < img_h; ++y ) {

            ImageDrawPixel( &image, x, y, img_fill_color );
        }
    }
}

void Mountain::M_CreateModel() {

    mesh_size = (Vector3){ 10, 1, 1 };
    model_position = (Vector3){5.0f, 0.0f, -2.0f };
    model_position_offset = (Vector3){ -1 * mesh_size.x / 2, mesh_size.z, 0 };

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
    auto mountain_position_2 = Vector3Add(mountain_position, (Vector3){0.0f, 0.0f, -2.1f} );
    auto mountain_position_3 = Vector3Add(mountain_position, (Vector3){0.0f, 0.0f, 4.5f} );
    auto mountain_position_4 = Vector3Add(mountain_position, (Vector3){0.0f, 0.0f, 3.9f} );
    DrawModel( model, mountain_position, 1.0f, (Color){0,190,0,255} );
    DrawModel( model, mountain_position_2, 1.0f, (Color){0,120,0,255} );
    DrawModel( model, mountain_position_3, 1.0f, (Color){50,60,65,255} );
    DrawModel( model, mountain_position_4, 1.0f, (Color){60,70,75,255} );
}

Mountain::~Mountain() {
    UnloadImage( image );
    UnloadModel( model );
    UnloadTexture( texture );
}
