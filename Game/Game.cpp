#include "Game.h"

// Project Includes
#include "MiniginEngine.h"
#include "PlayerTank.h"
#include "TestScene.h"

dae::Game::Game()
{

}

void dae::Game::Start()
{
	// Cache singletons
	auto& inputManager{ InputManager::GetInstance() };
	auto& sceneManager{ SceneManager::GetInstance() };
	auto& scene{ sceneManager.GetActiveScene() };

	// Create devices
	const auto pKeyboard{ inputManager.CreateInputDevice<Keyboard>() };
	const auto pMouse{ inputManager.CreateInputDevice<Mouse>() };
	const auto pGamepad{ inputManager.CreateInputDevice<Gamepad>() };

	// Move action
	auto keyboardMoveControl{ 
		std::make_unique<CompoundControlButton>(
			Button{ "KeyA" },
			Button{ "KeyD" },
			Button{ "KeyW" },
			Button{ "KeyS" }
		)
	};

	auto gamepadMoveControl{
		std::make_unique<CompoundControlButton>(
			Button{ "DpadLeft" },
			Button{ "DpadRight" },
			Button{ "DpadUp" },
			Button{ "DpadDown" }
		)
	};

	std::vector<std::unique_ptr<CompoundControl>> moveControls{};
	moveControls.push_back(std::move(keyboardMoveControl));
	moveControls.push_back(std::move(gamepadMoveControl));

	auto pMoveAction{ std::make_unique<InputActionAxis2D>(std::move(moveControls)) };
	inputManager.AddInputAction("Move", std::move(pMoveAction));

	// Aim action
	auto gamepadAimControl{ std::make_unique<CompoundControlAxis>(Axis::rightStick) };
	auto keyboardAimControl{ std::make_unique<CompoundControlAxis>(Axis::Mouse) };

	std::vector<std::unique_ptr<CompoundControl>> aimControls{};
	aimControls.push_back(std::move(gamepadAimControl));
	aimControls.push_back(std::move(keyboardAimControl));

	auto pAimAction{ std::make_unique<InputActionAxis2D>(std::move(aimControls)) };
	inputManager.AddInputAction("Aim", std::move(pAimAction));

	// Shoot action
	std::vector<Button> shootButtons{};
	shootButtons.push_back( std::move(Button{ "KeySpace" }) );
	shootButtons.push_back( std::move(Button{ "RightShoulder" }) );

	auto pShootAction{ std::make_unique<InputActionButton>(std::move(shootButtons)) };
	inputManager.AddInputAction("Shoot", std::move(pShootAction));

	// Tank1
	scene.AddObject().AttachComponent<PlayerTank>(pGamepad, glm::vec2(100.f, 200));

	// Tank2
	std::vector<const InputDevice*> devicesTank1{ pKeyboard, pMouse };
	scene.AddObject().AttachComponent<PlayerTank>(std::move(devicesTank1), glm::vec2(500.f, 200));
}

void dae::Game::Update()
{
}