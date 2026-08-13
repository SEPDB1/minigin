#pragma once

struct MIX_Mixer;

namespace dae
{
	// A simple RAII wrapper for an MIX_Mixer
	class Mixer final
	{
	public:
		Mixer();
		~Mixer();
		Mixer(const Mixer& other) = default;
		Mixer(Mixer&& other) = default;
		Mixer& operator=(const Mixer& other) = default;
		Mixer& operator=(Mixer&& other) = default;

		MIX_Mixer* GetMixer() const;

	private:
		MIX_Mixer* m_pMixer;
	};
}