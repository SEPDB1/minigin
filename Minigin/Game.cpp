#include "Game.h"
#include <algorithm>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FpsComponent.h"
#include "RotaterComponent.h"
#include "PlayerInputComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "Gamepad.h"
#include "Keyboard.h"
#include "Command.h"

dae::Game::Game(Scene* pScene)
	: m_pScene{ pScene }
{

}


void dae::Game::Start()
{
	auto& inputManager{ InputManager::GetInstance() };
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
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
	auto go = std::make_unique<dae::GameObject>();
	m_pBackground = go.get();
	m_pBackground->AttachComponent<dae::RenderComponent>()->LoadTexture("background.png");
	m_pScene->Add(std::move(go));

	// Create movable logo
	go = std::make_unique<dae::GameObject>();
	m_pLogo = go.get();
	m_pLogo->SetPosition(glm::vec3(358, 180, 0.f));
	m_pLogo->AttachComponent<dae::RenderComponent>()->LoadTexture("logo.png");
	auto pPlayerInput{ m_pLogo->AttachComponent<dae::PlayerInputComponent>(pKeyboard) };
	pPlayerInput->AddCommandBinding("Move", std::make_unique<MoveCommand>(m_pLogo, 2.f));
	m_pScene->Add(std::move(go));

	// Create movable title
	go = std::make_unique<dae::GameObject>();
	m_pTitle = go.get();
	go->SetPosition(glm::vec2(292, 20));
	go->AttachComponent<dae::TextComponent>()->SetText("Programming 4 Assignment", font).SetColor({ 255, 255, 0, 255 });
	pPlayerInput = m_pTitle->AttachComponent<dae::PlayerInputComponent>(pGamepad);
	pPlayerInput->AddCommandBinding("Move", std::make_unique<MoveCommand>(m_pTitle, 4.f));
	m_pScene->Add(std::move(go));

	// Create FPS object
	go = std::make_unique<dae::GameObject>();
	m_pFpsObject = go.get();
	auto pTextO = m_pFpsObject->AttachComponent<dae::TextComponent>();
	pTextO->SetText("FPS", font).SetColor({ 255, 255, 0, 255 });
	go->AttachComponent<dae::FpsComponent>()->SetTextComponent(pTextO);
	m_pScene->Add(std::move(go));
}

void dae::Game::Update()
{

}