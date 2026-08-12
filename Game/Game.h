#pragma once
//#include "InputUtility.h"
#include <memory>

namespace dae
{
	class Scene;
	class GameObject;
	class TextComponent;
	class IGameState;
	class Game final
	{
	public:
		Game();
		~Game();
		Game(const Game& other) = delete;
		Game(Game&& other) = delete;
		Game& operator=(const Game& other) = delete;
		Game& operator=(Game&& other) = delete;

		void Start();
		void Update();

	private:
		std::unique_ptr<IGameState> m_pCurrentState;

		//static inline const GameMode m_GameMode{ GameMode::singlePlayer };
		//static inline const DeviceType m_PlayerOneDevice{ DeviceType::gamepad };
		//static inline const DeviceType m_PlayerTwoDevice{ DeviceType::gamepad };
	};
}
