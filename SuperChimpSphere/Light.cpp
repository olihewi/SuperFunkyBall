#include "Light.h"

Light::Light(Renderer& renderer, Vector3 _direction, DirectX::XMFLOAT4 _ambient, DirectX::XMFLOAT4 _diffuse)
{
	bufferData = { _direction, 0.0F, _ambient, _diffuse };

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // The type of buffer we want
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC; // We want a dynamic buffer because it'll be updated every frame
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // We need to update it from the CPU
	bufferDesc.MiscFlags = 0u; // 
	bufferDesc.ByteWidth = sizeof(bufferData); // Byte size of the data
	bufferDesc.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = &bufferData;
	auto hr = renderer.GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &constantBuffer);
}

void Light::Update(GameTime& time)
{
	bufferData.gameTime = time.Time();
}

void Light::Render(Renderer& renderer)
{
	//D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	/*renderer.GetContext()->Map(
		constantBuffer.Get(), // Resource
		0U, // Subresource
		D3D11_MAP_WRITE_DISCARD, // How we want to map it
		0U, // Map flags
		&mappedSubresource // Mapped Subresource
	);
	memcpy(mappedSubresource.pData, &buffer, sizeof(buffer));
	renderer.GetContext()->Unmap(constantBuffer.Get(), 0U);*/
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	renderer.GetContext()->Map(
		constantBuffer.Get(), // Resource
		0U, // Subresource
		D3D11_MAP_WRITE_DISCARD, // How we want to map it
		0U, // Map flags
		&mappedSubresource // Mapped Subresource
	);
	memcpy(mappedSubresource.pData, &bufferData, sizeof(bufferData));
	renderer.GetContext()->Unmap(constantBuffer.Get(), 0U);

	renderer.GetContext()->PSSetConstantBuffers(
		1U, // Start Slot
		1U, // Number of buffers
		constantBuffer.GetAddressOf() // Constant Buffer
	);
}
