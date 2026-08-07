#pragma once
#include <cstdint>
#include <variant>
#include <glm/vec2.hpp>
#include <string_view>
#include <vector>

namespace dae
{
	/// Variant that can be cast to the corresponding action type.
	/// Should be cast to bool with a InputActionButton, to a glm::vec2 with InputActionAxis2D.
	using ActionValue = std::variant<bool, glm::vec2>;
	
	/// Struct that is passed to the execute function of commands
	struct InputContext final
	{
		InputContext() = default;
		InputContext(ActionValue value);
		InputContext(ActionValue value, bool isDownThisFrame, bool isUpThisFrame);

		ActionValue value{};
		bool isDownThisFrame{ false };
		bool isUpThisFrame{ false };
	};
	
	/// All available devices in the engine.
	enum class DeviceType : uint8_t
	{
		invalid = 0,
		gamepad,
		keyboard,
		Mouse
	};
	
	struct Button final
	{
		Button() = default;
		Button(std::string_view name);

		std::string_view name{};
	};

	enum class Axis : uint32_t
	{
		leftStick,
		rightStick,
		Mouse
	};

	class InputDevice;
	class CompoundControl
	{
	public:
		virtual ~CompoundControl() = default;

		virtual InputContext GetActionContext(const InputDevice* pDevice) const = 0;

	protected:
		CompoundControl() = default;
	};

	class CompoundControlButton final : public CompoundControl
	{
	public:
		CompoundControlButton(const Button& left, const Button& right, const Button& up, const Button& down);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:
		Button m_Left{};
		Button m_Right{};
		Button m_Up{};
		Button m_Down{};
	};

	class CompoundControlAxis final : public CompoundControl
	{
	public:
		CompoundControlAxis(Axis axis);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:
		Axis m_Axis{};
	};
}