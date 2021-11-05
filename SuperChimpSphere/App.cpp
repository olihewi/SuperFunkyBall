#include "App.h"
#include "Model.h"
#include "Camera.h"
#include "Player.h"
#include "PhysicsTestSphere.h"
#include "CollisionManager.h"

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
	gameObjects.push_back(std::make_unique<Player>(window.GetRenderer()));
	gameObjects.push_back(std::make_unique<Camera>(window.GetRenderer(), dynamic_cast<Player*>(gameObjects.back().get())));
	int numberOfDogs = 2000;
	int w = std::sqrt(numberOfDogs);
	for (int i = 0; i < numberOfDogs; i++)
	{
		gameObjects.push_back(std::make_unique<PhysicsTestSphere>(window.GetRenderer(),Vector3(2.0F + (i%w)*2.0F,-2.0F,-(i/w)*2.0F)));
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
	CollisionManager::DetectCollisions();
	for (auto& gameObject : gameObjects)
	{
		gameObject->Update(input, time);
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
	for (auto& gameObject : gameObjects)
	{
		gameObject->Render(window.GetRenderer());
	}
	//mesh->Render(window.GetRenderer());
	//window.GetRenderer().RenderTestTriangle(time.Time());
}
