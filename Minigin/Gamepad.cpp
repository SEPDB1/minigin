#include "Gamepad.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

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

	bool IsButtonCompatible(const dae::Button& button) const;

	bool IsDownThisFrame(const dae::Button& button) const;
	bool IsUpThisFrame(const dae::Button& button) const;
	bool IsPressed(const dae::Button& button) const;

private:
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

	if (m_CurrentState.dwPacketNumber != m_PreviousState.dwPacketNumber)
	{
		WORD buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}
}

bool dae::Gamepad::GamepadImpl::IsButtonCompatible(const dae::Button & button) const
{
	return button.deviceType == dae::DeviceType::gamepad;
}

bool dae::Gamepad::GamepadImpl::IsDownThisFrame(const dae::Button& button) const
{
	return m_ButtonsPressedThisFrame & m_ButtonTable.at(button.name);
}

bool dae::Gamepad::GamepadImpl::IsUpThisFrame(const dae::Button& button) const
{
	return m_ButtonsReleasedThisFrame & m_ButtonTable.at(button.name);
}

bool dae::Gamepad::GamepadImpl::IsPressed(const dae::Button& button) const
{
	return m_CurrentState.Gamepad.wButtons & m_ButtonTable.at(button.name);
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

bool dae::Gamepad::IsButtonCompatible(const Button& button) const
{
	return m_pImpl->IsButtonCompatible(button);
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
#pragma endregion Gamepad
