#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void Start();
		void Update();
		void Render();

		Scene& CreateScene();
		Scene& GetActiveScene() const;
		void SetActiveScene(Scene& scene);

	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<std::unique_ptr<Scene>> m_pScenes{};
		Scene* m_pActiveScene;
	};
}
