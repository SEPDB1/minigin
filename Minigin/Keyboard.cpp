#include "Keyboard.h"
#include <SDL3/SDL_keyboard.h>

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

	bool IsButtonCompatible(const dae::Button& button) const;

	bool IsDownThisFrame(const dae::Button& button) const;
	bool IsUpThisFrame(const dae::Button& button) const;
	bool IsPressed(const dae::Button& button) const;

private:
	uint8_t m_CurrentState[SDL_SCANCODE_COUNT]{};
	uint8_t m_PreviousState[SDL_SCANCODE_COUNT]{};

	static const std::unordered_map<std::string_view, uint32_t> m_ButtonTable;
};

const std::unordered_map<std::string_view, uint32_t> dae::Keyboard::KeyboardImpl::m_ButtonTable
{
	{ "A",			SDL_SCANCODE_A },			
	{ "B",			SDL_SCANCODE_B },			
	{ "C",			SDL_SCANCODE_C },			
	{ "D",			SDL_SCANCODE_D },			
	{ "E",			SDL_SCANCODE_E },			
	{ "F",			SDL_SCANCODE_F },			
	{ "G",			SDL_SCANCODE_G },			
	{ "H",			SDL_SCANCODE_H },			
	{ "I",			SDL_SCANCODE_I },			
	{ "J",			SDL_SCANCODE_J },			
	{ "K",			SDL_SCANCODE_K },			
	{ "L",			SDL_SCANCODE_L },			
	{ "M",			SDL_SCANCODE_M },			
	{ "N",			SDL_SCANCODE_N },			
	{ "O",			SDL_SCANCODE_O },			
	{ "P",			SDL_SCANCODE_P },			
	{ "Q",			SDL_SCANCODE_Q },			
	{ "R",			SDL_SCANCODE_R },			
	{ "S",			SDL_SCANCODE_S },			
	{ "T",			SDL_SCANCODE_T },			
	{ "U",			SDL_SCANCODE_U },			
	{ "V",			SDL_SCANCODE_V },			
	{ "W",			SDL_SCANCODE_W },			
	{ "X",			SDL_SCANCODE_X },			
	{ "Y",			SDL_SCANCODE_Y },			
	{ "Z",			SDL_SCANCODE_Z },			
	{ "1",			SDL_SCANCODE_1 },			
	{ "2",			SDL_SCANCODE_2 },			
	{ "3",			SDL_SCANCODE_3 },			
	{ "4",			SDL_SCANCODE_4 },			
	{ "5",			SDL_SCANCODE_5 },			
	{ "6",			SDL_SCANCODE_6 },			
	{ "7",			SDL_SCANCODE_7 },			
	{ "8",			SDL_SCANCODE_8 },			
	{ "9",			SDL_SCANCODE_9 },			
	{ "0",			SDL_SCANCODE_0 },			
	{ "Return",		SDL_SCANCODE_RETURN },		
	{ "Escape",		SDL_SCANCODE_ESCAPE },		
	{ "Backspace",	SDL_SCANCODE_BACKSPACE },	
	{ "Tab",		SDL_SCANCODE_TAB },		
	{ "Space",		SDL_SCANCODE_SPACE },		
	{ "F1",			SDL_SCANCODE_F1 },			
	{ "F2",			SDL_SCANCODE_F2 },			
	{ "F3",			SDL_SCANCODE_F3 },			
	{ "F4",			SDL_SCANCODE_F4 },			
	{ "F5",			SDL_SCANCODE_F5 },			
	{ "F6",			SDL_SCANCODE_F6 },			
	{ "F7",			SDL_SCANCODE_F7 },			
	{ "F8",			SDL_SCANCODE_F8 },			
	{ "F9",			SDL_SCANCODE_F9 },			
	{ "F10",		SDL_SCANCODE_F10 },
	{ "F11",		SDL_SCANCODE_F11 },		
	{ "F12",		SDL_SCANCODE_F12 },		
};

void dae::Keyboard::KeyboardImpl::Update()
{
	std::memcpy(m_PreviousState, m_CurrentState, sizeof(m_CurrentState));
	std::memcpy(m_CurrentState, SDL_GetKeyboardState(nullptr), sizeof(m_CurrentState));
}

bool dae::Keyboard::KeyboardImpl::IsButtonCompatible(const Button& button) const
{
	return button.deviceType == DeviceType::keyboard;
}

bool dae::Keyboard::KeyboardImpl::IsDownThisFrame(const Button& button) const
{
	auto idx{ m_ButtonTable.at(button.name) };
	return !m_PreviousState[idx] && m_CurrentState[idx];
}

bool dae::Keyboard::KeyboardImpl::IsUpThisFrame(const Button& button) const
{
	auto idx{ m_ButtonTable.at(button.name) };
	return m_PreviousState[idx] && !m_CurrentState[idx];
}

bool dae::Keyboard::KeyboardImpl::IsPressed(const Button& button) const
{
	auto idx{ m_ButtonTable.at(button.name) };
	return m_CurrentState[idx];
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

bool dae::Keyboard::IsButtonCompatible(const Button& button) const
{
	return m_pImpl->IsButtonCompatible(button);
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

#pragma endregion Keyboard