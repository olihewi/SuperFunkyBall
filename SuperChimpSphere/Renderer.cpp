#include "Renderer.h"
#include <d3dcompiler.h>
#include <array>
#include <cmath>
#include <DirectXMath.h>

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
	depthDesc.Width = 1080;
	depthDesc.Height = 720;
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

	
	cb.model = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	cb.view = {
		-1.00000000f, 0.00000000f,  0.00000000f,  0.00000000f,
		0.00000000f, 0.89442718f,  0.44721359f,  0.00000000f,
		0.00000000f, 0.44721359f, -0.89442718f, -2.23606800f,
		0.00000000f, 0.00000000f,  0.00000000f,  1.00000000f
	};
	float xScale = 1.42814801f;
	float yScale = 1.42814801f;
	if (depthDesc.Width > depthDesc.Height)
	{
		xScale = yScale *
			static_cast<float>(depthDesc.Height) /
			static_cast<float>(depthDesc.Width);
	}
	else
	{
		yScale = xScale *
			static_cast<float>(depthDesc.Width) /
			static_cast<float>(depthDesc.Height);
	}
	cb.projection = DirectX::XMFLOAT4X4(
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, -0.01f,
		0.0f, 0.0f, -1.0f, 0.0f
	);
	D3D11_BUFFER_DESC constantBufferDesc
	{
		sizeof(cb),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_CONSTANT_BUFFER,
		0U,
		0U,
		0U
	}; 
	D3D11_SUBRESOURCE_DATA constantBufferSubresourceData{};
	constantBufferSubresourceData.pSysMem = &cb;
	device->CreateBuffer(
		&constantBufferDesc,
		&constantBufferSubresourceData,
		&constantBuffer
	);
	context->VSSetConstantBuffers(
		0U,
		1U,
		constantBuffer.GetAddressOf()
	);
}

void Renderer::EndFrame()
{
	const float color[]{ backgroundColour.r,backgroundColour.g,backgroundColour.b,backgroundColour.a };
	swapChain->Present(1u, 0u);
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0F, 0U);
	context->ClearRenderTargetView(targetView.Get(), color); 
	D3D11_VIEWPORT viewport;
	viewport.Width = 1080;
	viewport.Height = 720;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	context->RSSetViewports(1U, &viewport);
}

void Renderer::SetBackground(Colour c)
{
	backgroundColour = c;
}

void Renderer::RenderTestTriangle(float angle)
{
	struct Vertex
	{
		float x, y, z;
	};
	const Vertex vertices[]
	{
		{ -1.0f,-1.0f,-1.0f},
		{ 1.0f,-1.0f,-1.0f},
		{ -1.0f,1.0f,-1.0f},
		{ 1.0f,1.0f,-1.0f},
		{ -1.0f,-1.0f,1.0f},
		{ 1.0f,-1.0f,1.0f},
		{ -1.0f,1.0f,1.0f},
		{ 1.0f,1.0f,1.0f},
	};
	const unsigned short triangles[]
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	D3D11_BUFFER_DESC vertexBufferDesc{};
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.ByteWidth = sizeof(vertices);
	vertexBufferDesc.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA vertexSubresourceData{};
	vertexSubresourceData.pSysMem = vertices;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	context->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);

	D3D11_BUFFER_DESC triangleBufferDesc{};
	triangleBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	triangleBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	triangleBufferDesc.CPUAccessFlags = 0;
	triangleBufferDesc.MiscFlags = 0;
	triangleBufferDesc.ByteWidth = sizeof(triangles);
	triangleBufferDesc.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA triangleSubresourceData{};
	triangleSubresourceData.pSysMem = triangles;
	Microsoft::WRL::ComPtr<ID3D11Buffer> triangleBuffer;
	device->CreateBuffer(&triangleBufferDesc, &triangleSubresourceData, &triangleBuffer);

	context->IASetIndexBuffer(triangleBuffer.Get(), DXGI_FORMAT_R16_UINT, 0U);

	// Constant Buffer
	struct ConstantBuffer
	{
		DirectX::XMMATRIX transformation;
	};
	const ConstantBuffer cb =
	{
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixRotationZ(angle) *
				DirectX::XMMatrixRotationX(angle)*
				DirectX::XMMatrixTranslation(0.0F, 0.0F, 4.0F) *
				DirectX::XMMatrixPerspectiveLH(1.0F,720.0F / 1080.0F,0.5F,10.0F)
			)
		}
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0U;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0U;
	D3D11_SUBRESOURCE_DATA csd{};
	csd.pSysMem = &cb;
	device->CreateBuffer(&cbd, &csd, &constantBuffer);
	context->VSSetConstantBuffers(0U, 1U, constantBuffer.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	// Pixel Shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	D3DReadFileToBlob(L"PixelShader.cso", &blob);
	device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
	context->PSSetShader(pixelShader.Get(), nullptr, 0U);
	// Vertex Shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &blob);
	device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);
	context->VSSetShader(vertexShader.Get(), nullptr, 0U);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	const D3D11_INPUT_ELEMENT_DESC elementDesc[]
	{
		{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"Colour",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12U,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	device->CreateInputLayout(elementDesc, static_cast<UINT>(std::size(elementDesc)), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);
	context->IASetInputLayout(inputLayout.Get());

	D3D11_VIEWPORT viewport;
	viewport.Width = 1080;
	viewport.Height = 720;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	context->RSSetViewports(1U, &viewport);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->DrawIndexed(static_cast<UINT>(std::size(triangles)), 0U, 0U);
}

ID3D11Device* Renderer::GetDevice()
{
	return device.Get();
}

ID3D11DeviceContext* Renderer::GetContext()
{
	return context.Get();
}
