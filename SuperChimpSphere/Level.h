#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Camera.h"
#include "Goal.h"
#include "Collectible.h"
class Level : public GameObject
{
public:
	Level(Renderer& renderer, const std::string& levelFile);
	void Update(Input& input, GameTime& time) override;
	void Render(Renderer& renderer) override;
private:
	std::unique_ptr<Player> player;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Goal> goal;
	std::vector<std::unique_ptr<Collectible>> collectibles;
	int collectiblesCollected = 0;
	Vector3 spawnPoint;
};

