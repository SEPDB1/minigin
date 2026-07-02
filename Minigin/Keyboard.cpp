#include "Keyboard.h"

const std::unordered_map<std::string_view, uint32_t> dae::Keyboard::m_ButtonTable
{
	{ "A",			4  },
	{ "B",			5  },
	{ "C",			6  },
	{ "D",			7  },
	{ "E",			8  },
	{ "F",			9  },
	{ "G",			10 },
	{ "H",			11 },
	{ "I",			12 },
	{ "J",			13 },
	{ "K",			14 },
	{ "L",			15 },
	{ "M",			16 },
	{ "N",			17 },
	{ "O",			18 },
	{ "P",			19 },
	{ "Q",			20 },
	{ "R",			21 },
	{ "S",			22 },
	{ "T",			23 },
	{ "U",			24 },
	{ "V",			25 },
	{ "W",			26 },
	{ "X",			27 },
	{ "Y",			28 },
	{ "Z",			29 },
	{ "1",			30 },
	{ "2",			31 },
	{ "3",			32 },
	{ "4",			33 },
	{ "5",			34 },
	{ "6",			35 },
	{ "7",			36 },
	{ "8",			37 },
	{ "9",			38 },
	{ "0",			39 },
	{ "Return",		40 },
	{ "Escape",		41 },
	{ "Backspace",	42 },
	{ "Tab",		43 },
	{ "Space",		44 },
	{ "F1",			58 },
	{ "F2",			59 },
	{ "F3",			60 },
	{ "F4",			61 },
	{ "F5",			62 },
	{ "F6",			63 },
	{ "F7",			64 },
	{ "F8",			65 },
	{ "F9",			66 },
	{ "F10",		67 },
	{ "F11",		68 },
	{ "F12",		69 },
};

void dae::Keyboard::Update()
{
	std::memcpy(m_PreviousState, m_CurrentState, sizeof(m_CurrentState));
	std::memcpy(m_CurrentState, SDL_GetKeyboardState(nullptr), sizeof(m_CurrentState));
}

bool dae::Keyboard::IsButtonCompatible(const Button& button) const
{
	return button.deviceType == DeviceType::keyboard;
}

bool dae::Keyboard::IsDownThisFrame(const Button& button) const
{
	auto idx{ m_ButtonTable.at(button.name) };
	return !m_PreviousState[idx] && m_CurrentState[idx];
}

bool dae::Keyboard::IsUpThisFrame(const Button& button) const
{
	auto idx{ m_ButtonTable.at(button.name) };
	return m_PreviousState[idx] && !m_CurrentState[idx];
}

bool dae::Keyboard::IsPressed(const Button& button) const
{
	auto idx{ m_ButtonTable.at(button.name) };
	return m_CurrentState[idx];
}
