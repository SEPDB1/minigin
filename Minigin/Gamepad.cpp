#include "Gamepad.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <unordered_map>

#pragma region GamepadImpl
class dae::Gamepad::GamepadImpl final
{
public:
	GamepadImpl();
	~GamepadImpl() = default;
	GamepadImpl(const GamepadImpl& other) = delete;
	GamepadImpl(GamepadImpl&& other) = delete;
	GamepadImpl& operator=(const GamepadImpl& other) = delete;
	GamepadImpl& operator=(GamepadImpl&& other) = delete;

	void Update();

	bool IsDownThisFrame(const dae::Button& button) const;
	bool IsUpThisFrame(const dae::Button& button) const;
	bool IsPressed(const dae::Button& button) const;
	glm::vec2 GetAxisValue(Axis axis) const;

private:
	float NormaliseAxis(SHORT value, SHORT deadzone) const;

	WORD m_ButtonsPressedThisFrame{ 0 };
	WORD m_ButtonsReleasedThisFrame{ 0 };
	DWORD m_DeviceIdx{};
	_XINPUT_STATE m_CurrentState{};
	_XINPUT_STATE m_PreviousState{};

	static const std::unordered_map<std::string_view, uint32_t> m_ButtonTable;
};

const std::unordered_map<std::string_view, uint32_t> dae::Gamepad::GamepadImpl::m_ButtonTable
{ 
	{ "DpadUp",			0x0001 },
	{ "DpadDown",		0x0002 },
	{ "DpadLeft",		0x0004 },
	{ "DpadRight",		0x0008 },
	{ "Start",			0x0010 },
	{ "Back",			0x0020 },
	{ "LeftThumb",		0x0040 },
	{ "RightThumb",		0x0080 },
	{ "LeftShoulder",	0x0100 },
	{ "RightShoulder",	0x0200 },
	{ "A",				0x1000 },
	{ "B",				0x2000 },
	{ "X",				0x4000 },
	{ "Y",				0x8000 },
};

dae::Gamepad::GamepadImpl::GamepadImpl()
	: m_DeviceIdx{ 0 }
{
}

void dae::Gamepad::GamepadImpl::Update()
{
	m_PreviousState = m_CurrentState;
	m_CurrentState = {};
	XInputGetState(m_DeviceIdx, &m_CurrentState);

	WORD buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool dae::Gamepad::GamepadImpl::IsDownThisFrame(const dae::Button& button) const
{
	auto it = m_ButtonTable.find(button.name);

	if (it != m_ButtonTable.end())
		return m_ButtonsPressedThisFrame & it->second;

	return false;
}

bool dae::Gamepad::GamepadImpl::IsUpThisFrame(const dae::Button& button) const
{
	auto it = m_ButtonTable.find(button.name);

	if (it != m_ButtonTable.end())
		return m_ButtonsReleasedThisFrame & it->second;

	return false;
}

bool dae::Gamepad::GamepadImpl::IsPressed(const dae::Button& button) const
{
	auto it = m_ButtonTable.find(button.name);

	if (it != m_ButtonTable.end())
		return m_CurrentState.Gamepad.wButtons & it->second;

	return false;

}

glm::vec2 dae::Gamepad::GamepadImpl::GetAxisValue(Axis axis) const
{
	glm::vec2 value{};

	if (axis == Axis::leftStick)
	{
		value.x = NormaliseAxis(m_CurrentState.Gamepad.sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		value.y = -NormaliseAxis(m_CurrentState.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	}
	else
	{
		value.x = NormaliseAxis(m_CurrentState.Gamepad.sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		value.y = -NormaliseAxis(m_CurrentState.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
	}

	return value;
}
float dae::Gamepad::GamepadImpl::NormaliseAxis(SHORT value, SHORT deadzone) const
{
	// Apply deadzone
	if (value > -deadzone && value < deadzone)
		return 0.f;

	// Normalise
	float normalisedValue{ value / 32768.f };

	// Clamp
	if (normalisedValue < -1.f)
		return -1.f;

	if (normalisedValue > 1.f)
		return 1.f;

	return normalisedValue;
}
#pragma endregion GamepadImpl

#pragma region Gamepad

dae::Gamepad::Gamepad()
	: m_pImpl{ std::make_unique<GamepadImpl>() }
{
}

dae::Gamepad::~Gamepad() = default;

void dae::Gamepad::Update()
{
	m_pImpl->Update();
}

bool dae::Gamepad::IsDownThisFrame(const Button& button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool dae::Gamepad::IsUpThisFrame(const Button& button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

bool dae::Gamepad::IsPressed(const Button& button) const
{
	return m_pImpl->IsPressed(button);
}

glm::vec2 dae::Gamepad::GetAxisValue(Axis axis) const
{
	return m_pImpl->GetAxisValue(axis);
}
#pragma endregion Gamepad
