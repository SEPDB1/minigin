#include "Game.h"

// Standard Includes
#include <algorithm>

// Project Includes
#include "MiniginEngine.h"

dae::Game::Game() = default;

void dae::Game::Start()
{
	auto& inputManager{ InputManager::GetInstance() };
	auto& sceneManager{ SceneManager::GetInstance() };
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	m_pTestScene = std::addressof(sceneManager.CreateScene());
	
	auto pGamepad{ inputManager.CreateInputDevice<dae::Gamepad>() };
	auto pKeyboard{ inputManager.CreateInputDevice<dae::Keyboard>() };

	inputManager.AddInputAction(
		"Move",
		std::make_unique<InputActionAxis2D>(
			std::vector<Button>{ Button{ "A", DeviceType::keyboard }, Button{ "DpadLeft", DeviceType::gamepad } },
			std::vector<Button>{ Button{ "D", DeviceType::keyboard }, Button{ "DpadRight", DeviceType::gamepad } },
			std::vector<Button>{ Button{ "W", DeviceType::keyboard }, Button{ "DpadUp", DeviceType::gamepad } },
			std::vector<Button>{ Button{ "S", DeviceType::keyboard }, Button{ "DpadDown", DeviceType::gamepad } }
		)
	);

	// Create background
	m_pBackground = std::addressof(m_pTestScene->AddObject());
	m_pBackground->AttachComponent<dae::RenderComponent>()->LoadTexture("background.png");

	// Create movable logo
	m_pLogo = std::addressof(m_pTestScene->AddObject());
	m_pLogo->SetPosition(glm::vec3(358, 180, 0.f));
	m_pLogo->AttachComponent<dae::RenderComponent>()->LoadTexture("logo.png");
	auto pPlayerInput{ m_pLogo->AttachComponent<dae::PlayerInputComponent>(pKeyboard) };
	pPlayerInput->AddCommandBinding("Move", std::make_unique<MoveCommand>(m_pLogo, 2.f));

	// Create movable title
	m_pTitle = std::addressof(m_pTestScene->AddObject());
	m_pTitle->SetPosition(glm::vec2(292, 20));
	m_pTitle->AttachComponent<dae::TextComponent>()->SetText("Programming 4 Assignment", font).SetColor({ 255, 255, 0, 255 });
	pPlayerInput = m_pTitle->AttachComponent<dae::PlayerInputComponent>(pGamepad);
	pPlayerInput->AddCommandBinding("Move", std::make_unique<MoveCommand>(m_pTitle, 4.f));

	// Create FPS object
	m_pFpsObject = std::addressof(m_pTestScene->AddObject());
	auto pTextO = m_pFpsObject->AttachComponent<dae::TextComponent>();
	pTextO->SetText("FPS", font).SetColor({ 255, 255, 0, 255 });
	m_pFpsObject->AttachComponent<dae::FpsComponent>()->SetTextComponent(pTextO);
}

void dae::Game::Update()
{

}