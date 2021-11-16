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
	Mesh(Renderer& renderer, std::vector<Vector3> _vertices, std::vector<unsigned int> _triangles, std::vector<Vector2> _uvs, std::string _texturePath = "Textures/UV_Checker.png", std::wstring _pixelShaderPath = L"PSTexturedLit.cso");
	Mesh(Renderer& renderer, std::vector<Vector3> _vertices, std::vector<unsigned int> _triangles, std::vector<Vector2> _uvs, std::vector<Vector3> _normals, std::string _texturePath = "Textures/UV_Checker.png", std::wstring _pixelShaderPath = L"PSTexturedLit.cso");
	Mesh(Renderer& renderer, std::string filePath, std::string _texturePath);
	void Render(Renderer& renderer);
private:
	void OnMeshUpdated(Renderer& renderer);
public:
	static std::unique_ptr<Mesh> CreatePrimitiveCube(Renderer& renderer, Vector3 size);
	static std::unique_ptr<Mesh> CreatePrimitiveSphere(Renderer& renderer, float radius, unsigned int resolution, std::string _texturePath = "Textures/UV_Checker.png");
	// should be protected but hey ho
	std::vector<Vector3> vertices;
	std::vector<unsigned int> triangles;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;

protected:
	std::vector<std::shared_ptr<GraphicsComponent>> components;

	std::string texturePath = "";
	std::wstring pixelShaderPath = L"PSTexturedLit.cso";

	const std::vector<D3D11_INPUT_ELEMENT_DESC> elementDesc
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
};

