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

		GameObject& SetPosition(float x, float y);
		GameObject& SetPosition(const glm::vec2& pos);
		GameObject& SetRotation(float radians);
		GameObject& SetScale(float x, float y);
		GameObject& SetScale(const glm::vec2& scale);
		GameObject& SetParent(GameObject* pParent, bool keepWorldPosition);

		const Transform& GetTransform() const;
		GameObject* GetParent() const;
		uint32_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;

#pragma region TemplatedFunctions
		// Creates a new component of the requested type and attaches it to the game object,
		// the type has to be a component
		template <typename ComponentT, typename... Args> requires std::derived_from<ComponentT, BaseComponent>
		ComponentT* AttachComponent(GameObject* pOwner, Args&&... args)
		{
			auto pUniqueComp{ std::make_unique<ComponentT>(pOwner, std::forward<Args>(args)...) };
			auto pComp = pUniqueComp.get();
			m_pComponents.push_back(std::move(pUniqueComp));
			return pComp;
		}

		// TO DO: mark as cleanup
		// Removes the reqeusted component if any
		template <typename ComponentT> requires std::derived_from<ComponentT, BaseComponent>
		void RemoveComponent()
		{
			auto it = std::ranges::find_if(
				m_pComponents,
				[](auto comp) { return typeid(ComponentT) == typeid(*comp); });

			if (it != m_pComponents.end())
			{
				m_pComponents.erase(it);
			}
		}

		// Returns a raw pointer to the requested component if any, returns a nullptr otherwise
		template <typename ComponentT> requires std::derived_from<ComponentT, BaseComponent>
		ComponentT* GetComponent() const
		{
			auto it = std::ranges::find_if(
				m_pComponents,
				[](const auto& comp) { return typeid(ComponentT) == typeid(*comp); });

			if (it != m_pComponents.end())
			{
				return dynamic_cast<ComponentT*>((*it).get());
			}
			return nullptr;
		}
#pragma endregion TemplatedFunctions

	private:
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
		void SetTransformDirty() const;

		void UpdateWorldTransform() const;

		bool IsChild(GameObject* pGameObject) const;
		bool IsParent(GameObject* pGameObject) const;

		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren{};
		std::vector<std::unique_ptr<BaseComponent>> m_pComponents{};
		mutable Transform m_GlobalTransform{};
		Transform m_LocalTransform{};
		mutable bool m_IsWorldTransformDirty{ false };
	};
}
