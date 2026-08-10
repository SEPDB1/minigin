#pragma once
#include <cstdint>
#include <memory>
#include <string>

namespace dae
{
	using SoundId = uint8_t;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const std::string&, float) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		~NullSoundSystem() = default;
		void Play(const std::string& file, float) override;
	};

	class SDLSoundSystem final: public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		void Play(const std::string&, float volume);

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};

	class SoundLocator final
	{
	public:
		static SoundSystem& GetSoundSystem();

		template <typename SoundSystemT> requires std::derived_from<SoundSystemT, SoundSystem>
		static SoundSystemT& RegisterSoundSystem()
		{
			m_pSoundSystem = std::move(std::make_unique<SoundSystemT>());
			return dynamic_cast<SoundSystemT&>(*m_pSoundSystem);
		}

	private:
		static std::unique_ptr<SoundSystem> m_pSoundSystem;
	};

}