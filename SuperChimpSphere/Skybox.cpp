#include "Skybox.h"

Skybox::Skybox(Renderer& renderer, std::string _texturePath) : 
    Mesh(renderer, 
        { // Bottom
            { -75.0F, -75.0F, -75.0F },
            { +75.0F, -75.0F, -75.0F },
            { -75.0F, -75.0F, +75.0F },
            { +75.0F, -75.0F, +75.0F },
            // Top
            { -75.0F, +75.0F, -75.0F },
            { +75.0F, +75.0F, -75.0F },
            { -75.0F, +75.0F, +75.0F },
            { +75.0F, +75.0F, +75.0F },
            // Front
            { -75.0F, -75.0F, +75.0F },
            { +75.0F, -75.0F, +75.0F },
            { -75.0F, +75.0F, +75.0F },
            { +75.0F, +75.0F, +75.0F },
            // Back
            { -75.0F, -75.0F, -75.0F },
            { +75.0F, -75.0F, -75.0F },
            { -75.0F, +75.0F, -75.0F },
            { +75.0F, +75.0F, -75.0F },
            // Left
            { -75.0F, -75.0F, +75.0F },
            { -75.0F, +75.0F, +75.0F },
            { -75.0F, -75.0F, -75.0F },
            { -75.0F, +75.0F, -75.0F },
            // Right
            { +75.0F, -75.0F, +75.0F },
            { +75.0F, +75.0F, +75.0F },
            { +75.0F, -75.0F, -75.0F },
            { +75.0F, +75.0F, -75.0F },
        },
        { // Tris
            0,1,2, 2,1,3,
            4,6,5, 6,7,5,
            8,9,10, 9,11,10,
            12,14,13, 13,14,15,
            16,17,18, 17,19,18,
            20,22,21, 22,23,21
        },
        { // Uvs
            // Bottom
            { 0.5F, 1.0F },
            { 0.25F, 1.0F },
            { 0.5F, 2.0/3.0F },
            { 0.25F, 2.0 / 3.0F },
            // Top
            { 0.25F, 0.0F },
            { 0.5F, 0.0F },
            { 0.25F, 1.0 / 3.0F },
            { 0.5F, 1.0 / 3.0F },
            // Front
            { 0.5F, 2.0 / 3.0F },
            { 0.25F, 2.0 / 3.0F },
            { 0.5F, 1.0 / 3.0F },
            { 0.25F, 1.0 / 3.0F },
            // Back
            { 0.75F, 2.0 / 3.0F },
            { 1.0F, 2.0 / 3.0F },
            { 0.75F, 1.0 / 3.0F },
            { 1.0F, 1.0 / 3.0F },
            // Left
            { 0.5F, 2.0 / 3.0F },
            { 0.5F, 1.0 / 3.0F },
            { 0.75F, 2.0 / 3.0F },
            { 0.75F, 1.0 / 3.0F },
            // Right
            { 0.25F, 2.0 / 3.0F },
            { 0.25F, 1.0 / 3.0F },
            { 0.0F, 2.0 / 3.0F },
            { 0.0F, 1.0 / 3.0F },
        },
        _texturePath,
        L"PSSkybox.cso")
{
}
