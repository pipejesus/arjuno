//
// Created by greg on 11.02.2022.
//

#include "Mountain.h"


Mountain::Mountain() {
    M_CreateModel();
}

void Mountain::M_CreateModel() {

    mesh_size = (Vector3){ 1, 1, 1 };
    model_position = (Vector3){0.0f, 0.0f, -2.0f };
    model_position_offset = (Vector3){ -1 * mesh_size.x / 2, mesh_size.z / 2, 0 };

    int img_w = 1024;
    int img_h = 1024;
    auto img_bg_color = (Color){0, 0, 0, 0};
    auto img_fill_color = (Color){5, 5, 5, 255};

    image = GenImageColor(img_w, img_h, img_bg_color );

    ImageDrawRectangle( &image, 0, 0, img_w / 2, img_h / 2, img_fill_color );

    texture = LoadTextureFromImage( image );

    mesh = GenMeshHeightmap(image, mesh_size);

    model = LoadModelFromMesh(mesh);

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    model.transform = MatrixMultiply( model.transform, MatrixRotateX( DEG2RAD * -90.0f ) );

}

Vector3 Mountain::M_CalcModelPosition() {
    return Vector3Add(model_position, model_position_offset);
}

void Mountain::Draw() {
    DrawModel( model, M_CalcModelPosition(), 1.0f, (Color){0,0,0,0} );
}

Mountain::~Mountain() {
    UnloadImage( image );
    UnloadMesh( mesh );
    UnloadModel( model );
    UnloadTexture( texture );
}
