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
	
	//enum class DeviceType : uint8_t
	//{
	//	invalid = 0,
	//	gamepad,
	//	keyboard
	//};
	
	struct Button final
	{
		Button() = default;
		Button(std::string_view name) : name{ name } {}

		std::string_view name{};
	};

	enum class Axis : uint32_t
	{
		leftStick,
		rightStick
	};
}