#pragma once
#include <cstdint>
#include <variant>
#include <glm/vec2.hpp>
#include <unordered_map>
#include <string_view>

namespace dae
{
	using ActionValue = std::variant<bool, float, glm::vec2>;
	
	struct InputContext final
	{
		InputContext() = default;
		InputContext(ActionValue value) : value{ value } {}
		InputContext(ActionValue value, bool isDownThisFrame, bool isUpThisFrame) 
			: value{ value }, isDownThisFrame{ isDownThisFrame }, isUpThisFrame{ isUpThisFrame } {};

		ActionValue value{};
		bool isDownThisFrame{ false };
		bool isUpThisFrame{ false };
	};
	
	enum class DeviceType
	{
		invalid = 0,
		gamepad,
		keyboard
	};
	
	struct Button final
	{
		Button() = default;
		Button(std::string_view name, DeviceType deviceType) : name{ name }, deviceType{ deviceType } {}

		std::string_view name{};
		DeviceType deviceType{ DeviceType::invalid };
	};

	//enum class Button : uint32_t
	//{
	//	invalid = 0,

	//	// Gamepad
	//	gamepadDpadUp = 0x0001,
	//	gamepadDpadDown = 0x0002,
	//	gamepadDpadLeft = 0x0004,
	//	gamepadDpadRight = 0x0008,
	//	gamepadStart = 0x0010,
	//	gamepadBack = 0x0020,
	//	gamepadLeftThumb = 0x0040,
	//	gamepadRightThumb = 0x0080,
	//	gamepadLeftShoulder = 0x0100,
	//	gamepadRightShoulder = 0x0200,
	//	gamepadA = 0x1000,
	//	gamepadB = 0x2000,
	//	gamepadX = 0x4000,
	//	gamepadY = 0x8000,

	//	// Keyboard
	//	keyboardA = 4,
	//	keyboardB = 5,
	//	keyboardC = 6,
	//	keyboardD = 7,
	//	keyboardE = 8,
	//	keyboardF = 9,
	//	keyboardG = 10,
	//	keyboardH = 11,
	//	keyboardI = 12,
	//	keyboardJ = 13,
	//	keyboardK = 14,
	//	keyboardL = 15,
	//	keyboardM = 16,
	//	keyboardN = 17,
	//	keyboardO = 18,
	//	keyboardP = 19,
	//	keyboardQ = 20,
	//	keyboardR = 21,
	//	keyboardS = 22,
	//	keyboardT = 23,
	//	keyboardU = 24,
	//	keyboardV = 25,
	//	keyboardW = 26,
	//	keyboardX = 27,
	//	keyboardY = 28,
	//	keyboardZ = 29,
	//	keyboard1 = 30,
	//	keyboard2 = 31,
	//	keyboard3 = 32,
	//	keyboard4 = 33,
	//	keyboard5 = 34,
	//	keyboard6 = 35,
	//	keyboard7 = 36,
	//	keyboard8 = 37,
	//	keyboard9 = 38,
	//	keyboard0 = 39,
	//	keyboardReturn = 40,
	//	keyboardEscape = 41,
	//	keyboardBackspace = 42,
	//	keyboardTab = 43,
	//	keyboardSpace = 44,
	//	keyboardF1 = 58,
	//	keyboardF2 = 59,
	//	keyboardF3 = 60,
	//	keyboardF4 = 61,
	//	keyboardF5 = 62,
	//	keyboardF6 = 63,
	//	keyboardF7 = 64,
	//	keyboardF8 = 65,
	//	keyboardF9 = 66,
	//	keyboardF10 = 67,
	//	keyboardF11 = 68,
	//	keyboardF12 = 69,
	//};
}