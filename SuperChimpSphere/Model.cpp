#include "Model.h"
#include "Mesh.h"

Model::Model(Renderer& renderer, std::string modelPath, std::wstring texturePath)
{
	AddComponent(std::make_unique<Mesh>(renderer, modelPath, texturePath));
	//transform *= DirectX::XMMatrixScaling(0.5F, 0.5F, 0.5F);
	transform.scale = Vector3(0.5F, 0.5F, 0.5F);
}
