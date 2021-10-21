#include "App.h"

App::App(const GameSettings& _settings) : settings(_settings), window(static_cast<int>(settings.video.resolution.x),static_cast<int>(settings.video.resolution.y),"ASGE")
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
	gameObjects.push_back(std::make_unique<GameObject>(window.GetRenderer()));
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
	for (auto& gameObject : gameObjects)
	{
		gameObject->Update(window.GetKeyboard(), time);
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
