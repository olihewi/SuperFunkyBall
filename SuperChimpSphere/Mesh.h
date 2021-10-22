#pragma once
#include <DirectXMath.h>
#include "Vector3.h"
#include <vector>
#include <memory>
#include <wrl.h>
#include "GameComponent.h"
#include "ConstantBuffer.h"
#include "GraphicsComponent.h"
class Mesh : public GameComponent
{
public:
	Mesh(Renderer& renderer, std::vector<Vector3> _vertices, std::vector<unsigned short> _triangles);
	void Render(Renderer& renderer);
private:
	void OnMeshUpdated(Renderer& renderer);
public:
	static Mesh CreatePrimitiveCube(Renderer& renderer, Vector3 size);
	static Mesh CreatePrimitiveSphere(Renderer& renderer, float radius, unsigned short resolution);
private:
	std::vector<Vector3> vertices;
	std::vector<unsigned short> triangles;
	std::vector<DirectX::XMFLOAT2> uvs;

	std::vector<std::shared_ptr<GraphicsComponent>> components;
};

