#include "Keyboard.h"
#include <SDL3/SDL_keyboard.h>
#include <unordered_map>

#pragma region KeyboardImpl

class dae::Keyboard::KeyboardImpl final
{
public:
	KeyboardImpl() = default;
	~KeyboardImpl() = default;
	KeyboardImpl(const KeyboardImpl& other) = delete;
	KeyboardImpl(KeyboardImpl&& other) = delete;
	KeyboardImpl& operator=(const KeyboardImpl& other) = delete;
	KeyboardImpl& operator=(KeyboardImpl&& other) = delete;

	void Update();

	bool IsDownThisFrame(const dae::Button& button) const;
	bool IsUpThisFrame(const dae::Button& button) const;
	bool IsPressed(const dae::Button& button) const;
	glm::vec2 GetAxisValue(Axis axis) const ;

private:
	uint8_t m_CurrentState[SDL_SCANCODE_COUNT]{};
	uint8_t m_PreviousState[SDL_SCANCODE_COUNT]{};

	static const std::unordered_map<std::string_view, uint32_t> m_ButtonTable;
};

const std::unordered_map<std::string_view, uint32_t> dae::Keyboard::KeyboardImpl::m_ButtonTable
{
	{ "KeyA",			SDL_SCANCODE_A },			
	{ "KeyB",			SDL_SCANCODE_B },			
	{ "KeyC",			SDL_SCANCODE_C },			
	{ "KeyD",			SDL_SCANCODE_D },			
	{ "KeyE",			SDL_SCANCODE_E },			
	{ "KeyF",			SDL_SCANCODE_F },			
	{ "KeyG",			SDL_SCANCODE_G },			
	{ "KeyH",			SDL_SCANCODE_H },			
	{ "KeyI",			SDL_SCANCODE_I },			
	{ "KeyJ",			SDL_SCANCODE_J },			
	{ "KeyK",			SDL_SCANCODE_K },			
	{ "KeyL",			SDL_SCANCODE_L },			
	{ "KeyM",			SDL_SCANCODE_M },			
	{ "KeyN",			SDL_SCANCODE_N },			
	{ "KeyO",			SDL_SCANCODE_O },			
	{ "KeyP",			SDL_SCANCODE_P },			
	{ "KeyQ",			SDL_SCANCODE_Q },			
	{ "KeyR",			SDL_SCANCODE_R },			
	{ "KeyS",			SDL_SCANCODE_S },			
	{ "KeyT",			SDL_SCANCODE_T },			
	{ "KeyU",			SDL_SCANCODE_U },			
	{ "KeyV",			SDL_SCANCODE_V },			
	{ "KeyW",			SDL_SCANCODE_W },			
	{ "KeyX",			SDL_SCANCODE_X },			
	{ "KeyY",			SDL_SCANCODE_Y },			
	{ "KeyZ",			SDL_SCANCODE_Z },			
	{ "Key1",			SDL_SCANCODE_1 },			
	{ "Key2",			SDL_SCANCODE_2 },			
	{ "Key3",			SDL_SCANCODE_3 },			
	{ "Key4",			SDL_SCANCODE_4 },			
	{ "Key5",			SDL_SCANCODE_5 },			
	{ "Key6",			SDL_SCANCODE_6 },			
	{ "Key7",			SDL_SCANCODE_7 },			
	{ "Key8",			SDL_SCANCODE_8 },			
	{ "Key9",			SDL_SCANCODE_9 },			
	{ "Key0",			SDL_SCANCODE_0 },			
	{ "KeyReturn",		SDL_SCANCODE_RETURN },		
	{ "KeyEscape",		SDL_SCANCODE_ESCAPE },		
	{ "KeyBackspace",	SDL_SCANCODE_BACKSPACE },	
	{ "KeyTab",		SDL_SCANCODE_TAB },		
	{ "KeySpace",		SDL_SCANCODE_SPACE },		
	{ "KeyF1",			SDL_SCANCODE_F1 },			
	{ "KeyF2",			SDL_SCANCODE_F2 },			
	{ "KeyF3",			SDL_SCANCODE_F3 },			
	{ "KeyF4",			SDL_SCANCODE_F4 },			
	{ "KeyF5",			SDL_SCANCODE_F5 },			
	{ "KeyF6",			SDL_SCANCODE_F6 },			
	{ "KeyF7",			SDL_SCANCODE_F7 },			
	{ "KeyF8",			SDL_SCANCODE_F8 },			
	{ "KeyF9",			SDL_SCANCODE_F9 },			
	{ "KeyF10",		SDL_SCANCODE_F10 },
	{ "KeyF11",		SDL_SCANCODE_F11 },		
	{ "KeyF12",		SDL_SCANCODE_F12 },		
};

void dae::Keyboard::KeyboardImpl::Update()
{
	std::memcpy(m_PreviousState, m_CurrentState, sizeof(m_CurrentState));
	std::memcpy(m_CurrentState, SDL_GetKeyboardState(nullptr), sizeof(m_CurrentState));
}

bool dae::Keyboard::KeyboardImpl::IsDownThisFrame(const Button& button) const
{
	auto it = m_ButtonTable.find(button.name);

	if (it != m_ButtonTable.end())
		return !m_PreviousState[it->second] && m_CurrentState[it->second];
	
	return false;
}

bool dae::Keyboard::KeyboardImpl::IsUpThisFrame(const Button& button) const
{
	auto it = m_ButtonTable.find(button.name);
	
	if (it != m_ButtonTable.end())
		return m_PreviousState[it->second] && !m_CurrentState[it->second];
	
	return false;
}

bool dae::Keyboard::KeyboardImpl::IsPressed(const Button& button) const
{
	auto it = m_ButtonTable.find(button.name);
	
	if (it != m_ButtonTable.end())
		return m_CurrentState[it->second];
	
	return false;
}

glm::vec2 dae::Keyboard::KeyboardImpl::GetAxisValue(Axis) const
{
	return glm::vec2();
}

#pragma endregion KeyboardImpl

#pragma region Keyboard

dae::Keyboard::Keyboard() 
	: m_pImpl{ std::make_unique<KeyboardImpl>() }
{
}

dae::Keyboard::~Keyboard() = default;

void dae::Keyboard::Update()
{
	m_pImpl->Update();
}

bool dae::Keyboard::IsDownThisFrame(const Button& button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool dae::Keyboard::IsUpThisFrame(const Button& button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

bool dae::Keyboard::IsPressed(const Button& button) const
{
	return m_pImpl->IsPressed(button);
}

glm::vec2 dae::Keyboard::GetAxisValue(Axis axis) const
{
	return m_pImpl->GetAxisValue(axis);
}

#pragma endregion Keyboard