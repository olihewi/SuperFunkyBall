#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(ID3D11Device* device, const ConstantBufferData& bufferData, unsigned int _slot) : slot(_slot)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // The type of buffer we want
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC; // We want a dynamic buffer because it'll be updated every frame
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // We need to update it from the CPU
	bufferDesc.MiscFlags = 0u; // 
	bufferDesc.ByteWidth = sizeof(bufferData); // Byte size of the data
	bufferDesc.StructureByteStride = 0u; // 

	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = &bufferData;
	device->CreateBuffer(&bufferDesc, &subresourceData, &constantBuffer);
}

void ConstantBuffer::Load(ID3D11DeviceContext* context, const ConstantBufferData& bufferData)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	context->Map(
		constantBuffer.Get(), // Resource
		0U, // Subresource
		D3D11_MAP_WRITE_DISCARD, // How we want to map it
		0U, // Map flags
		&mappedSubresource // Mapped Subresource
	);
	memcpy(mappedSubresource.pData, &bufferData, sizeof(bufferData));
	context->Unmap(constantBuffer.Get(), 0U);

	context->VSSetConstantBuffers(
		slot, // Start Slot
		1U, // Number of buffers
		constantBuffer.GetAddressOf() // Constant Buffer
	);
}
