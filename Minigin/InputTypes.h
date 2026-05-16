#pragma once
#include <variant>
#include <cstdint>
#include <glm/glm.hpp>

namespace dae
{
    using UButton = uint32_t; // Universal Button
    using InputActionID = uint32_t;
    using InputDeviceID = uint32_t;
    using ActionValue = std::variant<float, glm::vec2>;

    struct InputContext
    {
        InputContext(ActionValue value, bool started = false, bool canceled = false, bool isPressed = false)
            : value{ value }
            , started{ started }
            , canceled{ canceled }
            , isPressed{ isPressed }
        {

        }

        ActionValue value;
        bool started; // default state -> over treshold
        bool canceled; // over treshold -> default state
        bool isPressed; // over treshold   
    };
}