#include "Skybox.h"

Skybox::Skybox(Renderer& renderer, std::wstring _texturePath) : 
    Mesh(renderer, 
        { // Vertices
            // Bottom
            { -50.0F, -50.0F, -50.0F }, // 0
            { +50.0F, -50.0F, -50.0F }, // 1
            { -50.0F, -50.0F, +50.0F }, // 2
            { +50.0F, -50.0F, +50.0F }, // 3
        },
        { // Tris
            0,2,1,
            1,2,3,
        },
        { // Uvs
            { 0.25F, 0.0F },
            { 0.5F, 0.0F },
            { 0.25F, 1.0F / 3.0F },
            { 0.5F, 1.0F / 3.0F },
        })
{
    texturePath = _texturePath;
}
