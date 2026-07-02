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

	const std::string gamepadActionName{ "GamepadMove" };
	const std::string keyboardActionName{ "KeyboardMove" };
	
	inputManager.AddInputAction(
		gamepadActionName,
		std::make_unique<InputActionAxis2D>(
			Button{ "DpadLeft", DeviceType::gamepad },
			Button{ "DpadRight", DeviceType::gamepad },
			Button{ "DpadUp", DeviceType::gamepad },
			Button{ "DpadDown", DeviceType::gamepad }
		)
	);

	inputManager.AddInputAction(
		keyboardActionName,
		std::make_unique<InputActionAxis2D>(
			Button{ "A", DeviceType::keyboard },
			Button{ "D", DeviceType::keyboard },
			Button{ "W", DeviceType::keyboard },
			Button{ "S", DeviceType::keyboard }
		)
	);

	// Create background
	auto go = std::make_unique<dae::GameObject>();
	m_pBackground = go.get();
	m_pBackground->AttachComponent<dae::RenderComponent>(m_pBackground)->LoadTexture("background.png");
	m_pScene->Add(std::move(go));

	// Create movable logo
	go = std::make_unique<dae::GameObject>();
	m_pLogo = go.get();
	m_pLogo->SetPosition(glm::vec3(358, 180, 0.f));
	m_pLogo->AttachComponent<dae::RenderComponent>(m_pLogo)->LoadTexture("logo.png");
	auto pPlayerInput{ m_pLogo->AttachComponent<dae::PlayerInputComponent>(m_pLogo, pKeyboard) };
	pPlayerInput->AddCommandBinding(keyboardActionName, std::make_unique<MoveCommand>(m_pLogo, 2.f));
	m_pScene->Add(std::move(go));

	// Create movable title
	go = std::make_unique<dae::GameObject>();
	m_pTitle = go.get();
	go->SetPosition(glm::vec2(292, 20));
	go->AttachComponent<dae::TextComponent>(go.get())->SetText("Programming 4 Assignment", font).SetColor({ 255, 255, 0, 255 });
	pPlayerInput = m_pTitle->AttachComponent<dae::PlayerInputComponent>(m_pTitle, pGamepad);
	pPlayerInput->AddCommandBinding(gamepadActionName, std::make_unique<MoveCommand>(m_pTitle, 4.f));
	m_pScene->Add(std::move(go));

	// Create FPS object
	go = std::make_unique<dae::GameObject>();
	m_pFpsObject = go.get();
	auto pTextO = m_pFpsObject->AttachComponent<dae::TextComponent>(m_pFpsObject);
	pTextO->SetText("FPS", font).SetColor({ 255, 255, 0, 255 });
	go->AttachComponent<dae::FpsComponent>(m_pFpsObject)->SetTextComponent(pTextO);
	m_pScene->Add(std::move(go));
}

void dae::Game::Update()
{

}