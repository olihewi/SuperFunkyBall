#pragma once
#include <d3d11.h>
#include "Colour.h"
#include <wrl.h>
class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;
	void EndFrame();
	void SetBackground(Colour c);
	void RenderTestTriangle(float angle);
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> targetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;

	Colour backgroundColour = Colours::CornflowerBlue;
};

