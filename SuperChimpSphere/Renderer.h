#pragma once
#include <d3d11.h>
class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;
	~Renderer();
	void EndFrame();
private:
	ID3D11Device* device = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
};

