#pragma once
#include "InputUtility.h"

namespace dae
{
	class Scene;
	class GameObject;
	class TextComponent;
	class Game final
	{
	public:
		Game();
		~Game() = default;
		Game(const Game& other) = delete;
		Game(Game&& other) = delete;
		Game& operator=(const Game& other) = delete;
		Game& operator=(Game&& other) = delete;

		void Start();
		void Update();

	private:
		enum class GameMode : uint8_t
		{
			singlePlayer,
			coop,
			versus
		};

		static const GameMode m_GameMode{ GameMode::singlePlayer };
		static const DeviceType m_PlayerOneDevice{ DeviceType::gamepad };
		static const DeviceType m_PlayerTwoDevice{ DeviceType::gamepad };
	};
}
