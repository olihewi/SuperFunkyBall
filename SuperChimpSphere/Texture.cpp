#include "Texture.h"
#include "GDIManager.h"

std::unordered_map<std::wstring, std::shared_ptr<Texture>> Texture::cache;

Texture::Texture(Renderer& renderer, const std::wstring& path, unsigned int _slot) : slot(_slot)
{
	//Gdiplus::Bitmap bmp(path.c_str());
	auto width = 256U; //bmp.GetWidth();
	auto height = 256U; //bmp.GetHeight();
	pixels = std::make_unique<Colour[]>(width * height);
	//Gdiplus::Color pixel;
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			//bmp.GetPixel(x, y, &pixel);
			pixels[y * width + x] = (x / 32) % 2 == (y / 32) % 2 ? Colours::White : Colours::Black;
			//pixels[y * width + height] = { static_cast<unsigned char>(x), static_cast<unsigned char>(y), static_cast<unsigned char>(0), static_cast<unsigned char>(255) };
			//pixels[y * width + height] = { pixel.GetR(), pixel.GetG(), pixel.GetB(), pixel.GetA() };
		}
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA subresourceData;
	subresourceData.pSysMem = pixels.get();
	subresourceData.SysMemPitch = width * sizeof(Colour);

	renderer.GetDevice()->CreateTexture2D(
		&textureDesc,
		&subresourceData,
		&texture
	);

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	renderer.GetDevice()->CreateShaderResourceView(
		texture.Get(), &shaderResourceViewDesc, &shaderResourceView
	);

	renderer.GetContext()->GenerateMips(shaderResourceView.Get());
}

void Texture::Load(Renderer& renderer)
{
	renderer.GetContext()->PSSetShaderResources(
		slot,
		1U,
		shaderResourceView.GetAddressOf()
	);
}

std::shared_ptr<Texture> Texture::GetOrCreate(Renderer& renderer, const std::wstring& path)
{
	cache.try_emplace(path, std::make_shared<Texture>(renderer, path, cache.size()));
	return cache[path];
}
