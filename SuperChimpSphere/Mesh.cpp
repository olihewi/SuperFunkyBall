#include "Mesh.h"
#include <cmath>
#include <d3dcompiler.h>

#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d3d11.lib")

Microsoft::WRL::ComPtr<ID3D11InputLayout> Mesh::inputLayout;
Microsoft::WRL::ComPtr<ID3D11VertexShader> Mesh::vertexShader;
Microsoft::WRL::ComPtr<ID3D11PixelShader> Mesh::pixelShader;

Mesh::Mesh(Renderer& renderer, std::vector<Vector3> _vertices, std::vector<unsigned int> _triangles) : vertices(_vertices), triangles(_triangles)
{
    OnMeshUpdated(renderer);
}

void Mesh::Register(Renderer& renderer)
{
    auto* device = renderer.GetDevice();
    Microsoft::WRL::ComPtr<ID3DBlob> blob;
    // Pixel Shader
    D3DReadFileToBlob(L"PixelShader.cso", &blob);
    device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
    // Vertex Shader
    D3DReadFileToBlob(L"VertexShader.cso", &blob);
    device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);

    const D3D11_INPUT_ELEMENT_DESC elementDesc[]
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    renderer.GetDevice()->CreateInputLayout(
        elementDesc,
        static_cast<UINT>(std::size(elementDesc)),
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        &inputLayout
    );
}

void Mesh::Render(Renderer& renderer)
{
    auto* context = renderer.GetContext();

    const UINT stride = sizeof(Vector3);
    const UINT offset = 0U;
    context->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(triangleBuffer.Get(), DXGI_FORMAT_R16_UINT, 0U);

    context->PSSetShader(pixelShader.Get(), nullptr, 0U);
    context->VSSetShader(vertexShader.Get(), nullptr, 0U);

    context->IASetInputLayout(inputLayout.Get());

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    context->DrawIndexed(static_cast<UINT>(std::size(triangles)), 0U, 0U);
}

void Mesh::OnMeshUpdated(Renderer& renderer)
{
    auto* device = renderer.GetDevice();
    // Vertex Buffer
    D3D11_BUFFER_DESC vertexBufferDesc{};
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.ByteWidth = sizeof(vertices);
    vertexBufferDesc.StructureByteStride = sizeof(Vector3);
    D3D11_SUBRESOURCE_DATA vertexSubresourceData{};
    vertexSubresourceData.pSysMem = &vertices;
    device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
    // Triangle Buffer
    D3D11_BUFFER_DESC triangleBufferDesc{};
    triangleBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    triangleBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    triangleBufferDesc.CPUAccessFlags = 0;
    triangleBufferDesc.MiscFlags = 0;
    triangleBufferDesc.ByteWidth = sizeof(triangles);
    triangleBufferDesc.StructureByteStride = sizeof(unsigned short);
    D3D11_SUBRESOURCE_DATA triangleSubresourceData{};
    triangleSubresourceData.pSysMem = &triangles;
    device->CreateBuffer(&triangleBufferDesc, &triangleSubresourceData, &triangleBuffer);
}

Mesh Mesh::CreatePrimitiveCube(Renderer& renderer, Vector3 size)
{
    size.x /= 2;
    size.y /= 2;
    size.z /= 2;
    std::vector<Vector3> v{
        {-size.x, -size.y, -size.z},
        {+size.x, -size.y, -size.z},
        {-size.x, +size.y, -size.z},
        {+size.x, +size.y, -size.z},
        {-size.x, -size.y, +size.z},
        {+size.x, -size.y, +size.z},
        {-size.x, +size.y, +size.z},
        {+size.x, +size.y, +size.z}
    };
    std::vector<unsigned int> t{
        0,2,1, 2,3,1,
        1,3,5, 3,7,5,
        2,6,3, 3,6,7,
        4,5,7, 4,7,6,
        0,4,2, 2,4,6,
        0,1,4, 1,5,4
    };
    return Mesh(renderer,v,t);
}

Mesh Mesh::CreatePrimitiveSphere(Renderer& renderer, float radius, unsigned int resolution)
{
    std::vector<Vector3> v;
    std::vector<unsigned int> t;

    v.push_back({ 0.0F, +radius, 0.0F });
    
    float phiStep = DirectX::XM_PI / resolution;
    float thetaStep = phiStep * 2.0F;

    for (unsigned int i = 1; i <= resolution - 1; i++)
    {
        float phi = i * phiStep;
        for (unsigned int j = 0; j <= resolution; j++)
        {
            float theta = j * thetaStep;
            Vector3 pos
            {
                radius * std::sinf(phi) * std::cosf(theta),
                radius * std::cosf(phi),
                radius * std::sinf(phi) * std::sinf(theta)
            };
            v.push_back(pos);
        }
    }

    v.push_back({ 0.0F, -radius, 0.0F });

    // Top
    for (unsigned int i = 1; i <= resolution; i++)
    {
        t.push_back(0);
        t.push_back(i + 1);
        t.push_back(i);
    }
    //  Middle
    unsigned int baseIndex = 1;
    unsigned int ringVertexCount = resolution + 1;
    for (unsigned int i = 0; i < resolution - 2; i++)
    {
        for (unsigned int j = 0; j < resolution; j++)
        {
            t.push_back(baseIndex + i * ringVertexCount + j);
            t.push_back(baseIndex + i * ringVertexCount + j + 1);
            t.push_back(baseIndex + (i + 1) * ringVertexCount + j);

            t.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            t.push_back(baseIndex + i * ringVertexCount + j + 1);
            t.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
        }
    }
    // Bottom
    unsigned int southPoleIndex = v.size() - 1;
    baseIndex = southPoleIndex - ringVertexCount;
    for (unsigned int i = 0; i < resolution; i++)
    {
        t.push_back(southPoleIndex);
        t.push_back(baseIndex + i);
        t.push_back(baseIndex + i + 1);
    }


    return Mesh(renderer,v,t);
}
