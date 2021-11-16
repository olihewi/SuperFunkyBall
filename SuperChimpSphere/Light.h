#pragma once
#include "GameComponent.h"
#include "Vector3.h"
#include "Colour.h"
class Light : public GameComponent
{
public:
	Light(Renderer& renderer, Vector3 _direction, DirectX::XMFLOAT4 _ambient, DirectX::XMFLOAT4 _diffuse);
	void Render(Renderer& renderer) override;
private:
	struct LightBufferData
	{
		Vector3 direction;
		float WORTHLESS; // constant buffer data has to be multiples of 16...
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 diffuse;
	};
	LightBufferData bufferData;
	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
};

