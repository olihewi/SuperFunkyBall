#include "TriangleBuffer.h"

TriangleBuffer::TriangleBuffer(Renderer& renderer, const std::vector<unsigned short>& triangles)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // What to set the buffer up as
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; // What the buffer will be used for
	bufferDesc.CPUAccessFlags = 0U; // Whether the CPU needs to access the buffer (it doesn't yet)
	bufferDesc.MiscFlags = 0u; // 
	bufferDesc.ByteWidth = static_cast<unsigned int>(triangles.size() * sizeof(unsigned short)); // Size of the buffer in bytes
	bufferDesc.StructureByteStride = sizeof(unsigned short); // Size of each index
	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = triangles.data(); // Triangles to use
	renderer.GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &buffer);
}

void TriangleBuffer::Load(Renderer& renderer)
{
	renderer.GetContext()->IASetIndexBuffer(
		buffer.Get(), // Index (Triangle) Buffer
		DXGI_FORMAT_R16_UINT, // Format of the triangle data type (unsigned short)
		0U // Offset of the first triangle to use
	);
}
