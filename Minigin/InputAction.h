#pragma once
#include "InputUtility.h"
#include <vector>

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
		static float GetButtonValue(const Button& button, const InputDevice* pDevice);
	};

	class InputActionButton final : public InputAction
	{
	public:
		explicit InputActionButton(const Button& button);
		explicit InputActionButton(const std::vector<Button>& buttons);

		void AddButton(const Button& button);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:
		std::vector<Button> m_Buttons{};
	};

	class InputActionAxis2D final : public InputAction
	{
	public:
		InputActionAxis2D() = default;
		InputActionAxis2D(const Button& left, const Button& right, const Button& up, const Button& down);
		InputActionAxis2D(const std::vector<Button>& leftButtons, const std::vector<Button>& rightButtons,
			const std::vector<Button>& upButtons, const std::vector<Button>& downButtons);

		void AddConfiguration(const Button& left, const Button& right, const Button& up, const Button& down);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:
		static float GetHighestValue(const std::vector<Button>& buttons, const InputDevice* pDevice);

		std::vector<Button> m_LeftButtons{};
		std::vector<Button> m_RightButtons{};
		std::vector<Button> m_UpButtons{};
		std::vector<Button> m_DownButtons{};
	};

#pragma region InputActionAxis1D
	//class InputActionAxis1D final : public InputAction
	//{
	//public: 
	//	InputActionAxis1D(const Button& left, const Button& right);

	//	InputContext GetActionContext(const InputDevice* pDevice) const override;


	//private:
	//	Button m_LeftButtons{};
	//	Button m_RightButtons{};
	//};
#pragma endregion InputActionAxis1D
}