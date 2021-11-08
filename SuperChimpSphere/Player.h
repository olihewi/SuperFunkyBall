#pragma once
#include "GameObject.h"
#include "SphereCollider.h"
class Player : public GameObject
{
	friend class Camera;
public:
	Player(Renderer& renderer);
	void Update(Input& input, GameTime& time) override;
	void Render(Renderer& renderer) override;
private:
	Physics* physics;
	SphereCollider* collider;
	
	Vector2 acceleration;
};

