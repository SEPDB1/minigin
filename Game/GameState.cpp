#include "GameState.h"
#include "MiniginEngine.h"
#include "PlayerTank.h"
#include "Grid.h"
#include "CollisionUtility.h"
#include "GameCommands.h"
#include "StartScreen.h"

dae::GameState::GameState()
{
	// Cache singletons
	auto& inputManager{ InputManager::GetInstance() };
	auto& sceneManager{ SceneManager::GetInstance() };
	auto& scene{ sceneManager.GetActiveScene() };
	auto& renderer{ SDLRenderer::GetInstance() };

	Rect screenBounds{ renderer.GetScreenBounds() };

	// Create devices
	const auto pKeyboard{ inputManager.CreateInputDevice<Keyboard>() };
	const auto pMouse{ inputManager.CreateInputDevice<Mouse>() };
	const auto pGamepad1{ inputManager.CreateInputDevice<Gamepad>() };
	const auto pGamepad2{ inputManager.CreateInputDevice<Gamepad>() };

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
	shootButtons.push_back(std::move(Button{ "KeySpace" }));
	shootButtons.push_back(std::move(Button{ "RightShoulder" }));

	auto pShootAction{ std::make_unique<InputActionButton>(std::move(shootButtons)) };
	inputManager.AddInputAction("Shoot", std::move(pShootAction));

	// Grid
	scene.AddObject().AttachComponent<Grid>();

	// Tank1
	scene.AddObject().AttachComponent<RedPlayerTank>(pGamepad1, glm::vec2(screenBounds.GetCenter().x - 300.f, 200.f));

	// Tank2
	std::vector<const InputDevice*> devicesTank1{ pKeyboard, pMouse };
	scene.AddObject().AttachComponent<BluePlayerTank>(pGamepad2, glm::vec2(500.f, 200.f));

	constexpr size_t size{ 17 };
	std::array<glm::vec2, size> spawnPoints
	{
		glm::vec2(screenBounds.GetCenter().x + 128.f, 100.f),
		glm::vec2(screenBounds.GetCenter().x + 128.f, 100.f + 1.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 128.f, 100.f + 2.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 128.f, 100.f + 3.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 128.f, 100.f + 4.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f, 100.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f, 100.f + 1.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f, 100.f + 2.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f, 100.f + 3.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f, 100.f + 4.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f, 100.f + 5.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f, 100.f + 6.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f - 0.f * 128.f, 100.f + 6.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f - 1.f * 128.f, 100.f + 6.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f - 2.f * 128.f, 100.f + 6.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f - 3.f * 128.f, 100.f + 6.f * 128.f),
		glm::vec2(screenBounds.GetCenter().x + 400.f - 4.f * 128.f, 100.f + 6.f * 128.f),
	};

	for (const auto& v : spawnPoints)
	{
		auto& obstacle{ scene.AddObject() };
		obstacle.SetPosition(v).SetScale(glm::vec2(4.f, 4.f));
		obstacle.AttachComponent<RenderComponent>().LoadTexture("Sprites/BlueTank.png");
		obstacle.AttachComponent<HitboxComponent>(32.f, 32.f, true);
	}

	// Test obstacle
	SoundLocator::GetSoundSystem().Play("Sounds/MainMenuMusic.mp3", 0.f);
}

dae::GameState::~GameState()
{

}

std::unique_ptr<dae::IGameState> dae::GameState::Update()
{
	return nullptr;
}

dae::StartScreenState::StartScreenState()
{
	auto& inputManager{ InputManager::GetInstance() };
	auto& scene{ SceneManager::GetInstance().GetActiveScene() };
	auto& startScreen{ scene.AddObject().AttachComponent<StartScreen>() };

	// Create all possible devices
	const auto pKeyboard{ inputManager.CreateInputDevice<Keyboard>() };
	const auto pMouse{ inputManager.CreateInputDevice<Mouse>() };
	const auto pGamepad1{ inputManager.CreateInputDevice<Gamepad>() };
	const auto pGamepad2{ inputManager.CreateInputDevice<Gamepad>() };

	// Create InputComponent that keeps track of the input on the startscreen
	std::vector<const InputDevice*> pJoinDevices{ pKeyboard, pGamepad1, pGamepad2 };
	auto& playerCompCombined{ scene.AddObject().AttachComponent<PlayerInputComponent>(std::move(pJoinDevices)) };


	// Make a join action that works for both keyboard and gamepad
	std::vector<Button> joinButtons{};
	joinButtons.emplace_back("KeySpace");
	joinButtons.emplace_back("A");

	auto pJoinAction{ std::make_unique<InputActionButton>(std::move(joinButtons)) };
	inputManager.AddInputAction("Join", std::move(pJoinAction));

	playerCompCombined.AddCommandBinding("Join", std::move(std::make_unique<JoinCommand>(startScreen.GetOwner())));

	// Make a leave action 
	std::vector<Button> leaveButtons{};
	leaveButtons.emplace_back("KeyBackspace");
	leaveButtons.emplace_back("B");

	auto pLeaveAction{ std::make_unique<InputActionButton>(std::move(leaveButtons)) };
	inputManager.AddInputAction("Leave", std::move(pLeaveAction));

	playerCompCombined.AddCommandBinding("Leave", std::move(std::make_unique<LeaveCommand>(startScreen.GetOwner())));

	// Make a ready up action
	std::vector<Button> readyUpButtons{};
	readyUpButtons.emplace_back("KeyEnter");
	readyUpButtons.emplace_back("Start");

	auto pReadyUpAction{ std::make_unique<InputActionButton>(std::move(readyUpButtons)) };
	inputManager.AddInputAction("ReadyUp", std::move(pReadyUpAction));

	playerCompCombined.AddCommandBinding("ReadyUp", std::move(std::make_unique<ReadyUpCommand>(startScreen.GetOwner())));

}

dae::StartScreenState::~StartScreenState()
{
}

std::unique_ptr<dae::IGameState> dae::StartScreenState::Update()
{
	return nullptr;
}