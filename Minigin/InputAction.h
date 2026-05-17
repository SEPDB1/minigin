#pragma once
#include "InputTypes.h"
#include <functional>
#include <string_view>
#include <vector>

namespace dae
{
    class InputActionBase
    {
    public:
        InputActionBase(std::string_view name, std::vector<UButton> buttons);

        virtual ~InputActionBase() = default;
        InputActionBase(const InputActionBase& other) = delete;
        InputActionBase(InputActionBase&& other) = delete;
        virtual InputActionBase& operator=(const InputActionBase& other) = delete;
        virtual InputActionBase& operator=(InputActionBase&& other) = delete;

        const std::vector<UButton>& GetButtons() const;
        std::string_view GetName() const;
        InputActionID GetID() const;

        virtual InputContext GetContext(InputDeviceID deviceID) const = 0;

    private:
        std::vector<UButton> m_Buttons;
        std::string_view m_Name{};
        InputActionID m_ID{};

        static inline InputActionID m_NextID{ 0 };
    };

    class InputActionButton final : public InputActionBase
    {
    public:
        InputActionButton(std::string_view name, UButton button);
        ~InputActionButton() = default;
        InputActionButton(const InputActionButton& other) = delete;
        InputActionButton(InputActionButton&& other) = delete;
        InputActionButton& operator=(const InputActionButton& other) = delete;
        InputActionButton& operator=(InputActionButton&& other) = delete;

        InputContext GetContext(InputDeviceID deviceID) const override;
    };

    class InputActionAxis2D final : public InputActionBase
    {
    public:
        InputActionAxis2D(std::string_view name, UButton left, UButton right, UButton up, UButton down);
        ~InputActionAxis2D() = default;
        InputActionAxis2D(const InputActionAxis2D& other) = delete;
        InputActionAxis2D(InputActionAxis2D&& other) = delete;
        InputActionAxis2D& operator=(const InputActionAxis2D& other) = delete;
        InputActionAxis2D& operator=(InputActionAxis2D&& other) = delete;

        InputContext GetContext(InputDeviceID deviceID) const override;
    };
}