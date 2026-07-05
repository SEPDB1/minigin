#include "Game.h"

// Project Includes
#include "MiniginEngine.h"
#include "TestScene.h"

dae::Game::Game() = default;

void dae::Game::Start()
{
	auto& inputManager{ InputManager::GetInstance() };
	auto& sceneManager{ SceneManager::GetInstance() };
	auto& scene{ sceneManager.CreateScene() };
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	inputManager.AddInputAction("Move", std::make_unique<InputActionAxis2D>(
		Button{ "DpadLeft", DeviceType::gamepad },
		Button{ "DpadRight", DeviceType::gamepad },
		Button{ "DpadUp", DeviceType::gamepad },
		Button{ "DpadDown", DeviceType::gamepad }
	));

	// Tank
	auto pGamepad{ inputManager.CreateInputDevice<Gamepad>() };
	m_pTank = std::addressof(scene.AddObject());
	m_pTank->SetPosition(glm::vec2(300.f, 100.f)).SetScale(glm::vec2(8.f, 8.f));
	auto& input{ m_pTank->AttachComponent<PlayerInputComponent>(pGamepad) };
	auto& renderComp{ m_pTank->AttachComponent<RenderComponent>() };
	renderComp.LoadTexture("BlueTank.png");

	// RotationValue
	auto& valueDisplay{ scene.AddObject() };
	m_pTankValueDisplay = std::addressof(valueDisplay.AttachComponent<TextComponent>().SetText("B", font).SetColor(SDL_Color{255, 255, 255}));
	
	input.AddCommandBinding("Move", std::make_unique<MoveCommand>(m_pTank, 4.f));
	//test::LoadTestScene();
}

void dae::Game::Update()
{
	float etime{ Timer::GetInstance().GetElapsedTime() };
	const auto& tankTransform{ m_pTank->GetTransform() };

	m_pTank->SetRotation(tankTransform.GetRotationRadians() + etime * m_RotationSpeed);
	m_pTankValueDisplay->SetText(std::to_string(m_pTank->GetTransform().GetRotationDegrees()));
}