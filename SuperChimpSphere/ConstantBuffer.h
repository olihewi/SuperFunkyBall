#pragma once
#include <DirectXMath.h>
struct ConstantBuffer
{
public:
	DirectX::XMFLOAT4X4 model;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};