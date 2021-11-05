#include "Renderer.h"
#include <d3dcompiler.h>
#include <array>
#include <cmath>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Renderer::Renderer(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&swapChain,
		&device,
		nullptr,
		&context
	);
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
	device->CreateRenderTargetView(backBuffer.Get(), nullptr, &targetView);

	D3D11_DEPTH_STENCIL_DESC dsDesc{};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;
	device->CreateDepthStencilState(&dsDesc, &depthStencilState);
	context->OMSetDepthStencilState(depthStencilState.Get(), 1U);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil;
	D3D11_TEXTURE2D_DESC depthDesc{};
	depthDesc.Width = static_cast<unsigned int>(rect.right - rect.left);
	depthDesc.Height = static_cast<unsigned int>(rect.bottom - rect.top);
	depthDesc.MipLevels = 1U;
	depthDesc.ArraySize = 1U;
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthDesc.SampleDesc.Count = 1U;
	depthDesc.SampleDesc.Quality = 0U;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	device->CreateTexture2D(&depthDesc, nullptr, &depthStencil);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0U;
	device->CreateDepthStencilView(depthStencil.Get(), &dsvDesc, &depthStencilView);

	context->OMSetRenderTargets(1U, targetView.GetAddressOf(), depthStencilView.Get());

	constantBuffer = std::make_unique<ConstantBuffer>(device.Get(), modelViewProjection);
	constantBuffer->Load(context.Get(), modelViewProjection);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(depthDesc.Width);
	viewport.Height = static_cast<float>(depthDesc.Height);
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	context->RSSetViewports(1U, &viewport);

	SetProjectionMatrix(DirectX::XMMatrixPerspectiveRH(1.0F, viewport.Height / viewport.Width, 0.5F, 100.0F));
}

void Renderer::EndFrame()
{
	const float color[]{ 
		static_cast<float>(backgroundColour.r) / 255.0F,
		static_cast<float>(backgroundColour.g) / 255.0F,
		static_cast<float>(backgroundColour.b) / 255.0F,
		static_cast<float>(backgroundColour.a) / 255.0F };
	swapChain->Present(1u, 0u);
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0F, 0U);
	context->ClearRenderTargetView(targetView.Get(), color); 
}

void Renderer::SetBackground(Colour c)
{
	backgroundColour = c;
}

ID3D11Device* Renderer::GetDevice()
{
	return device.Get();
}

ID3D11DeviceContext* Renderer::GetContext()
{
	return context.Get();
}

void Renderer::SetModelMatrix(const DirectX::XMMATRIX& modelMatrix)
{
	modelViewProjection.model = DirectX::XMMatrixTranspose(modelMatrix);
	constantBuffer->Load(context.Get(), modelViewProjection);
}

void Renderer::SetViewMatrix(const DirectX::XMMATRIX& viewMatrix)
{
	modelViewProjection.view = DirectX::XMMatrixTranspose(viewMatrix);
	constantBuffer->Load(context.Get(), modelViewProjection);
}

void Renderer::SetProjectionMatrix(const DirectX::XMMATRIX& projectionMatrix)
{
	modelViewProjection.projection = DirectX::XMMatrixTranspose(projectionMatrix);
	constantBuffer->Load(context.Get(), modelViewProjection);
}

DirectX::XMMATRIX Renderer::GetViewMatrix()
{
	return DirectX::XMMatrixTranspose(modelViewProjection.view);
}
