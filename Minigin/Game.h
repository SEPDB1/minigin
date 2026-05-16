#pragma once

namespace dae
{
	class Scene;
	class GameObject;
	class Game final
	{
	public:
		Game(Scene* pScene);
		void Start();
		void Update();

	private:
		Scene* m_pScene;
		GameObject* m_pBackground{};
		GameObject* m_pLogo{};
		GameObject* m_pTitle{};
		GameObject* m_pFpsObject{};
	};
}
