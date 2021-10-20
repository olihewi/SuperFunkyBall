#pragma once
#include <DirectXMath.h>
#include "Vector3.h"
#include <vector>
#include <wrl.h>
#include "Renderer.h"
#include "ConstantBuffer.h"
class Mesh
{
public:
	Mesh(Renderer& renderer, std::vector<Vector3> _vertices, std::vector<unsigned int> _triangles);
	static void Register(Renderer& renderer);
	void Render(Renderer& renderer);
private:
	void OnMeshUpdated(Renderer& renderer);
public:
	static Mesh CreatePrimitiveCube(Renderer& renderer, Vector3 size);
	static Mesh CreatePrimitiveSphere(Renderer& renderer, float radius, unsigned int resolution);
private:
	std::vector<Vector3> vertices;
	std::vector<unsigned int> triangles;
	std::vector<DirectX::XMFLOAT2> uvs;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> triangleBuffer;

	static Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	static Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	static Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
};

