#include "Level.h"
#include "Mesh.h"
#include "MeshCollider.h"
#include "Json.h"
#include <fstream>
#include "CollisionManager.h"
#include <sstream>
#include "Sound.h"

Level::Level(Renderer& renderer, const std::string& levelFile)
{
	nextLevel = levelFile;
	light = std::make_unique<Light>(renderer, Vector3{ 0.25F,1.0F,0.25F }.Normalized(), DirectX::XMFLOAT4(0.33F,0.35F,0.4F,1.0F), DirectX::XMFLOAT4(1.0F,1.0F,0.86F,1.0F));
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
		killY = j["killY"].get<float>();
		levelTime = j["timeLimit"].get<float>();
		// Collectibles
		auto cols = j["collectibles"];
		for (auto i : cols)
		{
			collectibles.push_back(std::make_unique<Collectible>(renderer, 1, Vector3(i[0], i[1], i[2])));
		}
		uiText.push_back(std::make_unique<UIText>(renderer, "Paper: 0/" + std::to_string(collectibles.size()), Vector2(-0.95F, 0.75F)));
		uiText.push_back(std::make_unique<UIText>(renderer, "", Vector2(-0.125F,0.75F)));
		uiText.push_back(std::make_unique<UIText>(renderer, "", Vector2(-0.95F, -0.9F)));
		uiText.push_back(std::make_unique<UIText>(renderer, "Time", Vector2(-0.1F, 0.85F)));
		uiText.push_back(std::make_unique<UIText>(renderer, j["name"].get<std::string>(), Vector2(-0.95F, 0.85F)));
		file.open("Levels/highScores.json");
		if (file.is_open())
		{
			j.clear();
			file >> j;
			file.close();
			uiText.push_back(std::make_unique<UIText>(renderer, "High Scores", Vector2(0.4F, 0.85F)));
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << j[levelFile]["time"].get<float>();
			uiText.push_back(std::make_unique<UIText>(renderer, "Time: " + ss.str(), Vector2(0.4F, 0.75F)));
			uiText.push_back(std::make_unique<UIText>(renderer, "Paper: " + std::to_string(j[levelFile]["paper"].get<int>()), Vector2(0.4F, 0.65F)));
		}
	}
}

void Level::Update(Input& input, GameTime& time)
{
	light->Update(time);
	player->Update(input, time);
	camera->Update(input, time);
	if (player->transform.position.y <= killY)
	{
		player->transform.position = spawnPoint;
	}
	// Check for Victory
	for (auto& goal : goals)
	{
		if (CollisionManager::SphereVsPoint(player->transform.position, 0.5F, goal->transform.position))
		{
			std::fstream file;
			file.open("Levels/highScores.json", std::ios::in);
			if (file.is_open())
			{
				nlohmann::json j;
				file >> j;
				if (j[nextLevel]["paper"].get<int>() < collectiblesCollected)
				{
					j[nextLevel]["paper"] = collectiblesCollected;
				}
				if (j[nextLevel]["time"].get<float>() > timer)
				{
					j[nextLevel]["time"] = timer;
				}
				file.close();
				file.open("Levels/highScores.json", std::ios::out | std::ios::trunc);
				file << j.dump(2);
				file.close();
			}
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
			uiText[0]->text = "Paper: " + std::to_string(collectiblesCollected) + "/" + std::to_string(collectibles.size());
		}
		collectible->Update(input, time);
	}
	timer += time.Delta();
	if (timer >= levelTime)
	{
		finished = true;
	}
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << levelTime - timer;
	uiText[1]->text = stream.str();
	stream = {};
	stream << std::fixed << std::setprecision(0) << (player->physics->velocity + Vector3s::up * time.Delta() * player->physics->gravityMultiplier).Magnitude() * 4.0F << "mph";
	uiText[2]->text = stream.str();
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
	for (auto& ui : uiText)
	{
		ui->Render(renderer);
	}
	GameObject::Render(renderer);
}
