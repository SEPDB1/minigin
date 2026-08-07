#include "Game.h"

// Project Includes
#include "MiniginEngine.h"
#include "PlayerTankComponent.h"
#include "TestScene.h"

dae::Game::Game()
{

}

void dae::Game::Start()
{
	auto& inputManager{ InputManager::GetInstance() };
	auto& sceneManager{ SceneManager::GetInstance() };
	auto& scene{ sceneManager.GetActiveScene() };

	auto wasdControl{ 
		std::make_unique<CompoundControlButton>(
			Button{ "A" },
			Button{ "D" },
			Button{ "W" },
			Button{ "S" }
		)
	};

	auto dpadControl{
		std::make_unique<CompoundControlButton>(
			Button{ "DpadLeft" },
			Button{ "DpadRight" },
			Button{ "DpadUp" },
			Button{ "DpadDown" }
		)
	};

	auto stickControl{
		std::make_unique<CompoundControlAxis>(Axis::rightStick) 
	};

	auto mouseControl{
		std::make_unique<CompoundControlAxis>(Axis::Mouse)
	};


	std::vector<std::unique_ptr<CompoundControl>> moveControls{};
	moveControls.push_back(std::move(wasdControl));
	moveControls.push_back(std::move(dpadControl));

	std::vector<std::unique_ptr<CompoundControl>> aimControls{};
	aimControls.push_back(std::move(stickControl));
	aimControls.push_back(std::move(mouseControl));

	auto pMoveAction{ std::make_unique<InputActionAxis2D>(std::move(moveControls)) };
	auto pAimAction{ std::make_unique<InputActionAxis2D>(std::move(aimControls)) };

	inputManager.AddInputAction("Move", std::move(pMoveAction));
	inputManager.AddInputAction("Aim", std::move(pAimAction));

	// Tank1
	const auto pGamepad{ inputManager.CreateInputDevice<Gamepad>() };
	scene.AddObject().AttachComponent<PlayerTankComponent>(pGamepad, glm::vec2(100.f, 200));

	// Tank2
	const auto pKeyboard{ inputManager.CreateInputDevice<Keyboard>() };
	const auto pMouse{ inputManager.CreateInputDevice<Mouse>() };
	const std::vector<const InputDevice*> devicesTank1{ pKeyboard, pMouse };
	scene.AddObject().AttachComponent<PlayerTankComponent>(devicesTank1, glm::vec2(500.f, 200));
}

void dae::Game::Update()
{
}