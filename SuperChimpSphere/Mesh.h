#pragma once
#include <DirectXMath.h>
#include "Vertex.h"
#include <vector>
#include <memory>
#include <wrl.h>
#include "GameComponent.h"
#include "ConstantBuffer.h"
#include "GraphicsComponent.h"
#include <string>
class Mesh : public GameComponent
{
public:
	Mesh(Renderer& renderer, std::vector<Vector3> _vertices, std::vector<unsigned int> _triangles, std::vector<Vector2> _uvs);
	Mesh(Renderer& renderer, std::string filePath);
	void Render(Renderer& renderer);
private:
	void OnMeshUpdated(Renderer& renderer);
public:
	static std::unique_ptr<Mesh> CreatePrimitiveCube(Renderer& renderer, Vector3 size);
	static std::unique_ptr<Mesh> CreatePrimitiveSphere(Renderer& renderer, float radius, unsigned int resolution);
private:
	std::vector<Vector3> vertices;
	std::vector<unsigned int> triangles;
	std::vector<Vector2> uvs;

	std::vector<std::shared_ptr<GraphicsComponent>> components;
};

