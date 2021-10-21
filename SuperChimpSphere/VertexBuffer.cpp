#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Renderer& renderer, const std::vector<Vector3>& vertices) : stride(sizeof(Vector3))
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // What to set the buffer up as
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; // What the buffer will be used for
	bufferDesc.CPUAccessFlags = 0U; // Whether the CPU needs to access the buffer (it doesn't yet)
	bufferDesc.MiscFlags = 0U; // 
	bufferDesc.ByteWidth = UINT(sizeof(Vector3) * vertices.size()); // Size of the buffer in bytes
	bufferDesc.StructureByteStride = sizeof(Vector3); // Size of each vertex in bytes
	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = vertices.data(); // Vertices to use
	renderer.GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &buffer);
}

void VertexBuffer::Load(Renderer& renderer)
{
	const unsigned int offset = 0U;
	renderer.GetContext()->IASetVertexBuffers(
		0U, // Start Slot
		1U, // Number of Buffers to set
		buffer.GetAddressOf(), // Vertex Buffer address
		&stride, // Size in bytes of each vertex
		&offset // Number of bytes between first element of buffer and first element to be used.
	);
}
