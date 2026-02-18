#pragma once
#include <string>
#include <memory>
#include <vector>
#include "TransformComponent.h"
#include "TextureComponent.h"

namespace dae
{
	class GameObject 
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Update();
		virtual void Render() const;

		//void SetTexture(const std::string& filename);
		//void SetPosition(float x, float y);

		// Creates a new component instance and attaches it to the game object,
		// the template type has to be a component type
		template <typename T>
		std::shared_ptr<T> AttachComponent()
		{
			auto pComp = std::make_shared<T>();
			m_pComponents.push_back(pComp);
			return pComp;
		}

		// Removes the component with the templated type
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

		// Returns a shared pointer to the requested component,
		// returns a nullptr when the requested component is not attached to the GameObject
		template <typename T>
		const std::shared_ptr<T> GetComponent() const
		{
			//if (typeid(T) == typeid(TransformComponent))
			//{
			//	return m_Transform;
			//}

			auto it = std::ranges::find_if(
				m_pComponents,
				[](auto comp) { return typeid(T) == typeid(*comp); });

			if (it != m_pComponents.end())
			{
				return std::dynamic_pointer_cast<T>(*it);
			}
			return nullptr;
		}

	private:
		//TransformComponent m_Transform{};
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents{};
	};
}
