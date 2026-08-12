#include "DeviceSlot.h"
#include "MiniginEngine.h"

dae::DeviceSlot::DeviceSlot(GameObject* pGameObject)
	: BaseComponent(pGameObject)
	, m_MenuBox{ SceneManager::GetInstance().GetActiveScene().AddObject().AttachComponent<RenderComponent>() }
	, m_Title{ SceneManager::GetInstance().GetActiveScene().AddObject().AttachComponent<TextComponent>() }
	, m_Ready{ SceneManager::GetInstance().GetActiveScene().AddObject().AttachComponent<TextComponent>() }
	, m_NotReady{ SceneManager::GetInstance().GetActiveScene().AddObject().AttachComponent<TextComponent>() }
{
	auto& scene{ SceneManager::GetInstance().GetActiveScene() };
	auto pOwner{ BaseComponent::GetOwner() };

	m_pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_MenuBox.LoadTexture("Sprites/MenuBox.png");
	m_MenuBox.GetOwner()->SetParent(pOwner).SetScale(glm::vec2(1.4f, 1.4f));
	m_Title.SetText("Player " + std::to_string(++m_Count), m_pFont).GetOwner()->SetParent(pOwner).SetPosition(glm::vec2(-35.f, -90.f));
	m_Ready.SetText("Ready", m_pFont, SDL_Color{ 0, 255, 0, 255 }).GetOwner()->SetParent(pOwner).SetPosition(glm::vec2(-30.f, -67.f));
	m_NotReady.SetText("Not Ready", m_pFont, SDL_Color{ 255, 0, 0, 255 }).GetOwner()->SetParent(pOwner).SetPosition(glm::vec2(-46.f, -67.f));

	DisplayReadyUp();

	for (auto& pSprite : m_pSprites)
	{
		auto& gameObj{ scene.AddObject() };

		gameObj.SetParent(pOwner);
		gameObj.SetActiveSelf(false);
		pSprite = std::addressof(gameObj.AttachComponent<RenderComponent>());
	}

	m_pSprites[std::to_underlying(Visual::noDevice)]->LoadTexture("Sprites/Cross.png");
	m_pSprites[std::to_underlying(Visual::noDevice)]->GetOwner()->SetActiveSelf(true);
	m_pSprites[std::to_underlying(Visual::gamepad)]->LoadTexture("Sprites/Gamepad.png");
	m_pSprites[std::to_underlying(Visual::keyboard)]->LoadTexture("Sprites/Keyboard.png");
}

void dae::DeviceSlot::ChangeImage(Visual image)
{
	if (m_CurrentVisual == image)
		return;

	m_pSprites[std::to_underlying(m_CurrentVisual)]->GetOwner()->SetActiveSelf(false);
	m_pSprites[std::to_underlying(image)]->GetOwner()->SetActiveSelf(true);

	m_CurrentVisual = image;
}

void dae::DeviceSlot::ChangeImage(DeviceType type)
{
	Visual newVisual{ Visual::noDevice };

	if (type == DeviceType::keyboard)
		newVisual = Visual::keyboard;
	else if (type == DeviceType::gamepad)
		newVisual = Visual::gamepad;

	ChangeImage(newVisual);
}

void dae::DeviceSlot::ReadyUp()
{
	m_IsReady = !m_IsReady;
	DisplayReadyUp();
}

void dae::DeviceSlot::DisplayReadyUp()
{
	m_Ready.GetOwner()->SetActiveSelf(m_IsReady);
	m_NotReady.GetOwner()->SetActiveSelf(!m_IsReady);
}
