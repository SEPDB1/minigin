#pragma once
#include "MiniginEngine.h"

namespace dae
{
	namespace test
	{
		static void LoadTestScene()
		{
			auto& inputManager{ InputManager::GetInstance() };
			auto& sceneManager{ SceneManager::GetInstance() };
			auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

			auto pTestScene = std::addressof(sceneManager.CreateScene());

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
			auto pBackground = std::addressof(pTestScene->AddObject());
			pBackground->AttachComponent<dae::RenderComponent>()->LoadTexture("background.png");

			// Create movable logo
			auto pLogo = std::addressof(pTestScene->AddObject());
			pLogo->SetPosition(glm::vec3(358, 180, 0.f));
			pLogo->AttachComponent<dae::RenderComponent>()->LoadTexture("logo.png");
			auto pPlayerInput{ pLogo->AttachComponent<dae::PlayerInputComponent>(pKeyboard) };
			pPlayerInput->AddCommandBinding("Move", std::make_unique<MoveCommand>(pLogo, 2.f));

			// Create movable title
			auto pTitle = std::addressof(pTestScene->AddObject());
			pTitle->SetPosition(glm::vec2(292, 20));
			pTitle->AttachComponent<dae::TextComponent>()->SetText("Programming 4 Assignment", font).SetColor({ 255, 255, 0, 255 });
			pPlayerInput = pTitle->AttachComponent<dae::PlayerInputComponent>(pGamepad);
			pPlayerInput->AddCommandBinding("Move", std::make_unique<MoveCommand>(pTitle, 4.f));

			// Create FPS object
			auto pFpsObject = std::addressof(pTestScene->AddObject());
			auto pTextO = pFpsObject->AttachComponent<dae::TextComponent>();
			pTextO->SetText("FPS", font).SetColor({ 255, 255, 0, 255 });
			pFpsObject->AttachComponent<dae::FpsComponent>()->SetTextComponent(pTextO);
		}
	}
}