#include "Mesh.h"
#include <cmath>
#include "GraphicsComponents.h"
#include "OBJLoader.h"
#include <locale>
#include <codecvt>

Mesh::Mesh(Renderer& renderer, std::vector<Vector3> _vertices, std::vector<unsigned int> _triangles, std::vector<Vector2> _uvs) : vertices(_vertices), triangles(_triangles), uvs(_uvs)
{
    OnMeshUpdated(renderer);
}

Mesh::Mesh(Renderer& renderer, std::string modelPath, std::wstring _texturePath) : texturePath(_texturePath)
{
    objl::Loader loader;
    loader.LoadFile(modelPath);
    for (auto& vertex : loader.LoadedVertices)
    {
        vertices.push_back(vertex.Position);
        uvs.push_back(vertex.TextureCoordinate);
    }
    for (size_t i = 0; i < loader.LoadedIndices.size(); i += 3)
    {
        triangles.push_back(loader.LoadedIndices[i]);
        triangles.push_back(loader.LoadedIndices[i+2]);
        triangles.push_back(loader.LoadedIndices[i+1]);
    }
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
    components.push_back(PixelShader::GetOrCreate(renderer, L"PixelShader.cso"));
    std::vector<Vertex> v;

    size_t j = uvs.size();
    for (size_t i = 0; i < vertices.size(); i++)
    {
        v.push_back(Vertex(vertices[i], i < j ? uvs[i] : Vector2s::zero));
    }

    components.push_back(VertexShader::GetOrCreate(renderer, L"VertexShader.cso", elementDesc));
    components.push_back(std::make_shared<VertexBuffer>(renderer, v));
    components.push_back(std::make_shared<TriangleBuffer>(renderer, triangles));
    components.push_back(Texture::GetOrCreate(renderer, texturePath));
    components.push_back(std::make_shared<Sampler>(renderer));
}

std::unique_ptr<Mesh> Mesh::CreatePrimitiveCube(Renderer& renderer, Vector3 size)
{
    size.x /= 2;
    size.y /= 2;
    size.z /= 2;
    std::vector<Vector3> v{
        { -size.x, -size.y, -size.z },
        { +size.x, -size.y, -size.z },
        { -size.x, +size.y, -size.z },
        { +size.x, +size.y, -size.z },
        { -size.x, -size.y, +size.z },
        { +size.x, -size.y, +size.z },
        { -size.x, +size.y, +size.z },
        { +size.x, +size.y, +size.z }
    };
    std::vector<Vector2> u{
        { 0.0F, 0.0F },
        { 1.0F, 0.0F },
        { 0.0F, 1.0F },
        { 1.0F, 1.0F },
        { 0.0F, 0.0F },
        { 1.0F, 0.0F },
        { 0.0F, 1.0F },
        { 1.0F, 1.0F }
    };
    std::vector<unsigned int> t{
        0,2,1, 2,3,1,
        1,3,5, 3,7,5,
        2,6,3, 3,6,7,
        4,5,7, 4,7,6,
        0,4,2, 2,4,6,
        0,1,4, 1,5,4
    };
    return std::make_unique<Mesh>(renderer,v,t,u);
}

std::unique_ptr<Mesh> Mesh::CreatePrimitiveSphere(Renderer& renderer, float radius, unsigned int resolution)
{
    std::vector<Vector3> v;
    std::vector<unsigned int> t;
    std::vector<Vector2> u;

    v.push_back({ 0.0F, +radius, 0.0F });
    u.push_back({ 0.0F, 0.0F });
    
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
            Vector2 uv
            {
                theta / DirectX::XM_2PI,
                phi / DirectX::XM_PI
            };
            v.push_back(pos);
            u.push_back(uv);
        }
    }

    v.push_back({ 0.0F, -radius, 0.0F });
    u.push_back({ 0.0F, 0.0F });

    // Top
    for (unsigned int i = 1; i <= resolution; i++)
    {
        t.push_back(0);
        t.push_back(i);
        t.push_back(i + 1);
    }
    //  Middle
    unsigned int baseIndex = 1;
    unsigned int ringVertexCount = resolution + 1;
    for (unsigned int i = 0; i < resolution - 2; i++)
    {
        for (unsigned int j = 0; j < resolution; j++)
        {
            t.push_back(baseIndex + i * ringVertexCount + j);
            t.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            t.push_back(baseIndex + i * ringVertexCount + j + 1);

            t.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            t.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
            t.push_back(baseIndex + i * ringVertexCount + j + 1);
        }
    }
    // Bottom
    unsigned int southPoleIndex = static_cast<unsigned int>(v.size()) - 1;
    baseIndex = southPoleIndex - ringVertexCount;
    for (unsigned int i = 0; i < resolution; i++)
    {
        t.push_back(southPoleIndex);
        t.push_back(baseIndex + i + 1);
        t.push_back(baseIndex + i);
    }


    return std::make_unique<Mesh>(renderer,v,t,u);
}
