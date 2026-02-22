#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Transform.h"
#include "Texture2D.h"

namespace dae
{
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;

		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& position);
		GameObject& SetParent(GameObject* pParent);

		const Transform& GetTransform() const;
		GameObject* GetParent() const;
		uint32_t GetChildCount() const;
		GameObject* GetChildAt(uint32_t index) const;

#pragma region TemplatedFunctions
		// Creates a new component of the requested type and attaches it to the game object,
		// the type has to be a component
		template <typename T>
		T* AttachComponent(GameObject* pOwner)
		{
			auto pUniqueComp = std::make_unique<T>(pOwner);
			auto pComp = pUniqueComp.get();
			m_pComponents.push_back(std::move(pUniqueComp));
			return pComp;
		}

		// TO DO: mark as cleanup
		// Removes the reqeusted component if any
		template <typename T>
		void RemoveComponent()
		{
			auto it = std::ranges::find_if(
				m_pComponents,
				[](auto comp) { return typeid(T) == typeid(*comp); });

			if (it != m_pComponents.end())
			{
				m_pComponents.erase(it);
			}
		}

		// Returns a raw pointer to the requested component if any, returns a nullptr otherwise
		template <typename T>
		T* GetComponent() const
		{
			auto it = std::ranges::find_if(
				m_pComponents,
				[](const auto& comp) { return typeid(T) == typeid(*comp); });

			if (it != m_pComponents.end())
			{
				return dynamic_cast<T*>((*it).get());
			}
			return nullptr;
		}
#pragma endregion TemplatedFunctions

	private:
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
		bool IsChild(GameObject* pGameObject) const;
		bool IsParent(GameObject* pGameObject) const;

		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren{};
		Transform m_Transform{};
		std::vector<std::unique_ptr<BaseComponent>> m_pComponents{};
	};
}
