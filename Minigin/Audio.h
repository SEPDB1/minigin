#pragma once
#include <string>

struct MIX_Mixer;
struct MIX_Audio;

namespace dae
{
	// A simple RAII wrapper for an MIX_Audio
	class Audio final
	{
	public:
		explicit Audio(const std::string& path, MIX_Mixer* pMixer);
		~Audio();
		Audio(const Audio& other) = default;
		Audio(Audio&& other) = default;
		Audio& operator=(const Audio& other) = default;
		Audio& operator=(Audio && other) = default;

		MIX_Audio* GetAudio() const;

	private:
		MIX_Audio* m_pAudio;
	};
}