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
			auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

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
			auto& background{ pTestScene->AddObject() };
			background.AttachComponent<RenderComponent>().LoadTexture("background.png");

			// Create movable logo
			auto& logo{ pTestScene->AddObject() };
			logo.SetPosition(glm::vec3(358, 180, 0.f));
			logo.AttachComponent<dae::RenderComponent>().LoadTexture("logo.png");
			auto& playerInputLogo{ logo.AttachComponent<PlayerInputComponent>(pKeyboard) };
			playerInputLogo.AddCommandBinding("Move", std::make_unique<MoveCommand>(std::addressof(logo), 2.f));

			// Create movable title
			auto& title{ pTestScene->AddObject() };
			title.SetPosition(glm::vec2(292, 20));
			title.AttachComponent<dae::TextComponent>().SetText("Programming 4 Assignment", font).SetColor({ 255, 255, 0, 255 });
			auto& playerInputTitle = title.AttachComponent<dae::PlayerInputComponent>(pGamepad);
			playerInputTitle.AddCommandBinding("Move", std::make_unique<MoveCommand>(std::addressof(title), 4.f));

			// Create FPS object
			auto& fpsObj = pTestScene->AddObject();
			auto& fpsTextComp{ fpsObj.AttachComponent<dae::TextComponent>() };
			fpsTextComp.SetText("FPS", font).SetColor({ 255, 255, 0, 255 });
			fpsObj.AttachComponent<FpsComponent>().SetTextComponent(std::addressof(fpsTextComp));
		}
	}
}