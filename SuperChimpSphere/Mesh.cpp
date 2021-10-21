#include "Mesh.h"
#include <cmath>
#include "GraphicsComponents.h"

Microsoft::WRL::ComPtr<ID3D11VertexShader> Mesh::vertexShader;
Microsoft::WRL::ComPtr<ID3D11PixelShader> Mesh::pixelShader;

Mesh::Mesh(Renderer& renderer, std::vector<Vector3> _vertices, std::vector<unsigned short> _triangles) : vertices(_vertices), triangles(_triangles)
{
    OnMeshUpdated(renderer);
}

void Mesh::Render(Renderer& renderer)
{
    for (auto& component : components)
    {
        component->Load(renderer);
    }

    renderer.GetContext()->DrawIndexed(static_cast<UINT>(std::size(triangles)), 0U, 0U);
}

void Mesh::OnMeshUpdated(Renderer& renderer)
{
    components.clear();
    components.push_back(std::make_unique<PixelShader>(renderer, L"PixelShader.cso"));
    auto vertexShader = std::make_unique<VertexShader>(renderer, L"VertexShader.cso");
    const std::vector<D3D11_INPUT_ELEMENT_DESC> elementDesc
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    components.push_back(std::make_unique<InputLayout>(renderer, elementDesc, vertexShader->GetBytecode()));
    components.push_back(std::move(vertexShader));
    components.push_back(std::make_unique<VertexBuffer>(renderer, vertices));
    components.push_back(std::make_unique<TriangleBuffer>(renderer, triangles));
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
    std::vector<unsigned short> t{
        0,2,1, 2,3,1,
        1,3,5, 3,7,5,
        2,6,3, 3,6,7,
        4,5,7, 4,7,6,
        0,4,2, 2,4,6,
        0,1,4, 1,5,4
    };
    return Mesh(renderer,v,t);
}

Mesh Mesh::CreatePrimitiveSphere(Renderer& renderer, float radius, unsigned short resolution)
{
    std::vector<Vector3> v;
    std::vector<unsigned short> t;

    v.push_back({ 0.0F, +radius, 0.0F });
    
    float phiStep = DirectX::XM_PI / resolution;
    float thetaStep = phiStep * 2.0F;

    for (unsigned short i = 1; i <= resolution - 1; i++)
    {
        float phi = i * phiStep;
        for (unsigned short j = 0; j <= resolution; j++)
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
    unsigned short baseIndex = 1;
    unsigned short ringVertexCount = resolution + 1;
    for (unsigned short i = 0; i < resolution - 2; i++)
    {
        for (unsigned short j = 0; j < resolution; j++)
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
    unsigned short southPoleIndex = v.size() - 1;
    baseIndex = southPoleIndex - ringVertexCount;
    for (unsigned short i = 0; i < resolution; i++)
    {
        t.push_back(southPoleIndex);
        t.push_back(baseIndex + i);
        t.push_back(baseIndex + i + 1);
    }


    return Mesh(renderer,v,t);
}
