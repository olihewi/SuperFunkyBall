#include "Level.h"
#include "Mesh.h"
#include "MeshCollider.h"
#include "Json.h"
#include <fstream>
#include "CollisionManager.h"

Level::Level(Renderer& renderer, const std::string& levelFile)
{
	std::ifstream file;
	file.open(levelFile);
	if (file.is_open())
	{
		nlohmann::json j;
		file >> j;
		// Player
		player = std::make_unique<Player>( renderer );
		auto spawn = j["spawn"];
		spawnPoint = Vector3(spawn[0].get<float>(), spawn[1].get<float>(), spawn[2].get<float>());
		player->transform.position = spawnPoint;
		// Camera
		camera = std::make_unique<Camera>( renderer, player.get() );
		// Level
		std::string meshPath = j["mesh"].get<std::string>();
		Mesh* mesh = dynamic_cast<Mesh*>(AddComponent(std::make_unique<Mesh>(renderer, meshPath, L"Textures/UV_Checker.png")));
		AddComponent(std::make_unique<MeshCollider>(transform, mesh));
		// Goal
		auto goalPos = j["goal"];
		goal = std::make_unique<Goal>(renderer, Vector3(goalPos[0][0], goalPos[0][1], goalPos[0][2]), Vector3(goalPos[1][0], goalPos[1][1], goalPos[1][2]));
		file.close();
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
	if (CollisionManager::SphereVsPlane(player->transform.position, 0.5F, goal->transform.position, Vector3(0.0F, 0.0F, 1.0F)) &&
		CollisionManager::SphereVsSphere(player->transform.position, 0.25F, goal->transform.position, 0.5F))
	{
		player->transform.position.y += 10.0F;
	}
	// Pickup collectibles
	for (auto& collectible : collectibles)
	{
		if (collectible->collectionTimer < 0.0F && CollisionManager::SphereVsSphere(player->transform.position, 0.5F, collectible->transform.position, 0.25F))
		{
			collectible->collectionTimer = 0.0F;
			collectiblesCollected += collectible->value;
		}
		collectible->Update(input, time);
	}
	GameObject::Update(input, time);
}

void Level::Render(Renderer& renderer)
{
	player->Render(renderer);
	camera->Render(renderer);
	goal->Render(renderer);
	for (auto& collectible : collectibles)
	{
		collectible->Render(renderer);
	}
	GameObject::Render(renderer);
}
