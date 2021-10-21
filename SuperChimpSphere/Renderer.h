#pragma once
#include <d3d11.h>
#include "Colour.h"
#include <wrl.h>
#include <vector>
#include "ConstantBuffer.h"
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
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> targetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;

	ConstantBuffer cb;
	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;

	Colour backgroundColour = Colours::CornflowerBlue;
};

