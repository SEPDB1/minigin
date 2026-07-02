#pragma once
#include "InputUtility.h"
#include <array>

namespace dae
{
	class InputDevice;

	class InputAction
	{
	public:
		virtual ~InputAction() = default;

		virtual InputContext GetActionContext(const InputDevice* pDevice) const = 0;

	protected:
		InputAction() = default;
		float GetButtonValue(const Button& button, const InputDevice* pDevice) const;
	};

	class InputActionButton final : public InputAction
	{
	public:
		explicit InputActionButton(const Button& button);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:
		Button m_Button{};
	};

	class InputActionAxis1D final : public InputAction
	{
	public: 
		InputActionAxis1D(const Button& left, const Button& right);

		InputContext GetActionContext(const InputDevice* pDevice) const override;


	private:
		Button m_ButtonLeft{};
		Button m_ButtonRight{};
	};

	class InputActionAxis2D final : public InputAction
	{
	public:
		InputActionAxis2D(const Button& left, const Button& right, const Button& up, const Button& down);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:
		Button m_ButtonLeft{};
		Button m_ButtonRight{};
		Button m_ButtonUp{};
		Button m_ButtonDown{};
	};
}