#pragma once
#include "GameObject.h"
#include "Player.h"
class Camera : public GameObject
{
public:
	Camera(Renderer& renderer, Player* _player);
	void Update(Input& input, GameTime& time) override;
	void Render(Renderer& renderer) override;
private:
	Player* player;
};

