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

	inputManager.AddInputAction("Move", std::make_unique<InputActionAxis2D>(
		Button{ "DpadLeft", DeviceType::gamepad },
		Button{ "DpadRight", DeviceType::gamepad },
		Button{ "DpadUp", DeviceType::gamepad },
		Button{ "DpadDown", DeviceType::gamepad }
	));

	auto pGamepad{ inputManager.CreateInputDevice<Gamepad>() };
	auto& player{ scene.AddObject() };
	auto& input{ player.AttachComponent<PlayerInputComponent>(pGamepad) };
	auto& renderComp{ player.AttachComponent<RenderComponent>() };
	renderComp.LoadTexture("BlueTank.png");

	input.AddCommandBinding("Move", std::make_unique<MoveCommand>(std::addressof(player), 4.f));
}

void dae::Game::Update()
{

}