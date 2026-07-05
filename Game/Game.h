#pragma once

namespace dae
{
	class Scene;
	class GameObject;
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
		Scene* m_pTestScene{};
		GameObject* m_pBackground{};
		GameObject* m_pLogo{};
		GameObject* m_pTitle{};
		GameObject* m_pFpsObject{};
	};
}
