#pragma once
#include <memory>

namespace dae
{
	class IGameState
	{
	public:
		virtual ~IGameState() = default;
		virtual std::unique_ptr<IGameState> Update() = 0;

		enum class GameMode : uint8_t
		{
			singlePlayer = 0,
			coop,
			versus
		};

	protected:
		inline static GameMode m_GameMode{ GameMode::singlePlayer };
	};

	class GameState final : public IGameState
	{
	public:
		GameState();
		~GameState();
		GameState(const GameState& other) = delete;
		GameState(GameState&& other) = delete;
		GameState& operator=(const GameState& other) = delete;
		GameState& operator=(GameState&& other) = delete;

		std::unique_ptr<IGameState> Update() override;
	};

	class StartScreenState final : public IGameState
	{
	public:
		StartScreenState();
		~StartScreenState();
		StartScreenState(const StartScreenState& other) = delete;
		StartScreenState(StartScreenState&& other) = delete;
		StartScreenState& operator=(const StartScreenState& other) = delete;
		StartScreenState& operator=(StartScreenState&& other) = delete;

		std::unique_ptr<IGameState> Update() override;
	};
}