#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
class ConstantBuffer
{
public:
	struct ConstantBufferData
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	ConstantBuffer(ID3D11Device* device, const ConstantBufferData& bufferData);
	void Load(ID3D11DeviceContext* context, const ConstantBufferData& bufferData);
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
};

