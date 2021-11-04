#pragma once
#include "Mesh.h"
class Skybox : public Mesh
{
public:
	Skybox(Renderer& renderer, std::wstring _texturePath);
};

