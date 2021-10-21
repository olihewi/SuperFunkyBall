#pragma once
#include <d3d11.h>
#include "Colour.h"
#include <wrl.h>
#include <vector>
#include "ConstantBuffer.h"
#include <memory>
class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;
	void EndFrame();
	void SetBackground(Colour c);
	// Getters
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

	void SetModelMatrix(const DirectX::XMMATRIX& modelMatrix);
	void SetViewMatrix(const DirectX::XMMATRIX& viewMatrix);
	void SetProjectionMatrix(const DirectX::XMMATRIX& projectionMatrix);
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> targetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;

	Colour backgroundColour = Colours::CornflowerBlue;

	ConstantBuffer::ConstantBufferData modelViewProjection
	{
		DirectX::XMMatrixIdentity(),
		//DirectX::XMMatrixTranslation(0.0F, 1.0F, 2.0F),
		{-1.00000000f, 0.00000000f,  0.00000000f,  0.00000000f,
			 0.00000000f, 0.89442718f,  0.44721359f,  0.00000000f,
			 0.00000000f, 0.44721359f, -0.89442718f, -2.23606800f,
			 0.00000000f, 0.00000000f,  0.00000000f,  1.00000000f},
		{1.0F, 0.0f,    0.0f,  0.0f,
			0.0f,   1.5F,  0.0f,  0.0f,
			0.0f,   0.0f,   -1.0f, -0.01f,
			0.0f,   0.0f,   -1.0f,  0.0f}
		//DirectX::XMMatrixPerspectiveLH(1.0F, 720.0F / 1080.0F, 0.5F, 10.0F)
	};
	std::unique_ptr<ConstantBuffer> constantBuffer;
};

