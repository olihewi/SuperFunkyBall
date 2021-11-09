#include "Collectible.h"
#include "Mesh.h"

Collectible::Collectible(Renderer& renderer, int _value, Vector3 position) : value(_value)
{
	AddComponent(Mesh::CreatePrimitiveSphere(renderer, 0.25F, 4U));
	transform.position = position;
}

void Collectible::Update(Input& input, GameTime& time)
{
	if (!collected)
	{
		float rotation = time.Delta();
		if (collectionTimer >= 0.0F)
		{
			rotation *= -3.0F;
			transform.scale = Vector3s::one * (0.25F - collectionTimer);
			transform.position.y += 6.0F * time.Delta();
			if (collectionTimer >= 0.25F)
			{
				collected = true;
			}
			collectionTimer += time.Delta();
		}
		transform.rotation *= DirectX::XMMatrixRotationY(rotation);
	}
}

void Collectible::Render(Renderer& renderer)
{
	if (!collected)
	{
		GameObject::Render(renderer);
	}
}
