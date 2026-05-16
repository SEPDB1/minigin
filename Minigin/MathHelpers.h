#pragma once
#include <cmath>
#include <concepts>

namespace dae
{
    namespace math
    {
        template<typename T> requires std::floating_point<T>
        constexpr T Lerp(T a, T b, T t) noexcept 
        {
            return a + t * (b - a);
        }

        template<typename T> requires std::floating_point<T>
        constexpr T InverseLerp(T a, T b, T value) noexcept
        {
            if (a == b) 
                return static_cast<T>(0.0);

            return (value - a) / (b - a);
        }
    }
}
