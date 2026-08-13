#include "StartScreen.h"
#include "MiniginEngine.h"
#include "DeviceSlot.h"
#include <algorithm>

dae::StartScreen::StartScreen(GameObject* pGameObject)
	: BaseComponent(pGameObject)
	, m_Title{ SceneManager::GetInstance().GetActiveScene().AddObject().AttachComponent<TextComponent>() }
	, m_pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 160) }
{
	auto& scene{ SceneManager::GetInstance().GetActiveScene() };
	m_Title.SetText("Tron", m_pFont);
	m_Title.GetOwner()->SetPosition(glm::vec2(350.f, 75.f));

	for (auto& pair : m_pActivatedDevices)
		pair.second = std::addressof(scene.AddObject().AttachComponent<DeviceSlot>());

	m_pActivatedDevices[0].second->GetOwner()->SetPosition(glm::vec2(200.f, 550.f)).SetScale(glm::vec2(2.5f, 2.5));
	m_pActivatedDevices[1].second->GetOwner()->SetPosition(glm::vec2(800.f, 550.f)).SetScale(glm::vec2(2.5f, 2.5f));
	SoundLocator::GetSoundSystem().Play("Sounds/MainMenuMusic.mp3");
}

void dae::StartScreen::AddDevice(const dae::InputDevice* pDevice)
{
	// Find first open slot
	auto it = std::ranges::find_if(
		m_pActivatedDevices, 
		[pDevice](auto& pair) { return pair.first == nullptr; }
	);

	// Stop when no slot is open
	if (it == m_pActivatedDevices.end())
		return;

	// Set device image
	it->first = pDevice;
	it->second->ChangeImage(pDevice->GetType());
}

void dae::StartScreen::RemoveDevice(const InputDevice* pDevice)
{
	auto it = std::ranges::find_if(
		m_pActivatedDevices, 
		[pDevice](auto& pair) { return pair.first == pDevice; }
	);

	// The device is not in the list
	if (it == m_pActivatedDevices.end())
		return;

	it->first = nullptr;
	it->second->ChangeImage(DeviceSlot::Visual::noDevice);
}

void dae::StartScreen::ReadyUp(const InputDevice* pDevice)
{
	auto it = std::ranges::find_if(
		m_pActivatedDevices,
		[pDevice](auto& pair) { return pair.first == pDevice; }
	);

	// The device is not in the list
	if (it != m_pActivatedDevices.end())
		it->second->ReadyUp();
}
