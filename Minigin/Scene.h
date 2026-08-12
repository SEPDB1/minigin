#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"

namespace dae
{
	class CollisionHandler;
	class Scene final
	{
	public:
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Start();
		void Update();
		void Render() const;

		GameObject& AddObject();
		void Remove(const GameObject& object);
		void RemoveAll();

		CollisionHandler& GetCollisionHandler() const;

	private:
		friend class SceneManager;
		explicit Scene();

		std::vector<std::unique_ptr<GameObject>> m_Objects{};
		std::unique_ptr<CollisionHandler> m_pCollisionHandler{};
		bool m_IsStarted{ false };
	};

}
