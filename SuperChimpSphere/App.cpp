#include "App.h"
#include "Model.h"
#include "Camera.h"
#include "Player.h"
#include "Level.h"
#include "CollisionManager.h"
#include <fstream>
#include "Json.h"

App::App(const GameSettings& _settings) : settings(_settings), window(static_cast<int>(settings.video.resolution.x),static_cast<int>(settings.video.resolution.y),"ASGE"), input(window)
{
	//auto mesh = std::make_unique<Mesh>(Mesh::CreatePrimitiveSphere(window.GetRenderer(), 1.0F, 20U));
	//gameObjects.push_back(std::make_unique<GameObject>(std::move(mesh)));
	//mesh = std::make_unique<Mesh>(Mesh::CreatePrimitiveCube(window.GetRenderer(), Vector3{ 1.0F,1.0F,1.0F }));
	/*gameObjects.push_back(std::make_unique<GameObject>(
		std::vector<std::unique_ptr<GameComponent>>{
			std::make_unique<Mesh>(Mesh::CreatePrimitiveSphere(window.GetRenderer(), 1.0F, 20U))
		},
		DirectX::XMMatrixIdentity));*/
	//mesh = std::make_unique<Mesh>(Mesh::CreatePrimitiveSphere(window.GetRenderer(), 1.0F, 20U));
	std::ifstream file;
	file.open("Levels/levelSequence.json");
	if (file.is_open())
	{
		nlohmann::json j;
		file >> j;
		levelSequence = j["sequence"].get<std::vector<std::string>>();
		file.close();
	}
	if (!levelSequence.empty())
	{
		currentLevel = std::make_unique<Level>(window.GetRenderer(),levelSequence.front());
		levelSequence.erase(levelSequence.begin());
	}
	//gameObjects.push_back(std::make_unique<Model>(window.GetRenderer(), "Models/dog.obj", L"Models/dog.png"));
}

int App::Play()
{
	while (true)
	{
		if (const auto errorCode = Window::ProcessMessages())
		{
			return *errorCode;
		}
		GameLoop();
	}
	return -1;
}

void App::GameLoop()
{
	Update();
	Render();
	window.GetRenderer().EndFrame();
}

void App::Update()
{
	time.Tick();
	input.Tick();
	currentLevel->Update(input, time);
	for (auto& gameObject : gameObjects)
	{
		gameObject->Update(input, time);
	}
	CollisionManager::DetectCollisions(time.Delta());
	if (currentLevel->finished && !levelSequence.empty())
	{
		CollisionManager::colliders.clear();
		currentLevel = std::make_unique<Level>(window.GetRenderer(), levelSequence.front());
		levelSequence.erase(levelSequence.begin());
	}
}

void App::Render()
{
	const float t = -time.Time();
	const float r = sinf(t) / 2.0F + 0.5F;
	const float g = sinf(t + 2.0F) / 2.0F + 0.5F;
	const float b = sinf(t + 4.0F) / 2.0F + 0.5F;
	window.GetRenderer().SetBackground(Colour(r, g, b));
	if (ttfps <= 0.0F)
	{
		int fps = static_cast<int>(1.0F / time.Delta());
		window.SetTitle("Super Funky Ball: " + std::to_string(fps) + " FPS");
		ttfps = 1.0F;
	}
	ttfps -= time.Delta();
	currentLevel->Render(window.GetRenderer());
	for (auto& gameObject : gameObjects)
	{
		gameObject->Render(window.GetRenderer());
	}
	//mesh->Render(window.GetRenderer());
	//window.GetRenderer().RenderTestTriangle(time.Time());
}
