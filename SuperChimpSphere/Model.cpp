#include "Model.h"
#include "Mesh.h"
#include "MeshCollider.h"

Model::Model(Renderer& renderer, std::string modelPath, std::string texturePath)
{
	auto* mesh = dynamic_cast<Mesh*>(AddComponent(std::make_unique<Mesh>(renderer, modelPath, texturePath)));
	transform.scale = Vector3(0.5F, 0.5F, 0.5F);
}
