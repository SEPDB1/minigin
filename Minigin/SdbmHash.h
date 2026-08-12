#pragma once
namespace dae
{
	template <int Length> struct SdbmHash
	{
		consteval static unsigned int _calculate(const char* const text, unsigned int& value)
		{
			const unsigned int character = SdbmHash<Length - 1>::_calculate(text, value);
			value = character + (value << 6) + (value << 16) - value;
			return text[Length - 1];
		}
		consteval static unsigned int calculate(const char* const text)
		{
			unsigned int value = 0;
			const auto character = _calculate(text, value);
			return character + (value << 6) + (value << 16) - value;
		}
	};
	
	template <> 
	struct SdbmHash<1>
	{
		consteval static int _calculate(const char* const text, unsigned int&) { return text[0]; }
	};
	
	template <size_t N> 
	consteval unsigned int MakeSdbmHash(const char(&text)[N]) 
	{
		return SdbmHash<N - 1>::calculate(text);
	}
}