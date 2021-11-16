#include "UIImage.h"
#include "GraphicsComponents.h"

UIImage::UIImage(Renderer& renderer, std::string imagePath, Vector2 _dimensions, Vector2 _position) : position(_position), dimensions(_dimensions)
{
    components.push_back(PixelShader::GetOrCreate(renderer, L"PSTexturedFlat.cso"));
    
    std::vector<unsigned int> t = {
        0,1,2, 2,1,3
    };

    components.push_back(VertexShader::GetOrCreate(renderer, L"VS2D.cso", elementDesc));
    components.push_back(std::make_shared<TriangleBuffer>(renderer, t));
    components.push_back(Texture::GetOrCreate(renderer, imagePath));
    components.push_back(std::make_shared<Sampler>(renderer));
}

void UIImage::Render(Renderer& renderer)
{
    Vector2 dims = Vector2(dimensions.x * renderer.GetDimensions().y / renderer.GetDimensions().x, dimensions.y);
    std::vector<Vertex> v = {
        {{position.x,position.y,0.0F}, {uvUL.x,uvBR.y}, {0.0F,0.0F,0.0F}},
        {{position.x,position.y + dims.y,0.0F}, {uvUL.x,uvUL.y}, {0.0F,0.0F,0.0F}},
        {{position.x + dims.x,position.y,0.0F}, {uvBR.x,uvBR.y}, {0.0F,0.0F,0.0F}},
        {{position.x + dims.x,position.y + dims.y,0.0F}, {uvBR.x,uvUL.y}, {0.0F,0.0F,0.0F}},
    };
    auto vBuf = VertexBuffer(renderer, v);
    vBuf.Load(renderer);
    for (auto& component : components)
    {
        component->Load(renderer);
    }
    renderer.GetContext()->DrawIndexed(6U, 0U, 0U);
}
