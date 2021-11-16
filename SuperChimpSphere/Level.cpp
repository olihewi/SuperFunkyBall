#include "Level.h"
#include "Mesh.h"
#include "MeshCollider.h"
#include "Json.h"
#include <fstream>
#include "CollisionManager.h"

Level::Level(Renderer& renderer, const std::string& levelFile)
{
	light = std::make_unique<Light>(renderer, Vector3{ 0.25F,1.0F,0.25F }.Normalized(), DirectX::XMFLOAT4(0.5F,0.5F,0.5F,1.0F), DirectX::XMFLOAT4(1.0F,1.0F,1.0F,1.0F));
	playerScore = std::make_unique<UIText>(renderer, "Hello World!");
	std::ifstream file;
	file.open(levelFile);
	if (file.is_open())
	{
		nlohmann::json j;
		file >> j;
		file.close();
		// Player
		player = std::make_unique<Player>( renderer );
		auto spawn = j["spawn"];
		spawnPoint = Vector3(spawn[0].get<float>(), spawn[1].get<float>(), spawn[2].get<float>());
		player->transform.position = spawnPoint;
		// Camera
		camera = std::make_unique<Camera>( renderer, player.get() );
		// Level
		std::string meshPath = j["mesh"].get<std::string>();
		Mesh* mesh = dynamic_cast<Mesh*>(AddComponent(std::make_unique<Mesh>(renderer, meshPath, "Textures/StagePalette.png")));
		AddComponent(std::make_unique<MeshCollider>(transform, mesh));
		// Goals
		for (auto& jgoal : j["goals"])
		{
			auto goalPos = jgoal["position"];
			goals.push_back(std::make_unique<Goal>(renderer, Vector3(goalPos[0][0], goalPos[0][1], goalPos[0][2]), Vector3(goalPos[1][0], goalPos[1][1], goalPos[1][2]), "Levels/" + jgoal["nextLevel"].get<std::string>() + ".json"));
		}
		// Collectibles
		auto cols = j["collectibles"];
		for (auto i : cols)
		{
			collectibles.push_back(std::make_unique<Collectible>(renderer, 1, Vector3(i[0], i[1], i[2])));
		}
	}
}

void Level::Update(Input& input, GameTime& time)
{
	player->Update(input, time);
	camera->Update(input, time);
	if (player->transform.position.y <= -6.0F)
	{
		player->transform.position = spawnPoint;
	}
	// Check for Victory
	for (auto& goal : goals)
	{
		if (CollisionManager::SphereVsPoint(player->transform.position, 0.5F, goal->transform.position))
		{
			nextLevel = goal->nextLevel;
			finished = true;
		}
	}
	// Pickup collectibles
	for (auto& collectible : collectibles)
	{
		if (collectible->collectionTimer < 0.0F && CollisionManager::SphereVsSphere(player->transform.position, 0.5F, collectible->transform.position, 0.25F))
		{
			collectible->collectionTimer = 0.0F;
			collectiblesCollected += collectible->value;
			playerScore->text = std::to_string(collectiblesCollected) + "/" + std::to_string(collectibles.size());
		}
		collectible->Update(input, time);
	}
	GameObject::Update(input, time);
}

void Level::Render(Renderer& renderer)
{
	light->Render(renderer);
	player->Render(renderer);
	camera->Render(renderer);
	for (auto& goal : goals)
	{
		goal->Render(renderer);
	}
	for (auto& collectible : collectibles)
	{
		collectible->Render(renderer);
	}
	playerScore->Render(renderer);
	GameObject::Render(renderer);
}
