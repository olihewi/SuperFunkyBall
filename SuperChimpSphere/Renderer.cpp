#include "Renderer.h"
#include <d3dcompiler.h>
#include <array>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Renderer::Renderer(HWND hWnd)
{
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
		&deviceContext
	);
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
	device->CreateRenderTargetView(backBuffer.Get(), nullptr, &targetView);
}

void Renderer::EndFrame()
{
	const float color[]{ backgroundColour.r,backgroundColour.g,backgroundColour.b,backgroundColour.a };
	deviceContext->ClearRenderTargetView(targetView.Get(), color);
	RenderTestTriangle();
	swapChain->Present(1u, 0u);
}

void Renderer::SetBackground(Colour c)
{
	backgroundColour = c;
}

void Renderer::RenderTestTriangle()
{
	struct Vertex
	{
		float x, y;
	};
	const Vertex vertices[]
	{
		{0.0F, 0.5F},
		{0.5F,-0.5F},
		{-0.5F,-0.5F},
	};

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA subresourceData{};
	subresourceData.pSysMem = vertices;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	device->CreateBuffer(&bufferDesc, &subresourceData, &vertexBuffer);

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	deviceContext->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);

	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	// Pixel Shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	D3DReadFileToBlob(L"PixelShader.cso", &blob);
	device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
	deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0U);
	// Vertex Shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &blob);
	device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);
	deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0U);

	deviceContext->OMSetRenderTargets(1U, targetView.GetAddressOf(), nullptr);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	const D3D11_INPUT_ELEMENT_DESC elementDesc[]
	{
		{"Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	device->CreateInputLayout(elementDesc, static_cast<UINT>(std::size(elementDesc)), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);
	deviceContext->IASetInputLayout(inputLayout.Get());

	D3D11_VIEWPORT viewport;
	viewport.Width = 1080;
	viewport.Height = 720;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	deviceContext->RSSetViewports(1U, &viewport);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->Draw(static_cast<UINT>(std::size(vertices)), 0);
}
