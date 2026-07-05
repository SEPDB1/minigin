#pragma once

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
		float m_ElapsedTime{};
		const float m_RotationSpeed{ 2.f };
		GameObject* m_pTank{};
		TextComponent* m_pTankValueDisplay{};
	};
}
