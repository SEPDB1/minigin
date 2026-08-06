#include "Game.h"

// Project Includes
#include "MiniginEngine.h"
#include "PlayerTankComponent.h"
#include "TestScene.h"

dae::Game::Game() = default;

void dae::Game::Start()
{
	auto& inputManager{ InputManager::GetInstance() };
	auto& sceneManager{ SceneManager::GetInstance() };
	auto& scene{ sceneManager.GetActiveScene() };

	inputManager.AddInputAction("Move", std::make_unique<InputActionAxis2D>(
		Button{ "DpadLeft", DeviceType::gamepad },
		Button{ "DpadRight", DeviceType::gamepad },
		Button{ "DpadUp", DeviceType::gamepad },
		Button{ "DpadDown", DeviceType::gamepad }
	));

	// Tank
	const auto pGamepad{ inputManager.CreateInputDevice<Gamepad>() };
	m_pTank = std::addressof(scene.AddObject());
	m_pTank->AttachComponent<PlayerTankComponent>(pGamepad);
}

void dae::Game::Update()
{
}