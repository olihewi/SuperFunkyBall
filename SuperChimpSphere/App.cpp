#include "App.h"
#include "Model.h"
#include "Camera.h"
#include "Player.h"
#include "Level.h"
#include "CollisionManager.h"
#include <fstream>
#include "Json.h"
#include "Light.h"
#include <thread>

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
	/*std::ifstream file;
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
	}*/
	currentLevel = std::make_unique<Level>(window.GetRenderer(), "Levels/stage4.json");
	//gameObjects.push_back(std::make_unique<Model>(window.GetRenderer(), "Models/dog.obj", L"Models/dog.png"));
}

int App::Play()
{
	std::thread renderThread = std::thread([this]()
	{
		while (playing)
		{
			Render();
		}
	});
	while (true)
	{
		if (const auto errorCode = Window::ProcessMessages())
		{
			playing = false;
			renderThread.join();
			return *errorCode;
		}
		GameLoop();
	}
	return -1;
}

void App::GameLoop()
{
	Update();
	if (ttfps <= 0.0F)
	{
		int fps = static_cast<int>(1.0F / time.Delta());
		window.SetTitle("Super Funky Ball | Game: " + std::to_string(fps) + " TPS | Render: " + std::to_string(static_cast<int>(1.0F / window.GetRenderer().GetRenderTime().Delta())) + " FPS");
		ttfps = 1.0F;
	}
	ttfps -= time.Delta();
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
	if (currentLevel->finished)
	{
		CollisionManager::colliders.clear();
		currentLevel = std::make_unique<Level>(window.GetRenderer(), currentLevel->nextLevel);
	}
}

void App::Render()
{
	window.GetRenderer().SetBackground(Colours::CornflowerBlue);
	currentLevel->Render(window.GetRenderer());
	for (auto& gameObject : gameObjects)
	{
		gameObject->Render(window.GetRenderer());
	}
	window.GetRenderer().EndFrame();
}
