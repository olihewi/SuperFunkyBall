#pragma once
#include <DirectXMath.h>
#include "Vector3.h"
#include <vector>
#include <memory>
#include <wrl.h>
#include "Renderer.h"
#include "ConstantBuffer.h"
#include "GraphicsComponent.h"
class Mesh
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

	std::vector<std::unique_ptr<GraphicsComponent>> components;

	static Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	static Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
};

