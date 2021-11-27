#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Camera.h"
#include "Goal.h"
#include "Collectible.h"
#include "Light.h"
#include "UIText.h"
class Level : public GameObject
{
public:
	Level(Renderer& renderer, const std::string& levelFile);
	void Update(Input& input, GameTime& time) override;
	void Render(Renderer& renderer) override;
private:
	std::unique_ptr<Player> player;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Light> light;
	std::vector<std::unique_ptr<Goal>> goals;
	std::vector<std::unique_ptr<Collectible>> collectibles;

	std::vector<std::unique_ptr<UIText>> uiText;
	int collectiblesCollected = 0;
	float levelTime = 60.0F;
	float timer = 0.0F;
	float killY = -6.0F;
	Vector3 spawnPoint;
public:
	bool finished = false;
	std::string nextLevel;
};

