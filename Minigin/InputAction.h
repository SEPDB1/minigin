#pragma once
#include "InputUtility.h"
#include <vector>
#include <memory>

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
	};

	class InputActionButton final : public InputAction
	{
	public:
		explicit InputActionButton(const Button& button);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:
		Button m_Button{};
	};

	class InputActionAxis2D final : public InputAction
	{
	public:
		explicit InputActionAxis2D(std::unique_ptr<CompoundControl> pControl);
		explicit InputActionAxis2D(std::vector<std::unique_ptr<CompoundControl>> controls);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:
		std::vector<std::unique_ptr<CompoundControl>> m_Controls{};
	};
}